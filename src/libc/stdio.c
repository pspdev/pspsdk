/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * stdio.c - Simple standard C library implementation.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: stdio.c 2335 2007-11-06 07:47:36Z warren $
 */
#include <stdarg.h>
#include <stdio.h>
#include <psptypes.h>
#include <pspiofilemgr.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

/* std I/O buffer type constants. */
#define STD_IOBUF_TYPE_NONE            0
#define STD_IOBUF_TYPE_GE              1
#define STD_IOBUF_TYPE_MS			   2
#define STD_IOBUF_TYPE_UMD	           4
#define STD_IOBUF_TYPE_HOST            8
#define STD_IOBUF_TYPE_STDOUTHOST     16

#define _NFILE 16

#define _IOEOF                         0x0020
#define _IOERR                         0x0040

#define _IOREAD                        0x0001
#define _IOWRT                         0x0002
#define _IORW                          0x0200
#define _IOMYBUF                       0x0010

/* ensure FILE is defined. */
/* This is specific to psplibc, so we have to make sure it doesn't conflict with
   newlib's FILE definition. */;
/*
#ifndef __FILE_DEFINED
#define __FILE_DEFINED
*/
typedef struct {
        int  type;
        int  fd;
        int  cnt;
        int  flag;
        int  has_putback;
        u8   putback;
} __psplibc_FILE;
//#endif // __FILE_DEFINED

/* Override newlib's definition of a FILE. */
#define LOCAL_FILE(f) ((__psplibc_FILE *) (f))

extern FILE __iob[_NFILE];

/* Don't pull in macros from newlib's ctype.h that we don't support. */
int isdigit(int);

#ifdef F_clearerr
/* Get rid of the newlib macro definition. */
#ifdef clearerr
#undef clearerr
#endif
/*
**
**  [func] - clearerr.
**  [desc] - clears the stream file stream error condition.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**  [exit] - none.
**  [prec] - stream is a valid FILE pointer.
**  [post] - the stream file stream error condition is cleared.
**
*/
void clearerr(FILE *stream)
{
  LOCAL_FILE(stream)->flag &= (~_IOERR);
}
#endif


#ifdef F_fclose
/*
**
**  [func] - fclose.
**  [desc] - if stream is a valid FILE stream and able to close the stream file
**           then returns 0. else returns EOF.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**  [exit] - int; 0 if able to close the stream file. else EOF.
**  [prec] - stream is a valid FILE pointer.
**  [post] - the stream file is closed.
**
*/
int fclose(FILE *stream)
{
  int ret;

  /* test the file stream type. */
  switch(LOCAL_FILE(stream)->type) {
    case STD_IOBUF_TYPE_NONE:
    case STD_IOBUF_TYPE_GE:
    case STD_IOBUF_TYPE_STDOUTHOST:
      /* cannot close stdin, stdout, or stderr. */
      // duh.. this is wrong. One SHOULD be able to close
      // std*. That's a common unix doing. However, I doubt
      // allowing this madness could be a good idea.
      ret = EOF;
      break;
    default:
      if ((LOCAL_FILE(stream)->fd >= 0) && (sceIoClose(LOCAL_FILE(stream)->fd) >= 0)) {
        LOCAL_FILE(stream)->type = STD_IOBUF_TYPE_NONE;
        LOCAL_FILE(stream)->fd = -1;
        LOCAL_FILE(stream)->cnt = 0;
        LOCAL_FILE(stream)->flag = 0;
        ret = 0;
      }
      else ret = EOF;
  }
  return (ret);
}
#endif


#ifdef F_fcloseall
/*
**
**  [func] - fcloseall.
**  [desc] - attempts to close all the open files. if able to close all the open
**           files then returns the number of files closed. else returns -1.
**  [entr] - none.
**  [exit] - int; the number of files closed if successful. else -1.
**  [prec] - none.
**  [post] - all open non-system files are closed.
**
*/
int fcloseall(void)
{
  int  i, ret = 0;
  FILE *iob;

  /* process all open files except for stdout, stdin and stderr. */
  for (i = 3, iob = &__iob[3]; i < _NFILE; ++i, ++iob) {
    if (LOCAL_FILE(iob)->fd >= 0) {
      /* attempt to close the current file. */
      if ((fclose(iob) == 0) && (ret >= 0)) ++ret;
      else ret = EOF;
    }
  }
  return (ret);
}
#endif


#ifdef F_feof
/* Get rid of the newlib macro definition. */
#ifdef feof
#undef feof
#endif
/*
**
**  [func] - feof.
**  [desc] - if the stream file stream has reached the end of the file then
**           returns non-zero. else returns 0.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**  [exit] - int; non-zero if the stream file has reached EOF. else 0.
**  [prec] - stream is a valid FILE pointer.
**  [post] - none.
**
*/
int feof(FILE *stream)
{
  return ((LOCAL_FILE(stream)->flag & _IOEOF) != 0);
}
#endif


