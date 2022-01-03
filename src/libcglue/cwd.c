/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * cwd.c - The global init/deinit code for our crt0.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>
#include <dirent.h>
#include <errno.h>

#ifdef F___cwd
/* the present working directory variable. */
char __cwd[MAXNAMLEN + 1] = { 0 };
#else
extern char __cwd[MAXNAMLEN + 1];
#endif

#ifdef F___get_drive
/* Return the number of bytes taken up by the "drive:" prefix,
   or -1 if it's not found */
int __get_drive(const char *d)
{
	int i;
	for(i=0; d[i]; i++) {
		if(! ((d[i] >= 'a' && d[i] <= 'z') ||
		      (d[i] >= '0' && d[i] <= '9') ))
			break;
	}
	if(d[i] == ':') return i+1;
	return -1;
}
#else 
int __get_drive(const char *d);
#endif

#ifdef F_getcwd
char *getcwd(char *buf, size_t size)
{
	if(!buf) {
		errno = EINVAL;
		return NULL;
	}		

	if(strlen(__cwd) >= size) {
		errno = ERANGE;
		return NULL;
	}

	strcpy(buf, __cwd);
	return buf;
}
#endif

#ifdef F___path_absolute
/* Like strcpy, but returns 0 if the string doesn't fit */
static int __safe_strcpy(char *out, const char *in, int maxlen)
{
	for( ; maxlen > 0 && *in ; maxlen-- )
		*(out++) = *(in++);
	if(maxlen < 1) return 0;
	*out = 0;
	return 1;
}

/* Like strcat, but returns 0 if the string doesn't fit */
static int __safe_strcat(char *out, const char *in, int maxlen)
{
	for( ; *out ; out++,maxlen-- )
		continue;
	return __safe_strcpy(out, in, maxlen);
}

/* Normalize a pathname (without leading "drive:") by removing
   . and .. components, duplicated /, etc. */
static int __path_normalize(char *out, int len)
{
	int i, j;
	int first, next;

	/* First append "/" to make the rest easier */
	if(!__safe_strcat(out,"/",len)) return -10;

	/* Convert "//" to "/" */
	for(i=0; out[i+1]; i++) {
		if(out[i]=='/' && out[i+1]=='/') {
			for(j=i+1; out[j]; j++)
				out[j] = out[j+1];
			i--;
		}
	}

	/* Convert "/./" to "/" */
	for(i=0; out[i] && out[i+1] && out[i+2]; i++) {
		if(out[i]=='/' && out[i+1]=='.' && out[i+2]=='/') {
			for(j=i+1; out[j]; j++)
				out[j] = out[j+2];
			i--;
		}
	}

	/* Convert "/asdf/../" to "/" until we can't anymore.  Also
	 * convert leading "/../" to "/" */
	first = next = 0;
	while(1) {
		/* If a "../" follows, remove it and the parent */
		if(out[next+1] && out[next+1]=='.' && 
		   out[next+2] && out[next+2]=='.' &&
		   out[next+3] && out[next+3]=='/') {
			for(j=0; out[first+j+1]; j++)
				out[first+j+1] = out[next+j+4];
			first = next = 0;
			continue;
		}

		/* Find next slash */
		first = next;
		for(next=first+1; out[next] && out[next] != '/'; next++)
			continue;
		if(!out[next]) break;
	}

	/* Remove trailing "/" */
	for(i=1; out[i]; i++)
		continue;
	if(i >= 1 && out[i-1] == '/') 
		out[i-1] = 0;

	return 0;
}

/* Convert relative path to absolute path. */
int __path_absolute(const char *in, char *out, int len)
{
	int dr;

	/* See what the relative URL starts with */
	dr = __get_drive(in);
	if(dr > 0 && in[dr] == '/') {
		/* It starts with "drive:/", so it's already absolute */
		if(!__safe_strcpy(out, in, len))
			return -1;
	} else if(in[0] == '/') {
		/* It's absolute, but missing the drive, so use cwd's drive */
		if(strlen(__cwd) >= len)
			return -2;
		strcpy(out, __cwd);
		dr = __get_drive(out);
		out[dr] = 0;
		if(!__safe_strcat(out, in, len))
			return -3;
	} else {
		/* It's not absolute, so append it to the current cwd */
		if(strlen(__cwd) >= len)
			return -4;
		strcpy(out, __cwd);
		if(!__safe_strcat(out, "/", len)) 
			return -6;
		if(!__safe_strcat(out, in, len)) 
			return -7;
	}

	/* Now normalize the pathname portion */
	dr = __get_drive(out);
	if(dr < 0) dr = 0;
	return __path_normalize(out + dr, len - dr);
}
#endif

#ifdef F___init_cwd
/* Set the current working directory (CWD) to the path where the module was launched. */
void __init_cwd(char *argv_0)
{
	if (argv_0 != NULL) {
		char base_path[MAXPATHLEN + 1];
		char *end;

		strncpy(base_path, argv_0, sizeof(base_path) - 1);
		base_path[sizeof(base_path) - 1] = '\0';
		end = strrchr(base_path, '/');
		if (end != NULL) {
			*(end + 1) = '\0';
			chdir(base_path);
		}
	}
}
#endif