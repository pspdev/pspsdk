#ifndef __PSPPAF_H__
#define __PSPPAF_H

/**
 * sprintf
*/
int paf_sprintf(char * str, const char * format, ...);

/**
 * snprintf
*/
int paf_snprintf(char *str, int size, const char *format, ...);

/**
 * strcpy
*/
char *paf_strcpy(char *destination, const char *source);

/**
 * strncpy
*/
char *paf_strncpy(char *destination, const char *source, int num);

/**
 * strlen
*/
int paf_strlen(const char * str);

/**
 * memcmp
*/
void *paf_memcmp(void *s1, const void *s2, int n);

/**
 * memcpy
*/
void *paf_memcpy(void *s1, const void *s2, int n);

/**
 * memset
*/
void *paf_memset(void *s, int c, int n);

#endif