#ifdef F_ferror
/* Get rid of the newlib macro definition. */
#ifdef ferror
#undef ferror
#endif
/*
**
**  [func] - ferror.
**  [desc] - if an error has occured for the stream file stream then returns
**           non-zero. else returns 0.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**  [exit] - int; non-zero if error has occured for the stream file. else 0.
**  [prec] - stream is a valid FILE pointer.
**  [post] - none.
**
*/
int ferror(FILE *stream)
{
  return ((LOCAL_FILE(stream)->flag & _IOERR) != 0);
}
#endif


#ifdef F_fflush
int mcFlush(int fd);
int mcSync(int mode, int *cmd, int *result);

/*
**
**  [func] - fflush.
**  [desc] - if the stream file is opened as read-only then returns 0. else
**           if stream is a valid FILE stream and able to flush the stream
**           file write buffer then returns 0. else returns EOF.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**  [exit] - int; 0 if able to flush the write buffer or file is read-only. else EOF.
**  [prec] - stream is a valid FILE pointer.
**  [post] - the stream FILE stream write buffer is flushed.
**
*/
int fflush(FILE *stream)
{
  int ret = EOF; // Same as default case below.

  switch(LOCAL_FILE(stream)->type) {
    case STD_IOBUF_TYPE_GE:
    case STD_IOBUF_TYPE_STDOUTHOST:
      /* stdout & stderr are never buffered. */
    case STD_IOBUF_TYPE_UMD:
      /* cd-rom files are read-only so no write buffer to flush. */
      ret = 0;
      break;
    case STD_IOBUF_TYPE_MS:
      if (LOCAL_FILE(stream)->flag & (_IOWRT | _IORW)) {
        //if (ret != 0) ret = EOF;
		  /* Need to implement sync or something */
      }
      else ret = 0;
      break;
    case STD_IOBUF_TYPE_HOST:
      /* flush host file write buffer. */
      if (LOCAL_FILE(stream)->flag & (_IOWRT | _IORW)) ret = 0;
      else ret = 0;
      break;
    default:
      /* unknown/invalid I/O buffer type. */
      ret = EOF;
  }
  return (ret);
}
#endif


#ifdef F_fflushall
/*
**
**  [func] - _fcloseall.
**  [desc] - attempts to flush all the open files with write-access. if able
**           to flush all the open files with write-access then returns the
**           number of files flushed. else returns -1.
**  [entr] - none.
**  [exit] - int; the number of files flushed if successful. else -1.
**  [prec] - none.
**  [post] - all open non-system files with write-access are flushed.
**
*/
int _fflushall(void)
{
  int  i, ret = 0;
  FILE *iob;

  /* process all open files except for stdout, stdin and stderr. */
  for (i = 3, iob = &__iob[3]; i < _NFILE; ++i, ++iob) {
    if (LOCAL_FILE(iob)->fd >= 0) {
      /* attempt to flush the current file. */
      if ((fflush(iob) == 0) && (ret >= 0)) ++ret;
      else ret = EOF;
    }
  }
  return (ret);
}
#endif


#ifdef F_fgetc
/*
**
**  [func] - fgetc.
**  [desc] - attempts to read one character from the stream file. if able to
**           read one character from the file then returns the chaaracter
**           read. else EOF.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**  [exit] - int; the character read from the stream file. else -1.
**  [prec] - stream is a valid FILE pointer.
**  [post] - the stream file is modified.
**
*/
int fgetc(FILE *stream)
{
  char c;
  int  ret;

  if (LOCAL_FILE(stream)->has_putback) {
    LOCAL_FILE(stream)->has_putback = 0;
    return LOCAL_FILE(stream)->putback;
  }

  switch(LOCAL_FILE(stream)->type) {
    case STD_IOBUF_TYPE_GE:
    case STD_IOBUF_TYPE_STDOUTHOST:
      /* cannot read from stdout or stderr. */
      ret = EOF;
      break;
    default:
      ret = ((fread(&c, 1, 1, stream) == 1) ? (int)c : EOF);
  }
  return (ret);
}
#endif


#ifdef F_fgetpos
/*
**
**  [func] - fgetpos.
**  [desc] - attempts to retrieve the stream file stream pointer position.
**           if able to retrieve the stream file stream pointer position
**           then stores the position to pos and returns 0. else returns -1.
**  [entr] - FILE *stream; the pointer to the file stream.
**           fpos_t *pos; the pointer to the destination file position buffer.
**  [exit] - int; 0 if able to retrieve the stream file pointer position. else -1.
**  [prec] - stream is a valid FILE pointer and pos is a valid fpos_t pointer.
**  [post] - the memory pointed to by pos is modified.
**
*/
int fgetpos(FILE *stream, fpos_t *pos)
{
  long n;

  if ((n = ftell(stream)) >= 0) *pos = (fpos_t)n;
  return ((n >= 0) ? 0 : -1);
}

int fgetpos64(FILE *stream, int64_t *pos)
{
  int64_t n;

  if ((n = ftello64(stream)) >= 0) *pos = n;
  return ((n >= 0) ? 0 : -1);
}
#endif


