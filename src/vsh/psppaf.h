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

/**
 * strtok_r
*/
char *paf_strtok_r(char *str, const char *delim, char **saveptr);

/**
 * malloc
*/
void *paf_malloc(int size);

/**
 * free
*/
void paf_free(void *);

/**
 * 
*/
int paf_wcslen(wchar_t *);

/**
 * strncpy
*/
char *paf_strncpy(char *, const char *, int);

/**
 * strcmp
*/
int paf_strcmp(const char *, const char *);

/**
 * strncmp
*/
int paf_strncmp(const char *, const char *, int);

/**
 * strchr
*/
char *paf_strchr(const char *, int);

/**
 * strrchr
*/
char *paf_strrchr(const char *, int);

/**
 * strpbrk
*/
char *paf_strpbrk(const char *, const char *);

/**
 * strtoul
*/
int paf_strtoul(const char *, char **, int);

/**
 * scePafGetText
*/
wchar_t *scePafGetText(void *, char *);

typedef struct
{
	u8 id;
	u8 type;
	u16 unk1;
	u32 label;
	u32 param;
	u32 first_child;
	int child_count;
	u32 next_entry;
	u32 prev_entry;
	u32 parent;
	u32 unknown[2];
} SceRcoEntry;

/**
 * PAF_Resource_GetPageNodeByID
*/
int PAF_Resource_GetPageNodeByID(void *, char *, SceRcoEntry **);

/**
 * PAF_Resource_ResolveRefWString
*/
int PAF_Resource_ResolveRefWString(void *, u32 *, int *, char **, int *);

#endif


