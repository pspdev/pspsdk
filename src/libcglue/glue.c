/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * glue.c - Newlib-compatible system calls.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 * Copyright (c) 2021 Francisco J Trujillo <fjtrujy@gmail.com>
 *
 */

#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>

#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <psptypes.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspsysmem.h>
#include <pspthreadman.h>
#include <psputils.h>
#include <pspsdk.h>
#include <psprtc.h>

#include "fdman.h"

#define DEFAULT_HEAP_THRESHOLD_SIZE_KB 512

/* If defined it specifies the desired size of the heap, in KB. */
extern unsigned int sce_newlib_heap_kb_size __attribute__((weak));
extern unsigned int sce_newlib_heap_threshold_kb_size __attribute__((weak));

/* Functions from cwd.c */
extern char __cwd[MAXNAMLEN + 1];
int __path_absolute(const char *in, char *out, int len);

/* Functions from mutexman.c */
extern SceLwMutexWorkarea __malloc_mutex;
extern SceLwMutexWorkarea __sbrk_mutex;

/* Fuctions from errno.c */
int __set_errno(int code);

/* Functions from pipe.c */
int __pipe_read(int fd, void *buf, size_t len);
int __pipe_close(int fd);
int __pipe_write(int fd, const void *buf, size_t len);
int __pipe_nonblocking_read(int fd, void *buf, size_t len);
int __pipe_nonblocking_write(int fd, const void *buf, size_t len);

/* Functions from socket.c */
int __socket_close(int sock);

#ifdef F___fill_stat
static time_t psp_to_posix_time(ScePspDateTime psp_time)
{
	struct tm conv_time;
	conv_time.tm_year = psp_time.year;
	conv_time.tm_mon = psp_time.month;
	conv_time.tm_mday = psp_time.day;
	conv_time.tm_hour = psp_time.hour;
	conv_time.tm_min = psp_time.minute;
	conv_time.tm_sec = psp_time.second;
	conv_time.tm_isdst = -1;
	return mktime(&conv_time);
}

static mode_t io_to_posix_mode(SceMode sceMode)
{
        mode_t posixmode = 0;
        if (sceMode & FIO_SO_IFREG) posixmode |= S_IFREG;
        if (sceMode & FIO_SO_IFDIR) posixmode |= S_IFDIR;
        if (sceMode & FIO_SO_IROTH) posixmode |= S_IRUSR|S_IRGRP|S_IROTH;
        if (sceMode & FIO_SO_IWOTH) posixmode |= S_IWUSR|S_IWGRP|S_IWOTH;
        if (sceMode & FIO_SO_IXOTH) posixmode |= S_IXUSR|S_IXGRP|S_IXOTH;
        return posixmode;
}


void __fill_stat(struct stat *stat, const SceIoStat *sce_stat)
{
        stat->st_dev = 0;
        stat->st_ino = 0;
        stat->st_mode = io_to_posix_mode(sce_stat->st_attr);
        stat->st_nlink = 0;
        stat->st_uid = 0;
        stat->st_gid = 0;
        stat->st_rdev = 0;
        stat->st_size = sce_stat->st_size;
        stat->st_atime = psp_to_posix_time(sce_stat->sce_st_atime);
        stat->st_mtime = psp_to_posix_time(sce_stat->sce_st_mtime);
        stat->st_ctime = psp_to_posix_time(sce_stat->sce_st_ctime);
        stat->st_blksize = 16*1024;
        stat->st_blocks = stat->st_size / 512;
}
#else
void __fill_stat(struct stat *stat, const SceIoStat *sce_stat);
#endif

#ifdef F___psp_heap_blockid
/* UID of the memory block that represents the heap. */
SceUID __psp_heap_blockid;
#else
extern SceUID __psp_heap_blockid;
#endif

#ifdef F___psp_free_heap
/* Free the heap. */
int __psp_free_heap(void)
{
	if (__psp_heap_blockid > 0) {
		return sceKernelFreePartitionMemory(__psp_heap_blockid);
	}

	return __psp_heap_blockid;
}
#endif