#ifdef F_fgets
/*
**
**  [func] - fgets.
**  [desc] - attempts to read a string from the stream file. if able to read
**           a string from the stream file stdin then stores the string up to
**           n characters to the memory pointed by buf and returns buf. else
**           returns NULL.
**  [entr] - char *buf; the pointer to the destination string buffer.
**           int n; the maximum number of characters to write to buf.
**           FILE *stream; the pointer to the FILE stream.
**  [exit] - char *; buf if the string is read successfully. else NULL.
**  [prec] - buf is a valid memory pointer of n size in bytes and stream is a
**           valid FILE pointer.
**  [post] - the memory pointed to by buf is modified and the stream file
**           pointer is modified.
**
*/
char *fgets(char *buf, int n, FILE *stream)
{
  char *ret = buf;
  int  c, done;

  switch(LOCAL_FILE(stream)->type) {
    case STD_IOBUF_TYPE_GE:
    case STD_IOBUF_TYPE_STDOUTHOST:
      /* cannot read from stdout or stderr. */
      ret = NULL;
      break;
    default:
      for (done = 0; (!done); ) {
        switch(c = fgetc(stream)) {
          case '\r':
          case '\n':
            if (n > 0) {
              /* newline terminates fgets. */
              *buf++ = '\0';
              --n;
              done = 1;
              break;
            }
            break;
          case EOF:
            /* end of file or error. */
            ret = NULL;
            done = 1;
            break;
          default:
            if (n > 0) {
              /* store the current character to buf. */
              *buf++ = (char)c;
              --n;
            }
        }
      }
  }
  return (ret);
}
#endif


#ifdef F_fopen
/* std I/O internal function. */
int __stdio_get_fd_type(const char *);

/*
**
**  [func] - fopen.
**  [desc] - attempts to open the fname file using the mode file mode. if able
**           open the fname then returns the pointer to the FILE stream. else
**           returns NULL.
**  [entr] - const char *fname; the filename string pointer.
**           const char *mode; the file mode string pointer.
**  [exit] - FILE *; the pointer the fname FILE stream. else NULL.
**  [prec] - fname and mode are valid string pointers.
**  [post] - the fname file is opened.
**
*/
FILE *fopen(const char *fname, const char *mode)
{
  FILE *ret = NULL;
  int  fd, flag = 0, i, iomode = 0;

  /* ensure file name and mode are not NULL strings. */
  if ((fname != NULL) && (*fname != '\0')) {
    if ((mode != NULL) && (*mode != '\0')) {
      /* test the file mode. */
      switch(*mode++) {
        case 'r':
          flag = _IOREAD;
          iomode = PSP_O_RDONLY;
          break;
        case 'w':
          flag = _IOWRT;
          iomode = (PSP_O_WRONLY | PSP_O_CREAT);
          break;
        case 'a':
          flag = _IORW;
          iomode = PSP_O_APPEND;
          break;
      }
      /* test the extended file mode. */
      for (; (*mode++ != '\0'); ) {
        switch(*mode) {
          case 'b':
            continue;
          case '+':
            flag |= (_IOREAD | _IOWRT);
            iomode |= (PSP_O_RDWR | PSP_O_CREAT | PSP_O_TRUNC);
            continue;
          default:
            break;
        }
      }
      /* search for an available fd slot. */
      for (i = 2; i < _NFILE; ++i) if (LOCAL_FILE(&__iob[i])->fd < 0) break;
      if (i < _NFILE) {
        /* attempt to open the fname file. */
        if ((fd = sceIoOpen((char *)fname, iomode, 0777)) >= 0) {
          LOCAL_FILE(&__iob[i])->type = __stdio_get_fd_type(fname);
          LOCAL_FILE(&__iob[i])->fd = fd;
          LOCAL_FILE(&__iob[i])->cnt = 0;
          LOCAL_FILE(&__iob[i])->flag = flag;
          LOCAL_FILE(&__iob[i])->has_putback = 0;
          ret = (__iob + i);
        }
      }
    }
  }
  return (ret);
}

FILE *fopen64(const char *fname, const char *mode) {
	return fopen(fname, mode);
}

#endif

