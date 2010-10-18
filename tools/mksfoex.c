/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |     ___|    ____| |    \    PSPDEV Open Source Project.
#-----------------------------------------------------------------------
# Review pspsdk README & LICENSE files for further details.
#
# New and improved mksfo
# $Id$
*/
#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

#define PSF_MAGIC    0x46535000
#define PSF_VERSION  0x00000101

struct SfoHeader 
{
	uint32_t magic;
	uint32_t version;
	uint32_t keyofs;
	uint32_t valofs;
	uint32_t count;
} __attribute__((packed));

struct SfoEntry
{
	uint16_t nameofs;
	uint8_t  alignment;
	uint8_t  type;
	uint32_t valsize;
	uint32_t totalsize;
	uint32_t dataofs;
} __attribute__((packed));

#define PSF_TYPE_BIN  0
#define PSF_TYPE_STR  2
#define PSF_TYPE_VAL  4

struct EntryContainer
{
	const char *name;
	int type;
	uint32_t value;
	const char *data;
};

struct EntryContainer g_defaults[] = {
	{ "BOOTABLE", PSF_TYPE_VAL, 1, NULL },
	{ "CATEGORY", PSF_TYPE_STR, 0, "MG" },
	{ "DISC_ID",  PSF_TYPE_STR, 0, "UCJS10041" },
	{ "DISC_VERSION", PSF_TYPE_STR, 0, "1.00" },
	{ "PARENTAL_LEVEL", PSF_TYPE_VAL, 1, NULL },
	{ "PSP_SYSTEM_VER", PSF_TYPE_STR, 0, "1.00" },
	{ "REGION", PSF_TYPE_VAL, 0x8000, NULL },
};

#define MAX_OPTIONS (256)

static const char *g_title = NULL;
static const char *g_filename = NULL;
static int g_empty = 0;
static struct EntryContainer g_vals[MAX_OPTIONS];

static struct option arg_opts[] = 
{
	{"dword", required_argument, NULL, 'd'},
	{"string", required_argument, NULL, 's'},
	{"empty", no_argument, NULL, 'e'},
	{ NULL, 0, NULL, 0 }
};

struct EntryContainer *find_free()
{
	int i;

	for(i = 0; i < MAX_OPTIONS; i++)
	{
		if(g_vals[i].name == NULL)
		{
			return &g_vals[i];
		}
	}

	return NULL;
}

struct EntryContainer *find_name(const char *name)
{
	int i;

	for(i = 0; i < MAX_OPTIONS; i++)
	{
		if((g_vals[i].name != NULL) && (strcmp(g_vals[i].name, name) == 0))
		{
			return &g_vals[i];
		}
	}

	return NULL;
}

int add_string(char *str)
{
	char *equals = NULL;
	struct EntryContainer *entry;

	equals = strchr(str, '=');
	if(equals == NULL)
	{
		fprintf(stderr, "Invalid option (no =)\n");
		return 0;
	}

	*equals++ = 0;

	entry = find_free();
	if(entry == NULL)
	{
		fprintf(stderr, "Maximum options reached\n");
		return 0;
	}

	memset(entry, 0, sizeof(struct EntryContainer));
	entry->name = str;
	entry->type = PSF_TYPE_STR;
	entry->data = equals;

	return 1;
}

int add_dword(char *str)
{
	char *equals = NULL;
	struct EntryContainer *entry;

	equals = strchr(str, '=');
	if(equals == NULL)
	{
		fprintf(stderr, "Invalid option (no =)\n");
		return 0;
	}

	*equals++ = 0;

	entry = find_free();
	if(entry == NULL)
	{
		fprintf(stderr, "Maximum options reached\n");
		return 0;
	}

	memset(entry, 0, sizeof(struct EntryContainer));
	entry->name = str;
	entry->type = PSF_TYPE_VAL;
	entry->value = strtoul(equals, NULL, 0);

	return 1;
}

