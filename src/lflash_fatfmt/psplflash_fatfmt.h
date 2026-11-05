#ifndef __LFLASH_FATFMT_H__
#define __LFLASH_FATFMT_H__

/**
 * Performs a logical format in a flash partition.
 *
 * @param argc The number of parameters
 * @param argv The parameters
 *
 * @returns `< 0` on error
 */
int sceLflashFatfmtStartFatfmt(int argc, char *argv[]);

#endif