#ifdef F_fdopen
/*
**
**  [func] - fdopen.
**  [desc] - produces a file descriptor of type `FILE *', from a 
**           descriptor for an already-open file (returned, for 
**           example, by the system subroutine `open' rather than by `fopen').
**           The MODE argument has the same meanings as in `fopen'.
**  [entr] - int fd; file descriptor returned by 'open'.
**           const char *mode; the file mode string pointer.
**  [exit] - file pointer or `NULL', as for `fopen'.
**
*/
FILE *fdopen(int fd, const char *mode)
{
  FILE *ret = NULL;
  int  flag = 0, i, iomode = 0;

  /* ensure valid descriptor, and that mode is not a NULL string. */
  if (fd >= 0) {
    if ((mode != NULL) && (*mode != '\0')) {
      /* test the file mode. */
      switch(*mode++) {
        case 'r':
          flag = _IOREAD;
          iomode = PSP_O_RDONLY;
          break;
        case 'w':
          flag = _IOWRT;
          iomode = (PSP_O_WRONLY | PSP_O_CREAT);
          break;
        case 'a':
          flag = _IORW;
          iomode = PSP_O_APPEND;
          break;
      }
      /* test the extended file mode. */
      for (; (*mode++ != '\0'); ) {
        switch(*mode) {
          case 'b':
            continue;
          case '+':
            flag |= (_IOREAD | _IOWRT);
            iomode |= (PSP_O_RDWR | PSP_O_CREAT | PSP_O_TRUNC);
            continue;
          default:
            break;
        }
      }
      /* search for an available fd slot. */
      for (i = 2; i < _NFILE; ++i) if (LOCAL_FILE(&__iob[i])->fd < 0) break;
      if (i < _NFILE) {
        /* attempt to open the fname file. */
        LOCAL_FILE(&__iob[i])->type = STD_IOBUF_TYPE_NONE;
        LOCAL_FILE(&__iob[i])->fd = fd;
        LOCAL_FILE(&__iob[i])->cnt = 0;
        LOCAL_FILE(&__iob[i])->flag = flag;
        LOCAL_FILE(&__iob[i])->has_putback = 0;
        ret = (__iob + i);
      }
    }
  }
  return (ret);
}
#endif

#ifdef F_fileno
int fileno(FILE * f) {
    return LOCAL_FILE(f)->fd;
}
#endif

#ifdef F_fputc
/*
**
**  [func] - fputc.
**  [desc] - attempts to write the c character to the stream file. if able to
**           write the character to the stream file then returns the character
**           written. else returns -1.
**  [entr] - int c; the character to write to the file.
**           FILE *stream; the pointer to the FILE stream.
**  [exit] - int; the character written to the file if successful. else -1.
**  [prec] - stream is a valid FILE pointer.
**  [post] - the stream file is modified.
**
*/
int fputc(int c, FILE *stream)
{
  char ch;

  ch = (char)c;
  return ((fwrite(&ch, 1, 1, stream) == 1) ? 0 : EOF);
}
#endif


#ifdef F_fputs
/*
**
**  [func] - fputs.
**  [desc] - attempts to write the s string to the stream file. if able to
**           successfully write the string to the stream file then returns
**           the number of characters written to the file. else returns -1.
**  [entr] - const char *s; the source string pointer.
**  [exit] - int; the number of chars. written to file if successful. else -1.
**  [prec] - stream is a valid FILE pointer and s is a valid string pointer.
**  [post] - the stream file is modified.
**
*/
int fputs(const char *s, FILE *stream)
{
  size_t len;

  int temp = strlen(s);

  len = ((fwrite(s, 1, temp, stream) == temp) ? temp : EOF);

  if (len != EOF) {
    fputc('\n', stream);
  }
  return len + 1;
}
#endif


#ifdef F_fread
/*
**
**  [func] - fread.
**  [desc] - attempts to read n number of records of r size to the stream file
**           and returns the number of records successfully read from the file.
**  [entr] - void *buf; the pointer to the destination data buffer.
**           size_t r; the size of the records to read.
**           size_t n; the number of records to read.
**           FILE *stream; the pointer to the FILE stream.
**  [exit] - size_t; the number of records successfully read from the stream file.
**  [prec] - buf is a valid memory pointer of (r * n) size in bytes and stream
**           is a valid FILE pointer.
**  [post] - the stream file is modified.
**
*/
size_t fread(void *buf, size_t r, size_t n, FILE *stream)
{
  size_t ret;

  switch(LOCAL_FILE(stream)->type) {
    case STD_IOBUF_TYPE_NONE:
    case STD_IOBUF_TYPE_GE:
    case STD_IOBUF_TYPE_STDOUTHOST:
      /* cannot read from stdout or stderr. */
      ret = 0;
      break;
    default:
      /* attempt to read from the stream file. */
      ret = (sceIoRead(LOCAL_FILE(stream)->fd, buf, (int)(r * n)) / (int)r);
  }
  return (ret);
}
#endif


#ifdef F_fseek

/*
**
**  [func] - fseek.
**  [desc] - attempts to seek the stream file pointer to offset from origin.
**           if able to seek the stream file pointer to offset from origin
**           returns 0. else returns -1.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**           long offset; the seek offset.
**           int origin; the seek origin.
**  [exit] - int; 0 if able to seek to offset from origin successfully. else -1.
**  [prec] - stream is a valid FILE pointer and origin is a valid seek origin
**           type.
**  [post] - the stream file pointer position is modified.
**
*/
int fseeko64(FILE *stream, int64_t offset, int origin)
{
  int ret;

  switch(LOCAL_FILE(stream)->type) {
    case STD_IOBUF_TYPE_NONE:
    case STD_IOBUF_TYPE_GE:
    case STD_IOBUF_TYPE_STDOUTHOST:
      /* cannot seek stdout or stderr. */
      ret = -1;
      break;
    default:
      /* attempt to seek to offset from origin. */
      ret = ((sceIoLseek(LOCAL_FILE(stream)->fd, offset, origin) >= 0) ? 0 : -1);
  }
  return (ret);
}