/* Process the arguments */
int process_args(int argc, char **argv)
{
	int ch;

	g_title = NULL;
	g_filename = NULL;
	g_empty = 0;

	ch = getopt_long(argc, argv, "ed:s:", arg_opts, NULL);
	while(ch != -1)
	{
		switch(ch)
		{
			case 'd' : if(!add_dword(optarg))
					   {
						   return 0;
					   }
				break;
			case 's' : if(!add_string(optarg))
					   {
					   }
				break;
			default  : break;
		};

		ch = getopt_long(argc, argv, "ed:s:", arg_opts, NULL);
	}

	argc -= optind;
	argv += optind;

	if(argc < 1)
	{
		return 0;
	}

	if(!g_empty)
	{
		g_title = argv[0];
		argc--;
		argv++;
	}

	if(argc < 1)
	{
		return 0;
	}

	g_filename = argv[0];

	return 1;
}

int main(int argc, char **argv)
{
	FILE *fp;
	int i;
	char head[8192];
	char keys[8192];
	char data[8192];
	struct SfoHeader *h;
	struct SfoEntry  *e;
	char *k;
	char *d;
	unsigned int align;
	unsigned int keyofs;
	unsigned int count;

	if(!process_args(argc, argv)) 
	{
		fprintf(stderr, "Usage: mksfoex [options] TITLE output.sfo\n");
		fprintf(stderr, "Options:\n");
		fprintf(stderr, "-d NAME=VALUE - Add a new DWORD value\n");
		fprintf(stderr, "-s NAME=STR   - Add a new string value\n");

		return 1;
	}

	if(!g_empty)
	{
		struct EntryContainer *entry;

		for(i = 0; i < (sizeof(g_defaults) / sizeof(struct EntryContainer)); i++)
		{
			if(!find_name(g_defaults[i].name))
			{
				entry = find_free();
				if(entry == NULL)
				{
					fprintf(stderr, "Maximum options reached\n");
					return 0;
				}
				*entry = g_defaults[i];
			}
		}

		if(!find_name("TITLE"))
		{
			entry = find_free();
			entry->name = "TITLE";
			entry->type = PSF_TYPE_STR;
			entry->value = 0;
			entry->data = g_title;
		}
	}

	memset(head, 0, sizeof(head));
	memset(keys, 0, sizeof(keys));
	memset(data, 0, sizeof(data));
	h = (struct SfoHeader*) head;
	e = (struct SfoEntry*)  (head+sizeof(struct SfoHeader));
	k = keys;
	d = data;
	SW(&h->magic, PSF_MAGIC);
	SW(&h->version, PSF_VERSION);
	count = 0;

	for(i = 0; g_vals[i].name; i++)
	{
		SW(&h->count, ++count);
		SW(&e->nameofs, k-keys);
		SW(&e->dataofs, d-data);
		SW(&e->alignment, 4);
		SW(&e->type, g_vals[i].type);

		strcpy(k, g_vals[i].name);
		k += strlen(k)+1;
		if(e->type == PSF_TYPE_VAL)
		{
			SW(&e->valsize, 4);
			SW(&e->totalsize, 4);
			SW((uint32_t*) d, g_vals[i].value);
			d += 4;
		}
		else
		{
			int totalsize;
			int valsize;

			valsize = strlen(g_vals[i].data)+1;
			totalsize = (valsize + 3) & ~3;
			SW(&e->valsize, valsize);
			SW(&e->totalsize, totalsize);
			memset(d, 0, totalsize);
			memcpy(d, g_vals[i].data, valsize);
			d += totalsize;
		}
		e++;
	}


	keyofs = (char*)e - head;
	SW(&h->keyofs, keyofs);
	align = 3 - ((unsigned int) (k-keys) & 3);
	while(align < 3)
	{
		k++;
		align--;
	}
	
	SW(&h->valofs, keyofs + (k-keys));

	fp = fopen(g_filename, "wb");
	if(fp == NULL)
	{
		fprintf(stderr, "Cannot open filename %s\n", g_filename);
		return 0;
	}

	fwrite(head, 1, (char*)e-head, fp);
	fwrite(keys, 1, k-keys, fp);
	fwrite(data, 1, d-data, fp);
	fclose(fp);

	return 0;
}
