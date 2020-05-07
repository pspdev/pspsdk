/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * encrypt.h - Declarations for functions in encrypt.c
 *
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 * Coypright (c) 2005 psp123
 *
 */

#include <pspchnnlsv.h>

/* Encrypt the given plaintext file, and update the message
   authentication hashes in the param.sfo.  The data_filename is
   usually the final component of encrypted_filename, e.g. "DATA.BIN".
   See main.c for an example of usage. */
int encrypt_file(const char *plaintext_filename,
		 const char *encrypted_filename,
		 const char *data_filename,
		 const char *paramsfo_filename,
		 const unsigned char *gamekey);

/* Do the actual hardware encryption.  
   mode is 3 for saves with a cryptkey, or 1 otherwise.
   data, alignedLen, cryptkey, and hash must be multiples of 0x10.
   cryptkey is NULL if mode == 1.
*/
int encrypt_data(unsigned int mode, 
		 unsigned char *data,
		 int *dataLen,
		 int *alignedLen,
		 unsigned char *hash,
		 unsigned char *cryptkey);