int fseek(FILE *stream, long offset, int origin)
{
	return fseeko64(stream, (int64_t)offset, origin);
}
#endif


#ifdef F_fsetpos
/*
**
**  [func] - fsetpos.
**  [desc] - attempts to set the stream file pointer position to the pos offset.
**           if able to set the stream file pointer position to pos then returns
**           0. else returns -1.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**           const fpos_t *pos; the pointer to the source file position buffer.
**  [exit] - 0 if able to set the stream file pointer position. else -1.
**  [prec] - stream is a valid FILE pointer and pos is a valid fpos_t pointer.
**  [post] - the stream file pointer position is modified.
**
*/
int fsetpos(FILE *stream, const fpos_t *pos)
{
  return (fseek(stream, (long)*pos, SEEK_SET));
}
#endif


#ifdef F_ftell
/*
**
**  [func] - ftell.
**  [desc] - attempts to retrieve the stream file stream pointer position.
**           if able to retrieve the stream file stream pointer position
**           then returns the position. else sets error code and returns -1.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**  [exit] - long; the stream file pointer position if successful. else -1.
**  [prec] - stream is a valid FILE pointer.
**  [post] - none.
**
*/
long ftell(FILE *stream)
{
  long n, ret;

  switch(LOCAL_FILE(stream)->type) {
    case STD_IOBUF_TYPE_NONE:
    case STD_IOBUF_TYPE_GE:
    case STD_IOBUF_TYPE_STDOUTHOST:
      /* stdout or stderr is an invalid seek stream argument. */
      errno = EINVAL;
      ret = -1L;
      break;
    default:
      if (LOCAL_FILE(stream)->fd < 0) {
        /* file is not open. */
        errno = EBADF;
        ret = -1L;
      }
      else ret = (((n = sceIoLseek(LOCAL_FILE(stream)->fd, 0, SEEK_CUR)) >= 0) ? (long)n : -1L);
  }
  return (ret);
}

int64_t ftello64(FILE *stream)
{
  int64_t n, ret;

  switch(LOCAL_FILE(stream)->type) {
    case STD_IOBUF_TYPE_NONE:
    case STD_IOBUF_TYPE_GE:
    case STD_IOBUF_TYPE_STDOUTHOST:
      /* stdout or stderr is an invalid seek stream argument. */
      errno = EINVAL;
      ret = -1L;
      break;
    default:
      if (LOCAL_FILE(stream)->fd < 0) {
        /* file is not open. */
        errno = EBADF;
        ret = -1L;
      }
      else ret = (((n = sceIoLseek(LOCAL_FILE(stream)->fd, 0, SEEK_CUR)) >= 0) ? (int64_t)n : -1);
  }
  return (ret);
}
#endif


#ifdef F_fwrite
/*
**
**  [func] - fwrite.
**  [desc] - attempts to write n number of records of r size to the stream file
**           and returns the number of records successfully written to the file.
**  [entr] - const void *buf; the pointer to the source data buffer.
**           size_t r; the size of the records to write.
**           size_t n the number of records to write.
**           FILE *stream; the pointer to the FILE stream.
**  [exit] - size_t; the number of records successfully written to the stream file.
**  [prec] - buf is a valid memory pointer of (r * n) size in bytes and stream
**           is a valid FILE pointer.
**  [post] - the stream file is modified.
**
*/
size_t fwrite(const void *buf, size_t r, size_t n, FILE *stream)
{
  size_t ret;

  /* attempt to write the stream file. */
  //ret = (sceIoWrite(stream->fd, (void *)buf, (int)(r * n)) / (int)r);
  ret = (sceIoWrite(LOCAL_FILE(stream)->fd, (void *)buf, (int)(r * n)) / (int) r);

  return (ret);
}
#endif


#ifdef F_getc
/* Get rid of the newlib macro definition. */
#ifdef getc
#undef getc
#endif
/*
**
**  [func] - getc.
**  [desc] - attempts to read one character from the stream file. if able to
**           read one character from the file then returns the chaaracter
**           read. else EOF.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**  [exit] - int; the character read from the stream file. else -1.
**  [prec] - stream is a valid FILE pointer.
**  [post] - the stream file is modified.
**
*/
int getc(FILE *stream)
{
  char c;
  int  ret;

  switch(LOCAL_FILE(stream)->type) {
    case STD_IOBUF_TYPE_NONE:
    case STD_IOBUF_TYPE_GE:
    case STD_IOBUF_TYPE_STDOUTHOST:
      /* cannot read from stdout or stderr. */
      ret = EOF;
      break;
    default:
      ret = ((fread(&c, 1, 1, stream) == 1) ? (int)c : EOF);
  }
  return (ret);
}
#endif


