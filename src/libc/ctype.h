/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * ctype.h
 *
 * Copyright (c) 2002-2004 PS2DEV
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: ctype.h 1095 2005-09-27 21:02:16Z jim $
 */

#ifndef __CTYPE_H__
#define __CTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}


/* To be compatible with C++'s ctype_base.h */

namespace std {
    enum {
	_U =	01,
	_L =	02,
	_N =	04,
	_S =	010,
	_P =	020,
	_C =	040,
	_X =	0100,
	_B =	0200
    };
};
#endif

#endif