#ifdef F__open
int _open(const char *buf, int flags, int mode) {
	int scefd, fd, sce_flags, is_dir;
	char dest[MAXNAMLEN + 1];

	if(__path_absolute(buf, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

   is_dir = 0;
	/* O_RDONLY starts at 0, where PSP_O_RDONLY starts at 1, so remap the read/write
	   flags by adding 1. */
	sce_flags = (flags & O_ACCMODE) + 1;

	/* Translate standard open flags into the flags understood by the PSP kernel. */
	if (flags & O_APPEND) {
		sce_flags |= PSP_O_APPEND;
	}
	if (flags & O_CREAT) {
		sce_flags |= PSP_O_CREAT;
	}
	if (flags & O_TRUNC) {
		sce_flags |= PSP_O_TRUNC;
	}
	if (flags & O_EXCL) {
		sce_flags |= PSP_O_EXCL;
	}
	if (flags & O_NONBLOCK) {
		sce_flags |= PSP_O_NBLOCK;
	}
	if (flags & O_DIRECTORY) {
		sce_flags |= PSP_O_DIR;
		is_dir = 1;
	}

	scefd = is_dir ? sceIoDopen(dest) : sceIoOpen(dest, sce_flags, mode);
	if (scefd >= 0) {
		fd = __fdman_get_new_descriptor();
		if (fd != -1) {
			__descriptormap[fd]->descriptor = scefd;
			__descriptormap[fd]->type = is_dir ? __DESCRIPTOR_TYPE_FOLDER : __DESCRIPTOR_TYPE_FILE;
			__descriptormap[fd]->flags = flags;
			__descriptormap[fd]->filename = strdup(dest);
			return fd;
		}
		else {
			is_dir ? sceIoDclose(scefd) : sceIoClose(scefd);
			errno = ENOMEM;
			return -1;
		}
	} 
	else {
		return __set_errno(scefd);
	}
}

#endif

#ifdef F__close
int _close(int fd) {
	int ret = 0;

	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_FILE:
		case __DESCRIPTOR_TYPE_TTY:
			if (__descriptormap[fd]->ref_count == 1) {
				ret = __set_errno(sceIoClose(__descriptormap[fd]->descriptor));
			}
			__fdman_release_descriptor(fd);
			return ret;
			break;
		case __DESCRIPTOR_TYPE_FOLDER:
			if (__descriptormap[fd]->ref_count == 1) {
				ret = __set_errno(sceIoDclose(__descriptormap[fd]->descriptor));
			}
			__fdman_release_descriptor(fd);
			return ret;
			break;
		case __DESCRIPTOR_TYPE_PIPE:
			return __pipe_close(fd);
			break;
		case __DESCRIPTOR_TYPE_SOCKET:
			return __socket_close(fd);
			break;
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F__read
int _read(int fd, void *buf, size_t nbytes) {
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_FILE:
		case __DESCRIPTOR_TYPE_TTY:
			return __set_errno(sceIoRead(__descriptormap[fd]->descriptor, buf, nbytes));
			break;
		case __DESCRIPTOR_TYPE_PIPE:
			if (__descriptormap[fd]->flags & O_NONBLOCK) {
				return __pipe_nonblocking_read(fd, buf, nbytes);
			}
			else {
				return __pipe_read(fd, buf, nbytes);
			}
			break;
		case __DESCRIPTOR_TYPE_SOCKET:
			return recv(fd, buf, nbytes, 0);
			break;
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F__write
int _write(int fd, const void *buf, size_t nbytes) {
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_FILE:
		case __DESCRIPTOR_TYPE_TTY:
			return __set_errno(sceIoWrite(__descriptormap[fd]->descriptor, buf, nbytes));
			break;
		case __DESCRIPTOR_TYPE_PIPE:
			if (__descriptormap[fd]->flags & O_NONBLOCK) {
				return __pipe_nonblocking_write(fd, buf, nbytes);
			}
			else {
				return __pipe_write(fd, buf, nbytes);
			}
			break;
			break;
		case __DESCRIPTOR_TYPE_SOCKET:
			return send(fd, buf, nbytes, 0);
			break;
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F__stat
int _stat(const char *filename, struct stat *buf)
{
	SceIoStat psp_stat;
	char dest[MAXNAMLEN + 1];
	int ret;

	if(__path_absolute(filename, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	memset(buf, '\0', sizeof(struct stat));
	ret = sceIoGetstat(dest, &psp_stat);
	if (ret < 0) {
		return __set_errno(ret);
	}

	__fill_stat(buf, &psp_stat);
	return 0;
}
#else
int _stat(const char *filename, struct stat *buf);
#endif

#ifdef F_lstat
int lstat(const char *filename, struct stat *buf)
{
	return stat(filename, buf);
}
#endif

#ifdef F__fstat
int _fstat(int fd, struct stat *buf) {
	int ret;
	SceOff oldpos;
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_TTY:
			memset(buf, '\0', sizeof(struct stat));
			buf->st_mode = S_IFCHR;
			return 0;
			break;		
		case __DESCRIPTOR_TYPE_FILE:
			if (__descriptormap[fd]->filename != NULL) {
				ret = _stat(__descriptormap[fd]->filename, buf);
				
				/* Find true size of the open file */
				oldpos = sceIoLseek(__descriptormap[fd]->descriptor, 0, SEEK_CUR);
				if (oldpos != (off_t) -1) {
					buf->st_size = (off_t) sceIoLseek(__descriptormap[fd]->descriptor, 0, SEEK_END);
					sceIoLseek(__descriptormap[fd]->descriptor, oldpos, SEEK_SET);
				}
				return ret;
			}
			break;
		case __DESCRIPTOR_TYPE_PIPE:
		case __DESCRIPTOR_TYPE_SOCKET:
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F_access
int access(const char *fn, int flags)
{
	struct stat s;
	if (stat(fn, &s))
		return -1;
	if (s.st_mode & S_IFDIR)
		return 0;
	if (flags & W_OK)
	{
		if (s.st_mode & S_IWRITE)
			return 0;
		errno = EACCES;
		return -1;
	}
	return 0;
}
#endif

#ifdef F__fcntl
int _fcntl(int fd, int cmd, ...)
{
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch (cmd)
	{
		case F_DUPFD:
		{
			return __fdman_get_dup_descriptor(fd);
			break;
		}
		case F_GETFL:
		{
			return __descriptormap[fd]->flags;
			break;
		}
		case F_SETFL:
		{
			int newfl;
			va_list args;
	
			va_start (args, cmd);         /* Initialize the argument list. */
			newfl =  va_arg(args, int);
			va_end (args);                /* Clean up. */

			__descriptormap[fd]->flags = newfl;

			switch(__descriptormap[fd]->type)
			{
				case __DESCRIPTOR_TYPE_FILE:
					break;
				case __DESCRIPTOR_TYPE_PIPE:
					break;
				case __DESCRIPTOR_TYPE_SOCKET:
					if (newfl & O_NONBLOCK)
					{
						int one = 1;
						return setsockopt(fd, SOL_SOCKET, SO_NONBLOCK, (char *)&one, sizeof(one));
					}
					else
					{
						int zero = 0;
						return setsockopt(fd, SOL_SOCKET, SO_NONBLOCK, (char *)&zero, sizeof(zero));
					}
					break;
				default:
					break;
			}
			return 0;
			break;
		}
	}

	errno = EBADF;
	return -1;
}
#endif /* F__fcntl */

#ifdef F_getdents
int getdents(int fd, void *dd_buf, int count)
{
	struct dirent *dirp;
	int rv, read;
	SceIoDirent sceiode;

	read = 0;
   // NEEDED otherwise it will crash!!!
   memset(&sceiode, 0, sizeof(SceIoDirent));
   rv = sceIoDread(__descriptormap[fd]->descriptor, &sceiode);
   if (rv < 0) {
      return __set_errno(rv);
   } else if (rv == 0) {
      return read;
   }

   read += sizeof(struct dirent);
   dirp = (struct dirent *)dd_buf;

   dirp->d_fileno = rv;
   strncpy(dirp->d_name, sceiode.d_name, MAXNAMLEN);
   dirp->d_name[MAXNAMLEN] = 0;
   dirp->d_reclen = count;
	
	return read;
}
#endif

#ifdef F__seekdir
void _seekdir(DIR *dirp, long loc)
{
	int i;
	SceUID uid;
	SceIoDirent sceiode;

	if (__descriptormap[dirp->dd_fd]->filename != NULL) {
		sceIoDclose(__descriptormap[dirp->dd_fd]->descriptor);
		uid = sceIoDopen(__descriptormap[dirp->dd_fd]->filename);
		__descriptormap[dirp->dd_fd]->descriptor = uid;
		for (i = 0; i < loc; i++) {
   			// NEEDED otherwise it will crash!!!
   			memset(&sceiode, 0, sizeof(SceIoDirent));
   			sceIoDread(uid, &sceiode);
		}
	}
}
#endif

#ifdef F__lseek
off_t _lseek(int fd, off_t offset, int whence)
{
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	switch(__descriptormap[fd]->type)
	{
		case __DESCRIPTOR_TYPE_FILE:
			/* We don't have to do anything with the whence argument because SEEK_* == PSP_SEEK_*. */
			return (off_t) __set_errno(sceIoLseek(__descriptormap[fd]->descriptor, offset, whence));
			break;
		case __DESCRIPTOR_TYPE_PIPE:
			break;
		case __DESCRIPTOR_TYPE_SOCKET:
			break;
		default:
			break;
	}

	errno = EBADF;
	return -1;
}
#endif

#ifdef F_chdir
int chdir(const char *path)
{
	char dest[MAXNAMLEN + 1];
	SceUID uid;

	if(__path_absolute(path, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	/* sceIoChdir doesn't give an indication of whether it worked,
	   so test for existence by attempting to open the dir */
	uid = sceIoDopen(dest);
	if(uid < 0) {
		errno = ENOTDIR;
		return -1;
	}
	sceIoDclose(uid);

	sceIoChdir(dest);
	strcpy(__cwd, dest);
	return 0;
}
#endif

#ifdef F_mkdir
int mkdir(const char *pathname, mode_t mode)
{
	char dest[MAXNAMLEN + 1];

	if(__path_absolute(pathname, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	return __set_errno(sceIoMkdir(dest, mode));
}
#endif

#ifdef F_rmdir
int rmdir(const char *pathname)
{
	char dest[MAXNAMLEN + 1];

	if(__path_absolute(pathname, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	return __set_errno(sceIoRmdir(dest));
}
#endif

#ifdef F__link
int _link(const char *old, const char *new) {
    errno = ENOSYS;
	return -1; /* not supported */
}
#endif

#ifdef F__unlink
int _unlink(const char *path) {
    errno = ENOSYS;
	return -1; /* not supported */
}
#endif

#ifdef F__rename
int _rename(const char *old, const char *new)
{
   char oldname[MAXNAMLEN + 1];
   char newname[MAXNAMLEN + 1];

   if(__path_absolute(old, oldname, MAXNAMLEN) < 0) {
       errno = ENAMETOOLONG;
       return -1;
   }

   if(__path_absolute(new, newname, MAXNAMLEN) < 0) {
       errno = ENAMETOOLONG;
       return -1;
   }

   return __set_errno(sceIoRename(oldname, newname));
}
#endif

#ifdef F__getpid
pid_t _getpid(void)
{
	return (pid_t)__set_errno(sceKernelGetThreadId());
}
#endif

#ifdef F__kill
int _kill(pid_t pid, int sig)
{
	return __set_errno(sceKernelDeleteThread((SceUID)pid));
}
#endif

#ifdef F__fork
pid_t _fork(void)
{
	errno = ENOSYS;
	return (pid_t) -1; /* not supported */
}
#endif

#ifdef F__wait
pid_t _wait(int *unused)
{
	errno = ENOSYS;
	return (pid_t) -1; /* not supported */
}
#endif

#ifdef F__sbrk
#define TO_KB(value) (value * 1024)
void * _sbrk(ptrdiff_t incr)
{
	static void * heap_bottom = NULL;
	static void * heap_top = NULL;
	static void * heap_ptr = NULL;

	sceKernelLockLwMutex(&__sbrk_mutex, 1, 0);

	/* Has our heap been initialized? */
	if (heap_bottom == NULL) {
		/* No, initialize the heap. */
		SceSize heap_size = (SceSize) -1;

		if (&sce_newlib_heap_kb_size != NULL) {
			heap_size = TO_KB(sce_newlib_heap_kb_size);
		}

		if ((int)heap_size < 0) {
			heap_size = sceKernelMaxFreeMemSize();
			if(&sce_newlib_heap_threshold_kb_size != NULL)
				heap_size -= TO_KB(sce_newlib_heap_threshold_kb_size);
			else
				heap_size -= TO_KB(DEFAULT_HEAP_THRESHOLD_SIZE_KB);
		}

		if (heap_size != 0) {
			__psp_heap_blockid = sceKernelAllocPartitionMemory(PSP_MEMORY_PARTITION_USER, "heap_block", PSP_SMEM_Low, heap_size, NULL);
			if (__psp_heap_blockid > 0) {
				heap_bottom = sceKernelGetBlockHeadAddr(__psp_heap_blockid);
				heap_ptr = heap_bottom;
				heap_top = (unsigned char *) heap_bottom + heap_size;
			}
		}
	}

	void * heap_addr = (void *) -1;
	void * next_heap_ptr = (void *) ((ptrdiff_t) heap_ptr + incr);
	if ((heap_bottom != NULL) && (next_heap_ptr >= heap_bottom) && (next_heap_ptr < heap_top)) {
		heap_addr = heap_ptr;
		heap_ptr = next_heap_ptr;
	}

	sceKernelUnlockLwMutex(&__sbrk_mutex, 1);

	return heap_addr;
}
#endif

#ifdef F__gettimeofday
int _gettimeofday(struct timeval *tp, struct timezone *tzp)
{
	int ret;
	struct SceKernelTimeval pspTimeval;

	ret = __set_errno(sceKernelLibcGettimeofday(&pspTimeval, tzp));
	if (ret < 0)
		return ret;

	/* Return the actual time since epoch */
	tp->tv_sec = pspTimeval.tv_sec;
	tp->tv_usec = pspTimeval.tv_usec;

	return 0;
}
#endif

#ifdef F__times
clock_t _times(struct tms *buffer) 
{
	clock_t clk = sceKernelGetSystemTimeWide();

	if (buffer != NULL) {
		buffer->tms_utime  = clk;
		buffer->tms_stime  = 0;
		buffer->tms_cutime = clk;
		buffer->tms_cstime = 0;
	}

	return clk;
}
#endif

#ifdef F_ftime
int ftime(struct timeb *tb)
{
  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);

  tb->time = tv.tv_sec;
  tb->millitm = tv.tv_usec / 1000;
  tb->timezone = tz.tz_minuteswest;
  tb->dstflag = tz.tz_dsttime;

  return 0;
}
#endif

#ifdef F__internal_malloc_lock
void _internal_malloc_lock(struct _reent *ptr)
{
	sceKernelLockLwMutex(&__malloc_mutex, 1, 0);
}
#endif

#ifdef F__internal_malloc_unlock
void _internal_malloc_unlock(struct _reent *ptr)
{
	sceKernelUnlockLwMutex(&__malloc_mutex, 1);
}
#endif

// Some POSIX functions that are missing in NEWLIB

#ifdef F_symlink
int symlink(const char *path1, const char *path2)
{
  return link(path1, path2);
}
#endif

#ifdef F_truncate
int truncate(const char *path, off_t length)
{
	ssize_t bytes_read;
    int fd;
    char buff[length];

	fd = open(path, O_RDONLY);
	if (fd < 0) {
		return -1;
	}

	bytes_read = read(fd, &buff, length);
	close(fd);
	if (bytes_read < length) {
		errno = EFBIG;
		return -1;
	}

	fd = open (path, O_TRUNC|O_WRONLY);
	if (fd < 0) {
		return -1;
	}

	write(fd, &buff, length);
	close(fd);
	return 0;
}
#endif

#ifdef F__isatty
int _isatty(int fd)
{
	errno = ENOTTY;
	return -1; /* not supported */
}
#endif

#ifdef F_chmod
int chmod(const char *pathname, mode_t mode)
{
	SceIoStat psp_stat;
	char dest[MAXNAMLEN + 1];
	int ret;

	if(__path_absolute(pathname, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	ret = sceIoGetstat(dest, &psp_stat);
	if (ret < 0) {
		return __set_errno(ret);
	}

	psp_stat.st_mode = (SceMode)mode;
	ret = sceIoChstat(dest, &psp_stat, 0x0001);
	if (ret < 0) {
		return __set_errno(ret);
	}
    
	return 0;
}
#endif

#ifdef F_fchmod
int fchmod(int fd, mode_t mode)
{
	return chmod(__descriptormap[fd]->filename, mode);
}
#endif

#ifdef F_fchmodat
int fchmodat(int fd, const char *path, mode_t mode, int flag)
{
	return chmod(path, mode);
}
#endif

#ifdef F_pathconf
long int pathconf(const char *path, int name) {
	errno = ENOSYS;
	return -1; /* not supported */
}
#endif

#ifdef F_readlink
ssize_t readlink(const char *path, char *buf, size_t bufsiz) {
	errno = ENOSYS;
	return -1; /* not supported */
}
#endif

#ifdef F_utime
struct utimbuf {
  time_t  actime;   /* Access time */
  time_t  modtime;  /* Modification time */
};

int utime(const char *pathname, const struct utimbuf *times)
{
	SceIoStat psp_stat;
	char dest[MAXNAMLEN + 1];
	int ret;

	if(__path_absolute(pathname, dest, MAXNAMLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	ret = sceIoGetstat(dest, &psp_stat);
	if (ret < 0) {
		return __set_errno(ret);
	}

	ret = sceRtcSetTime_t((pspTime *)&psp_stat.sce_st_atime, times->actime);
	if (ret < 0) {
		return __set_errno(ret);
	}

	ret = sceRtcSetTime_t((pspTime *)&psp_stat.sce_st_mtime, times->modtime);
	if (ret < 0) {
		return __set_errno(ret);
	}

	ret = sceIoChstat(dest, &psp_stat, 0x0030);
	if (ret < 0) {
		return __set_errno(ret);
	}
    
	return 0;
}
#endif

#ifdef F_fchown
int fchown(int fd, uid_t owner, gid_t group)
{
	errno = ENOSYS;
	return -1; /* not supported */
}
#endif

#ifdef F_getentropy
int getentropy(void *buffer, size_t length) {
	size_t i;
	SceKernelUtilsMt19937Context ctx;
	sceKernelUtilsMt19937Init(&ctx, time(NULL));
	uint8_t *source = (uint8_t *)buffer;
	for (i = 0; i < length; i++) {
		uint8_t rand_val = sceKernelUtilsMt19937UInt(&ctx) & 0xFF;
		source[i] = rand_val; 
	}

	return 0;
}
#endif

#ifdef F_getpwuid
struct passwd *getpwuid(uid_t uid) {
	/* There's no support for users */
	return NULL;
}
#endif

#ifdef F_getpwnam
struct passwd *getpwnam(const char *name) {
	/* There's no support for users */
	return NULL;
}
#endif