#ifdef F_getchar
/* Get rid of the newlib macro definition. */
#ifdef getchar
#undef getchar
#endif
/* We can't use the macro version of getc provided in newlib's stdio.h. */
#ifdef getc
#undef getc
#endif
/*
**
**  [func] - getchar.
**  [desc] - attempts to read one character from the stdin file stream. if able
**           to read one character from the stdin file stream then returns the
**           character read. else returns -1.
**  [entr] - none.
**  [exit] - int; the character read from stdin if successful. else -1.
**  [prec] - none.
**  [post] - the stdin file stream is modified.
**
*/
int getchar(void)
{
  return (getc(stdin));
}
#endif


#ifdef F_getfdtype
/* the present working directory variable. */
#if 0
char __direct_pwd[256];
#endif

/*
**
**  [func] - __stdio_get_fd_type.
**  [desc] - if s or the present working directory begins with a valid file
**           device name then returns the corresponding file descriptor type.
**           else returns -1.
**  [entr] - const char *s; the source string pointer.
**  [exit] - int; the device name file descriptor type if determined. else -1.
**  [prec] - s is a valid string pointer.
**  [post] - none.
**
*/
int __stdio_get_fd_type(const char *s)
{
  return (-1);
}
#endif


#ifdef F_gets
/*
**
**  [func] - gets.
**  [desc] - attempts to read a string from stdin. if able to read a string
**           from stdin then stores the string to the memory pointed by buf
**           and returns buf. else returns NULL.
**  [entr] - char *buf; the pointer to the destination string buffer.
**  [exit] - char *; buf if string is read successfully. else NULL.
**  [prec] - buf is a valid memory pointer.
**  [post] - the memory pointed to by buf is modified.
**
*/
char *gets(char *buf)
{
  return (fgets(buf, INT_MAX, stdin));
}
#endif


#ifdef F_strerror
static const char * file_errors[] = {
"",										//	0
"Not super-user",								//	1
"No such file or directory",						//	2
"No such process",							//	3
"Interrupted system call",						//	4
"I/O error",								//	5
"No such device or address",						//	6
"Arg list too long",							//	7
"Exec format error",							//	8
"Bad file number",							//	9
"No children",								//	10
"No more processes",							//	11
"Not enough core",							//	12
"Permission denied",							//	13
"Bad address",								//	14
"Block device required",						//	15
"Mount device busy",							//	16
"File exists",								//	17
"Cross-device link",							//	18
"No such device",								//	19
"Not a directory",							//	20
"Is a directory",								//	21
"Invalid argument",							//	22
"Too many open files in system",					//	23
"Too many open files",							//	24
"Not a typewriter",							//	25
"Text file busy",								//	26
"File too large",								//	27
"No space left on device",						//	28
"Illegal seek",								//	29
"Read only file system",						//	30
"Too many links",								//	31
"Broken pipe",								//	32
"Math arg out of domain of func",					//	33
"Math result not representable",					//	34
"No message of desired type",						//	35
"Identifier removed",							//	36
"Channel number out of range",					//	37
"Level 2 not synchronized",						//	38
"Level 3 halted",								//	39
"Level 3 reset",								//	40
"Link number out of range",						//	41
"Protocol driver not attached",					//	42
"No CSI structure available",						//	43
"Level 2 halted",								//	44
"Deadlock condition",							//	45
"No record locks available",						//	46
"",										//	47
"",										//	48
"",										//	49
"Invalid exchange",							//	50
"Invalid request descriptor",						//	51
"Exchange full",								//	52
"No anode",									//	53
"Invalid request code",							//	54
"Invalid slot",								//	55
"File locking deadlock error",					//	56
"Bad font file fmt",							//	57
"",										//	58
"",										//	59
"Device not a stream",							//	60
"No data (for no delay io)",						//	61
"Timer expired",								//	62
"Out of streams resources",						//	63
"Machine is not on the network",					//	64
"Package not installed",						//	65
"The object is remote",							//	66
"The link has been severed",						//	67
"Advertise error",							//	68
"Srmount error",								//	69
"Communication error on send",					//	70
"Protocol error",								//	71
"",										//	72
"",										//	73
"Multihop attempted",							//	74
"Inode is remote (not really error)",				//	75


"Cross mount point (not really error)",				//	76
"Trying to read unreadable message",				//	77
"",										//	78
"Inappropriate file type or format",				//	79
"Given log. name not unique",						//	80
"f.d. invalid for this operation",					//	81
"Remote address changed",						//	82
"Can't access a needed shared lib",					//	83
"Accessing a corrupted shared lib",					//	84
".lib section in a.out corrupted",					//	85
"Attempting to link in too many libs",				//	86
"Attempting to exec a shared library",				//	87
"Function not implemented",						//	88
"No more files",								//	89
"Directory not empty",							//	90
"File or path name too long",						//	91
"Too many symbolic links",						//	92
"",										//	93
"",										//	94
"Operation not supported on transport endpoint",		//	95
"Protocol family not supported",					//	96
"",										//	97
"",										//	98
"",										//	99
"",										//	100
"",										//	101
"",										//	102
"",										//	103
"Connection reset by peer",						//	104
"No buffer space available",						//	105
"Address family not supported by protocol family",		//	106
"Protocol wrong type for socket",					//	107
"Socket operation on non-socket",					//	108
"Protocol not available",						//	109
"Can't send after socket shutdown",					//	110
"Connection refused",							//	111
"Address already in use",						//	112
"Connection aborted",							//	113
"Network is unreachable",						//	114
"Network interface is not configured",				//	115
"Connection timed out",							//	116
"Host is down",								//	117
"Host is unreachable",							//	118
"Connection already in progress",					//	119
"Socket already connected",						//	120
"Destination address required",					//	121
"Message too long",							//	122
"Unknown protocol",							//	123
"Socket type not supported",						//	124
"Address not available",						//	125
"",										//	126
"Socket is already connected",					//	127
"Socket is not connected",						//	128
"",										//	129
"EPROCLIM",									//	130
"EUSERS",									//	131
"EDQUOT",									//	132
"ESTALE",									//	133
"Not supported",								//	134
"No medium (in tape drive)",						//	135
"No such host or network path",					//	136
"Filename exists with different case",				//	137
"EILSEQ",									//	138
"Value too large for defined data type",				//	139
""};
#define error_to_string(errnum) (file_errors[errnum*-1])

