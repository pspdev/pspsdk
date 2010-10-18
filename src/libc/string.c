/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * string.c - Standard ANSI string functions to complement the ASM funcs
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: string.c 1710 2006-01-17 01:24:53Z jim $
 */
#include <psptypes.h>
#include <limits.h>
#include <string.h>
#include <malloc.h>

/* Until a _ctype_ array exists in psplibc, don't include ctype.h and declare ctype.h
   function prototypes. */
int isalnum(int);
int isalpha(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int tolower(int);
int toupper(int);

#ifdef F_strlen
unsigned int strlen(const char *s)
{
	int len = 0;
	while(*s)
	{
		s++;
		len++;
	}

	return len;
}
#endif

#ifdef F_strcat
char *strcat(char *s, const char *append)
{
	char *pRet = s;
	while(*s)
	{
		s++;
	}

	while(*append)
	{
		*s++ = *append++;
	}

	*s = 0;

	return pRet;
}
#endif

#ifdef F_strncat
char *strncat(char *s, const char *append, size_t count)
{
	char *pRet = s;

	while(*s)
	{
		s++;
	}

	while((*append) && (count > 0))
	{
		*s++ = *append++;
		count--;
	}

	*s = 0;

	return pRet;
}
#endif

#ifdef F_strcmp
int strcmp(const char *s1, const char *s2)
{
	int val = 0;
	const unsigned char *u1, *u2;

	u1 = (unsigned char *) s1;
	u2 = (unsigned char *) s2;

	while(1)
	{
		if(*u1 != *u2)
		{
			val = (int) *u1 - (int) *u2;
			break;
		}

		if((*u1 == 0) && (*u2 == 0))
		{
			break;
		}

		u1++;
		u2++;
	}

	return val;
}
#endif

#ifdef F_strncmp
int strncmp(const char *s1, const char *s2, size_t count)
{
	int val = 0;
	const unsigned char *u1, *u2;

	u1 = (unsigned char *) s1;
	u2 = (unsigned char *) s2;

	while(count > 0)
	{
		if(*u1 != *u2)
		{
			val = (int) *u1 - (int) *u2;
			break;
		}

		if((*u1 == 0) && (*u2 == 0))
		{
			break;
		}

		u1++;
		u2++;
		count--;
	}

	return val;
}
#endif

#ifdef F_strcpy
char *strcpy(char *dst, const char *src)
{
	char *pRet = dst;

	while(*src)
	{
		*dst++ = *src++;
	}

	*dst = 0;

	return pRet;
}
#endif

#ifdef F_strncpy
char *strncpy(char *dst, const char *src, size_t count)
{
	char *pRet = dst;

	while(count > 0)
	{
		if(*src)
		{
			*dst++ = *src++;
		}
		else
		{
			*dst++ = 0;
		}

		count--;
	}

	return pRet;
}
#endif

#ifdef F_memcmp
int memcmp(const void *b1, const void *b2, size_t len)
{
	int val = 0;
	const unsigned char *u1, *u2;

	u1 = (const unsigned char *) b1;
	u2 = (const unsigned char *) b2;

	while(len > 0)
	{
		if(*u1 != *u2)
		{
			val = (int) *u1 - (int) *u2;
			break;
		}
		u1++;
		u2++;
		len--;
	}

	return val;
}
#endif

#ifdef F_memcpy
void *memcpy(void *dst, const void *src, size_t len)
{
	void *pRet = dst;
	const char *usrc = (const char *) src;
	char *udst = (char *) dst;

	while(len > 0)
	{
		*udst++ = *usrc++;
		len--;
	}

	return pRet;
}
#endif

#ifdef F_memmove
void *memmove(void *dst, const void* src, size_t len)
{
	void *pRet = dst;
	char *udst;
	const char *usrc;

	if(dst < src)
	{
		/* Copy forwards */
		udst = (char *) dst;
		usrc = (const char *) src;
		while(len > 0)
		{
			*udst++ = *usrc++;
			len--;
		}
	}
	else
	{
		/* Copy backwards */
		udst = ((char *) dst) + len;
		usrc = ((const char *) src) + len;
		while(len > 0)
		{
			*--udst = *--usrc;
			len--;
		}
	}
	
	return pRet;
}
#endif

#ifdef F_memset
void *memset(void *b, int c, size_t len)
{
	void *pRet = b;
	unsigned char *ub = (unsigned char *) b;

	while(len > 0)
	{
		*ub++ = (unsigned char) c;
		len--;
	}

	return pRet;
}
#endif

#ifdef F_memchr
void *memchr(const void *b, int c, size_t len)
{
	void *pRet = NULL;
	const unsigned char *ub;

	ub = (void *) b;
	while(len > 0)
	{
		if(*ub == (unsigned char) c)
		{
			pRet = (void *) &ub[0];
			break;
		}

		ub++;
		len--;
	}

	return pRet;
}
#endif

#ifdef F_strchr
char *strchr(const char *s, int c)
{
	char *pRet = NULL;

	do
	{
		if(*s == (char) c)
		{
			pRet = (char *) &s[0];
			break;
		}
	}
	while(*s++);

	return pRet;
}
#endif

#ifdef F_strdup
char *strdup(const char *s) {
	size_t str_size = strlen(s);
	char * r = (char *)malloc(str_size + 1);
	
	return strcpy(r, s);
}
#endif

#ifdef F_strcasecmp
int	strcasecmp(const char * string1, const char * string2)
{
	while (*string1 != '\0' && tolower(*string1) == tolower(*string2))
    {
      string1++;
      string2++;
    }

	return tolower(*(unsigned char *) string1) - tolower(*(unsigned char *) string2);
}
#endif


#ifdef F_strncasecmp
int	 strncasecmp(const char * string1, const char * string2, size_t n)
{
	if (n == 0)
		return 0;

	while ((n-- != 0) && (tolower(*string1) == tolower(*string2)))
    {
		if ((n == 0) || (*string1 == '\0') || (*string2 == '\0'))
			break;

		string1++;
		string2++;
	}

	return tolower(*(unsigned char *) string1) - tolower(*(unsigned char *) string2);
}
#endif

#ifdef F_strtok
char* strtok(char * strToken, const char * strDelimit)
{
	static char* start;
	static char* end;

	if (strToken != NULL)
		start = strToken;
	else
	{
		if (*end == 0)
			return 0;

		start=end;
	}

	if(*start == 0)
	{
		return 0;
	}

	// Strip out any leading delimiters
	while (strchr(strDelimit, *start))
	{
		// If a character from the delimiting string
		// then skip past it

		start++;

		if (*start == 0)
			return 0;
	}

	if (*start == 0)
		return 0;

	end=start;


	while (*end != 0)
	{
		if (strchr(strDelimit, *end))
		{
			// if we find a delimiting character
			// before the end of the string, then
			// terminate the token and move the end
			// pointer to the next character
			*end = 0;
			end++;
			return start;
		}
		
		end++;
	}


	// reached the end of the string before finding a delimiter
	// so dont move on to the next character
	return start;
}
#endif

#ifdef F_strrchr
char* strrchr(const char * string, int c)
{
	/* use the asm strchr to do strrchr */
	char* lastmatch;
	char* result;

	/* if char is never found then this will return 0 */
	/* if char is found then this will return the last matched location
	   before strchr returned 0 */

	lastmatch = 0;
	result = strchr(string,c);

	while ((int)result != 0)
	{
		lastmatch=result;
		result = strchr(lastmatch+1,c);
	}

	return lastmatch;
}
#endif

#ifdef F_strstr
char *	strstr(const char * string, const char * substring)
{
	char* strpos;

	if (string == 0)
		return 0;
	
	if (strlen(substring)==0)
		return (char*)string;

	strpos = (char*)string;

	while (*strpos != 0)
	{
		if (strncmp(strpos, substring, strlen(substring)) == 0)
		{
			return strpos;
		}

		strpos++;
	}

	return 0;
}
#endif


#ifdef F_strupr
char * strupr(char *str)
{
	char * strptr = str;
	
	// loop thru each char in string
	while (*strptr != '\0')
    {
      // if char is lowercase, convert to uppercase
      if(islower(*strptr))
      	*strptr = toupper(*strptr);
      strptr++;
    }
	
	return str;
}
#endif

#ifdef F_strlwr
char * strlwr(char *str)
{
	char * strptr = str;
	
	// loop thru each char in string
	while (*strptr != '\0')
    {
      // if char is uppercase, convert to lowercase
      if(isupper(*strptr))
      	*strptr = tolower(*strptr);
      strptr++;
    }
	
	return str;
}
#endif


#ifdef F_tolower
int tolower(int c)
{
	if (isupper(c))
		c+=32;

	return c;
}
#endif

#ifdef F_toupper
int toupper(int c)
{
	if (islower(c))
		c-=32;

	return c;
}
#endif

#ifdef F_isupper
int isupper(int c)
{
	if (c < 'A')
		return 0;

	if (c > 'Z')
		return 0;

	// passed both criteria, so it
	// is an upper case alpha char
	return 1;
}
#endif

#ifdef F_islower
int islower(int c)
{
	if (c < 'a')
		return 0;

	if (c > 'z')
		return 0;

	// passed both criteria, so it
	// is a lower case alpha char
	return 1;
}
#endif

#ifdef F_isalpha
int isalpha(int c)
{
	if (islower(c) || isupper(c))
		return 1;

	return 0;
}
#endif

#ifdef F_isdigit
int isdigit(int c)
{
	if (c < '0')
		return 0;

	if (c > '9')
		return 0;

	// passed both criteria, so it
	// is a numerical char
	return 1;
}
#endif

#ifdef F_isalnum
int isalnum(int c)
{
	if (isalpha(c) || isdigit(c))
		return 1;

	return 0;
}
#endif

#ifdef F_iscntrl
int iscntrl(int c)
{
	if (c < 0x20)
		return 1;

	if (c == 0x7F)
		return 1;

	return 0;
}
#endif

#ifdef F_isgraph
int isgraph(int c)
{
	if (iscntrl(c))
		return 0;

	if (isspace(c))
		return 0;

	return 1;
}
#endif

#ifdef F_isprint
int isprint(int c)
{
	if (iscntrl(c))
		return 0;

	return 1;
}
#endif

#ifdef F_ispunct
int ispunct(int c)
{
	if (iscntrl(c))
		return 0;
	
	if (isalnum(c))
		return 0;

	if (isspace(c))
		return 0;

	// It's a printable character
	// thats not alpha-numeric, or a space
	// so its a punctuation character
	return 1;
}
#endif

#ifdef F_isspace
int isspace(int c)
{
	if ((c>=0x09) && (c<=0x0D))
		return 1;

	if (c==0x20)
		return 1;

	return 0;
}
#endif

#ifdef F_isxdigit
int isxdigit(int c)
{
	if (isdigit(c))
		return 1;

	if ((c>='a') && (c<='f'))
		return 1;

	if ((c>='A') && (c<='F'))
		return 1;

	return 0;
}
#endif


// sjis<->ascii conversion routines by Peter Sandström

struct charmap_t {
	unsigned short sjis;
	unsigned char ascii;
};

#ifdef F__sjis_internals
struct charmap_t sjis_conversion[] = {
    { 0x4081, ' ' }, 
    { 0x6d81, '[' }, 
    { 0x6e81, ']' }, 
    { 0x7c81, '-' }, 
    { 0x5b81, '°' }, 
    { 0x4581, '¥' }, 
    { 0x4481, '.' }, 
    { 0x7B81, '+' }, 
    { 0x9681, '*' }, 
    { 0x5E81, '/' }, 
    { 0x4981, '!' }, 
    { 0x6881, '"' }, 
    { 0x9481, '#' }, 
    { 0x9081, '$' }, 
    { 0x9381, '%' }, 
    { 0x9581, '&' }, 
    { 0x6681, '\'' }, 
    { 0x6981, '(' }, 
    { 0x6a81, ')' }, 
    { 0x8181, '=' }, 
    { 0x6281, '|' }, 
    { 0x8f81, '\\' }, 
    { 0x4881, '?' }, 
    { 0x5181, '_' }, 
    { 0x6f81, '{' }, 
    { 0x7081, '}' }, 
    { 0x9781, '@' }, 
    { 0x4781, ';' }, 
    { 0x4681, ':' }, 
    { 0x8381, '<' }, 
    { 0x8481, '>' }, 
    { 0x4d81, '`' },
    { 0, 0 }
};

unsigned char isSpecialSJIS(short sjis)
{
    struct charmap_t *s = &sjis_conversion[0];
    do {
	if (s->sjis == sjis) return s->ascii;
 	s++;
    } while (s->sjis != 0);
    return 0;
}

short isSpecialASCII(unsigned char ascii)
{
    struct charmap_t *s = &sjis_conversion[0];
    do {
	if (s->ascii == ascii) return s->sjis;
 	s++;
    } while (s->ascii != 0);
    return 0;
}
#else
extern struct charmap_t * sjis_conversion;
unsigned char isSpecialSJIS(short sjis);
short isSpecialASCII(unsigned char ascii);
#endif

#ifdef F_strcpy_ascii
int strcpy_ascii(char* ascii_buff, const short* sjis_buff)
{
    int i;
    short ascii, sjis;

    int len = strlen((const char *)sjis_buff)/2;

    for (i=0;i<len;i++) {
	sjis = sjis_buff[i];
	if ((ascii = isSpecialSJIS(sjis)) != 0) {
	} else {
	    ascii = ((sjis & 0xFF00) >> 8) - 0x1f;
	    if (ascii>96) ascii--;
	}
	ascii_buff[i] = ascii;
    }
    ascii_buff[i+1]=0;
    return len;
}
#endif

#ifdef F_strcpy_sjis
int strcpy_sjis(short* sjis_buff, const char* ascii_buff)
{
    int i;
    short ascii, sjis;
	
    int len = strlen(ascii_buff);

    for (i=0;i<len;i++)	{
	ascii = ascii_buff[i];
	if ((sjis = isSpecialASCII(ascii)) != 0) {
	} else {
	    if (ascii>96) ascii++;
	    sjis = ((ascii + 0x1f) << 8) | 0x82;
	}
        sjis_buff[i] = sjis;
    }
    sjis_buff[i+1]=0;
    return len;
}
#endif

#ifdef F_strpbrk
char *strpbrk(const char *s, const char *accept)
{
    const char *needle;
    for (; *s; s++) {
        for (needle = accept; *needle; needle++) {
            if (*s == *needle)
                return (char *) s;
        }
    }
    
    return NULL;
}
#endif

#ifdef F_strspn
size_t strspn(const char *s, const char *accept) {
    const char *c;

    for (c = s; *c; c++) {
        if (!strchr(accept, *c))
            return c - s;
    }

    return c - s;
}
#endif

#ifdef F_strcspn
size_t strcspn(const char *s, const char *reject) {
    const char *c;
    
    for (c = s; *c; c++) {
        if (strchr(reject, *c))
            return c - s;
    }
    
    return c - s;
}
#endif
