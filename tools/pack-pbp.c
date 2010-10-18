/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |     ___|    ____| |    \    PSPDEV Open Source Project.
#-----------------------------------------------------------------------
# (c) 2005 Dan Peori <peori@oopo.net>
# Licenced under Academic Free License version 2.0
# Review pspsdk README & LICENSE files for further details.
#
# 2006-12-30 - Andrew Whatson <whatson@gmail.com>
#   - rewrote for easier reading
#   - gave "correct" names to UNKNOWN.* files
#   - improved memory efficiency with large PBPs
#   - output name of each file as it's added
#
# $Id: pack-pbp.c 2228 2007-05-01 05:22:03Z oopo $
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef WORDS_BIGENDIAN

// Swap the bytes of an int for big-endian machines
static int swap_int(int n)
{
  return ((n>>24)&0xff)|((n>>8)&0xff00)|((n<<8)&0xff0000)|((n<<24)&0xff000000);
}

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

// Struct to describe the header of a PBP file
struct {
   char signature[4];
   char version[4];
   int offset[8];
} header = {
   { 0x00, 0x50, 0x42, 0x50 },
   { 0x00, 0x00, 0x01, 0x00 },
   { 40, 0, 0, 0, 0, 0, 0, 0 }
};

// Maximum size of read buffer
int maxbuffer = 16 * 1024 * 1024;

int main(int argc, char *argv[]) { int loop0, result;
   FILE *infile;
   FILE *outfile;
   int filesize[8];
   
   // Check for the correct number of arguments
   if (argc != 10) {
      printf("USAGE: %s <output.pbp> <param.sfo> <icon0.png> <icon1.pmf> <pic0.png> <pic1.png> <snd0.at3> <data.psp> <data.psar>\n", argv[0]);
      return -1;
   }
   
   // For each file in the PBP
   for (loop0 = 0; loop0 < 8; loop0++) {
      
      // If the specificed filename is NULL or -, skip the file.
      if (strncmp(argv[2 + loop0], "NULL", 4) == 0 || strncmp(argv[2 + loop0], "-", 4) == 0) {
         filesize[loop0] = 0;
      } else {
         
         // Open the file
         infile = fopen(argv[2 + loop0], "rb");
         if (infile == NULL) {
            printf("ERROR: Could not open the file. (%s)\n", argv[2 + loop0]);
            return -1;
         }
         
         // Read in the file size
         fseek(infile, 0, SEEK_END);
         filesize[loop0] = ftell(infile);
         fseek(infile, 0, SEEK_SET);
         if (filesize[loop0] < 0) {
            printf("ERROR: Could not read in the file size. (%s)\n", argv[2 + loop0]);
            return -1;
         }
         
         // Close the file
         result = fclose(infile);
         if (result < 0) {
            printf("ERROR: Could not close the file. (%s)\n", argv[2 + loop0]);
            return -1;
         }
      }
   }

   // Set the header offset values for each file
   for (loop0 = 1; loop0 < 8; loop0++) {
      header.offset[loop0] = header.offset[loop0 - 1] + filesize[loop0 - 1];
   }
   
#ifdef WORDS_BIGENDIAN
   
   // Swap the bytes of the offsets for big-endian machines
   for (loop0 = 0; loop0 < 8; loop0++) {
      header.offset[loop0] = swap_int(header.offset[loop0]);
   }
   
#endif
   
   // Open the output file
   outfile = fopen(argv[1], "wb");
   if (outfile == NULL) {
      printf("ERROR: Could not open the output file. (%s)\n", argv[1]);
      return -1;
   }
   
   // Write out the header
   result = fwrite(&header, sizeof(header), 1, outfile);
   if (result < 0) {
      printf("ERROR: Could not write out the file header. (%s)\n", argv[1]);
      return -1;
   }
   
   // For each file in the PBP
   for (loop0 = 0; loop0 < 8; loop0++) {
      void *buffer;
      int readsize;
      
      // Print out the file details
      printf("[%d] %10d bytes | %s\n", loop0, filesize[loop0], argv[2 + loop0]);
      
      // If this file is empty, skip it
      if (!filesize[loop0]) continue;
      
      // Open the file
      infile = fopen(argv[2 + loop0], "rb");
      if (infile == NULL) {
         printf("ERROR: Could not open the file. (%s)\n", argv[2 + loop0]);
         return -1;
      }
      
      do {
         // Make sure we don't exceed the maximum buffer size
         if (filesize[loop0] > maxbuffer) {
            readsize = maxbuffer;
         } else {
            readsize = filesize[loop0];
         }
         filesize[loop0] -= readsize;
         
         // Create the read buffer
         buffer = malloc(readsize);
         if (buffer == NULL) {
            printf("ERROR: Could not allocate the file data space. (%s)\n", argv[2 + loop0]);
            return -1;
         }
         
         // Read in the data from the file
         if (fread(buffer, readsize, 1, infile) < 0) {
            printf("ERROR: Could not read in the file data. (%s)\n", argv[2 + loop0]);
            return -1;
         }
         
         // Write the contents of the buffer to the PBP
         if (fwrite(buffer, readsize, 1, outfile) < 0) {
            printf("ERROR: Could not write out the file data. (%s)\n", argv[1]);
            return -1;
         }
         
         // Clean up the buffer
         free(buffer);
         
         // Repeat if we haven't finished writing the file
      } while (filesize[loop0]);
   }
   
   // Close the output file.
   result = fclose(outfile);
   if (result < 0) {
      printf("ERROR: Could not close the output file. (%s)\n", argv[1]);
      return -1;
   }
   
   // Exit successful
   return 0;
} 