char * strerror(int err) {
    return (char *) error_to_string(err);
}
#endif


#ifdef F_perror
/*
**
**  [func] - perror.
**  [desc] - if there is a current error then prints the corresponding error
**           and then prints s to stderr. else prints s to stderr.
**  [entr] - const char *s; the error string pointer.
**  [exit] - none.
**  [prec] - s is a valid string pointer.
**  [post] - none.
**
*/
void perror(const char *s)
{
  char *err;

  /* print to stderr output. */
  if ((err = strerror(errno)) != NULL) fprintf(stderr, "%s : ", err);
  fputs(s, stderr);
}
#endif


#ifdef F_putc
/* Get rid of the newlib macro definition. */
#ifdef putc
#undef putc
#endif
/* std I/O data variable. */
#ifdef USE_GS
extern int __stdio_stdout_xy[2];


/* stdio internal function. */
void __stdio_update_stdout_xy(int, int);
#endif

/*
**
**  [func] - putc.
**  [desc] - attempts to write the c character to the stream file. if able to
**           write the character to the stream file then returns the character
**           written. else returns -1.
**  [entr] - int c; the character to write to the file.
**           FILE *stream; the pointer to the FILE stream.
**  [exit] - int; the character written to the file if successful. else -1.
**  [prec] - stream is a valid FILE pointer.
**  [post] - the stream file is modified.
**
*/
int putc(int c, FILE *stream)
{
  char ch;
  int  ret = 0;

  switch(LOCAL_FILE(stream)->type) {
      break;
    default:
      /* write one character to the stream file. */
      ch = (char)c;
      ret = ((fwrite(&ch, 1, 1, stream) == 1) ? c : EOF);
  }
  return (ret);
}
#endif


#ifdef F_putchar
/* We can't use the macro version of putc provided in newlib's stdio.h. */
#ifdef putc
#undef putc
#endif
/*
**
**  [func] - putchar.
**  [desc] - attempts to write the c character to stdout. if able to write
**           the character to stdout then returns the character written.
**           else returns -1.
**  [entr] - int c; the character to write to stdout.
**  [exit] - int; the character written to stdout. else -1.
**  [prec] - none.
**  [post] - the stdout file stream is modified.
**
*/
int putchar(int c)
{
  return (putc(c, stdout));
}
#endif


#ifdef F_puts
/* We can't use the macro version of putc provided in newlib's stdio.h. */
#ifdef putc
#undef putc
#undef putchar
#endif
/*
**
**  [func] - puts.
**  [desc] - attempts to write the s string to stdout. if able to write the s
**           string to stdout then returns the number of characters written.
**           else returns -1.
**  [entr] - const char *s; the source string pointer.
**  [exit] - int; the number of characters written to stdout. else -1.
**  [prec] - s is a valid string pointer.
**  [post] - the stdout file stream is modified.
**
*/
int puts(const char *s)
{
  int ret;

  for (ret = 0; (*s != '\0'); ++s) {
    /* attempt to print the current character to stdout. */
    if ((putchar(*s) == (int)*s) && (ret >= 0)) ++ret;
    else ret = EOF;
  }
  if ((putchar('\n') == '\n') && (ret >= 0)) ++ret;
  else ret = EOF;
  return (ret);
}
#endif


#ifdef F_remove
/*
**
**  [func] - remove.
**  [desc] - if the s named file exists then deletes the s named file and
**           returns 0. else returns -1.
**  [entr] - const char *s; the filename string pointer.
**  [exit] - int; 0 if able to delete the s file. else -1.
**  [prec] - s is a valid string pointer.
**  [post] - the s file is deleted.
**
*/
int remove(const char *s)
{
	int ret = sceIoRemove(s);

	return (ret);
}
#endif


#ifdef F_rename
/*
**
**  [func] - rename.
**  [desc] -
**  [entr] - const char *name; the filename string pointer.
**           const char *newname; the new filename string pointer.
**  [exit] - int;
**  [prec] - name and newname are valid string pointers.
**  [post] - the name filen name is modified.
**
*/
int rename(const char *name, const char *newname)
{
	int ret = sceIoRename(name, newname);
	
	return (ret);
}
#endif


#ifdef F_rewind
/*
**
**  [func] - rewind.
**  [desc] - resets the stream file pointer to 0.
**  [entr] - FILE *stream; the pointer to the FILE stream.
**  [exit] - none.
**  [prec] - stream is a valid FILE pointer.
**  [post] - the stream file pointer is modified.
**
*/
void rewind(FILE *stream)
{
  fseek(stream, 0, SEEK_SET);
}
#endif


#ifdef F_skipatoi
/*
**
**  [func] - __stdio_skip_atoi.
**  [desc] -
**  [entr] - const char **s; the pointer to the source string pointer.
**  [exit] - int;
**  [prec] - s is a valid pointer to string pointer.
**  [post] - the memory pointed to by s is modified.
**
*/
int __stdio_skip_atoi(const char **s)
{
  int ret = 0;

  for (; (isdigit(**s) != 0); ) ret = ((ret * 10) + (*((*s)++) - '0'));
  return (ret);
}
#endif

//Do not uncomment until vsscanf is implemented - Warren
//#ifdef F_sscanf
/*
**
**  [func] - sscanf.
**  [desc] -
**  [entr] - const char *buf;
**           const char *format; the format string pointer.
**           ...;
**  [exit] - int;
**  [prec] - buf and format are valid string pointers.
**  [post] - the memory pointed to by format string arguments are
**
*/
/*
int sscanf(const char *buf, const char *format, ...)
{
  int     ret;
  va_list va;

  va_start(va, format);
  ret = vsscanf(buf, format, va);
  va_end(va);
  return (ret);
}*/
//#endif


#ifdef F__stdio
/* stdio data variables. */
FILE __iob[_NFILE] = {
  { -1,                 0, 0, 0 },     // stdin
  { STD_IOBUF_TYPE_STDOUTHOST, 1, 0, 0 }, // stdout
  { STD_IOBUF_TYPE_STDOUTHOST, 2, 0, 0 }, // stdout
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 },
  { 0, -1, 0, 0 }
};
char __stdio_tmpnam[256];
#ifdef USE_GS
int  __stdio_stdout_xy[2];
#endif
#endif


#ifdef F_tmpfile
/* stdio temp name variable. */
extern char __stdio_tmpnam[256];


/*
**
**  [func] - tmpfile.
**  [desc] - attempts to create a temporary file. if able to create a temporary
**           file then returns the pointer to the FILE stream. else returns NULL.
**  [entr] - none.
**  [exit] - FILE *; the ptr. to the opened temp. file if successful. else NULL.
**  [prec] - none.
**  [post] - a temporary is opened.
**
*/
FILE *tmpfile(void)
{
  return ((tmpnam(NULL) != NULL) ?  fopen(__stdio_tmpnam, "rw+") : NULL);
}
#endif


#ifdef F_tmpnam
/* stdio temp name variable. */
extern char __stdio_tmpnam[256];


/*
**
**  [func] - tmpnam.
**  [desc] - creates a temporary filename string, 
**  [entr] - char *name; the pointer to the destination string pointer.
**  [exit] - char *;
**  [prec] -
**  [post] -
**
*/
char *tmpnam(char *name)
{
  char *ret = NULL;

  return (ret);
}
#endif


#ifdef F_ungetc
/*
**
**  [func] - ungetc.
**  [desc] -
**  [entr] - int c;
**           FILE *stream; the pointer to the FILE stream.
**  [exit] - int;
**  [prec] - stream is a valid FILE pointer.
**  [post] - the stream FILE stream is modified.
**
*/
int ungetc(int c, FILE *stream)
{
  // int ret = EOF;

  if (c == EOF || LOCAL_FILE(stream)->has_putback) {
    /* invalid input, or putback queue full */
    return EOF;
  }

  LOCAL_FILE(stream)->putback = (u8)c;
  LOCAL_FILE(stream)->has_putback = 1;
  return c;
}
#endif


#ifdef F_updatestdoutxy
/* std I/O data variable. */
#ifdef USE_GS
extern int __stdio_stdout_xy[2];
#endif

/*
**
**  [func] - __stdio_update_stdout_xy.
**  [desc] - updates the stdout (x, y) screen coordinates.
**  [entr] - int x; the x screen coordinate.
**           int y; the y screen coordinate.
**  [exit] - none.
**  [prec] - none.
**  [post] - the stdout screen coordinates are modified.
**
*/
void __stdio_update_stdout_xy(int x, int y)
{
#ifdef USE_GS
  if ((x * 16) >= gsGetDisplayWidth()) {
    x = 0;
    ++y;
  }
  if ((y * 16) >= gsGetDisplayHeight()) y = 0;
  __stdio_stdout_xy[0] = x;
  __stdio_stdout_xy[1] = y;
#endif
}
#endif


#ifdef F___stdio_internals
void _pspsdk_stdio_init()
{
}

void _pspsdk_stdio_deinit()
{
}
#endif
