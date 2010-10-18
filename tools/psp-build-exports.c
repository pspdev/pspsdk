/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psp-build-exports.c - Simple program to build an export file.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: psp-build-exports.c 2415 2008-08-01 16:56:26Z Raphael $
 */

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>

#include "sha1.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define MAX_LIB_NAME 27
#define MAX_LIB_FUNCS 65535
#define MAX_LIB_VARS  255
#define MAX_LIB_ENTRY_NAME 127
#define MAX_ERROR 1024
#define MAX_LINE  1024
#define SYSTEM_LIB_NAME "syslib"

enum PspConfigMode
{
	PSP_BUILD_UNKNOWN,
	PSP_BUILD_EXPORTS,
	PSP_BUILD_STUBS,
	PSP_BUILD_STUBS_NEW,
};

struct psp_export
{
	struct psp_export *pNext;
	unsigned int nid;
	char name[MAX_LIB_ENTRY_NAME+1];
};

struct psp_alias
{
	struct psp_alias *pNext;
	char name[MAX_LIB_ENTRY_NAME+1];
	char alias[MAX_LIB_ENTRY_NAME+1];
};

struct psp_lib
{
	struct psp_lib *pNext;
	char name[MAX_LIB_NAME+1];
	unsigned short ver;
	unsigned short attr;
	int funcCount;
	struct psp_export *pFuncHead;
	int varCount;
	struct psp_export *pVarHead;
	struct psp_alias *pAliasHead;
};

struct export_cmd
{
	const char *name;
	int params;
	int (*handler)(char ** params);
};

/* Specifies that the current usage is to the print the pspsdk path */
static enum PspConfigMode g_outputmode;
static int g_verbose = 0;
static const char *g_infile;
static char g_errstring[MAX_ERROR] = "No Error";
static struct psp_lib *g_libhead = NULL;
static struct psp_lib *g_currlib = NULL;
static int g_libcount = 0;

void free_export_chain(struct psp_export *pHead)
{
	struct psp_export *pNext;

	pNext = pHead;

	while(pNext != NULL)
	{
		struct psp_export *pTemp;

		pTemp = pNext->pNext;
		free(pNext);
		pNext = pTemp;
	}
}

void free_alias_chain(struct psp_alias *pHead)
{
	struct psp_alias *pNext;

	pNext = pHead;

	while(pNext != NULL)
	{
		struct psp_alias *pTemp;

		pTemp = pNext->pNext;
		free(pNext);
		pNext = pTemp;
	}
}

void free_lib_data(void)
{
	struct psp_lib *pNext;

	if(g_currlib != NULL)
	{
		free_export_chain(g_currlib->pFuncHead);
		free_export_chain(g_currlib->pVarHead);
		free_alias_chain(g_currlib->pAliasHead);
		free(g_currlib);
		g_currlib = NULL;
	}

	pNext = g_libhead;

	while(pNext != NULL)
	{
		struct psp_lib *pTemp;

		pTemp = pNext->pNext;
		free_export_chain(pNext->pFuncHead);
		free_export_chain(pNext->pVarHead);
		free_alias_chain(pNext->pAliasHead);
		free(pNext);
		pNext = pTemp;
	}

	g_libhead = NULL;
}

const char *find_alias(struct psp_alias *pHead, const char *name)
{
	struct psp_alias *pNext;
	const char *szAlias = NULL;

	pNext = pHead;
	while(pNext)
	{
		if(strcmp(name, pNext->name) == 0)
		{
			szAlias = pNext->alias;
			break;
		}

		pNext = pNext->pNext;
	}

	return szAlias;
}

static struct option arg_opts[] = 
{
	{"build-exports", no_argument, NULL, 'b'},
	{"build-stubs", no_argument, NULL, 's'},
	{"build-stubs-new", no_argument, NULL, 'k'},
	{"verbose", no_argument, NULL, 'v'},
	{ NULL, 0, NULL, 0 }
};

/* Process the arguments */
int process_args(int argc, char **argv)
{
	int ret = 0;
	int ch;

	g_outputmode = PSP_BUILD_UNKNOWN;

	ch = getopt_long(argc, argv, "bsvk", arg_opts, NULL);
	while(ch != -1)
	{
		switch(ch)
		{
			case 'b' : g_outputmode = PSP_BUILD_EXPORTS;
					   ret = 1;
					   break;
			case 's' : g_outputmode = PSP_BUILD_STUBS;
					   ret = 1;
					   break;
			case 'v' : g_verbose = 1;
					   break;
			case 'k' : g_outputmode = PSP_BUILD_STUBS_NEW;
					   ret = 1;
					   break;
			default  : //fprintf(stderr, "Invalid option '%c'\n", ch);
					   break;
		};

		ch = getopt_long(argc, argv, "bsvk", arg_opts, NULL);
	}

	argc -= optind;
	argv += optind;

	if(argc < 1)
	{
		return 0;
	}

	g_infile = argv[0];

	return ret;
}

void print_help(void)
{
	fprintf(stderr, "Usage: psp-build-exports -b|-s|-k [-v] export.exp\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-b, --build-exports     : Build an export file to stdout\n");
	fprintf(stderr, "-s, --build-stubs       : Build a batch of stub files for the exports\n");
	fprintf(stderr, "-k, --build-stubs-new   : Build a batch of stub files (in new format)\n");
	fprintf(stderr, "-v, --verbose           : Verbose output\n");
}

void strip_whitespace(char *dest, const char *src)
{
	assert(dest != NULL);
	assert(src != NULL);

	while(*src != 0)
	{
		if(!isspace(*src))
		{
			*dest = *src;
			dest++;
		}

		src++;
	}

	*dest = 0;
}

/*
   Parse a string of the form FUNC(arg1,arg2,...)
   Returns the number of parameters or -1 on error.
   */
int parse_string(char *line, char **params, int max_params)
{
	int pos;
	int param_start;
	char *next_param;
	int param_count;

	assert(line != NULL);
	assert(params != NULL);

	pos = 0;

	/* Parse off "function" name */
	while((isalnum(line[pos])) || (line[pos] == '_'))
	{
		pos++;
	}

	/* If we don't have any thing else than this is just the function */
	if(line[pos] == 0)
	{
		return 0;
	}

	if(line[pos] != '(')
	{
		snprintf(g_errstring, MAX_ERROR, "Invalid character %c, expected (", line[pos]);
		return -1;
	}

	/* Terminate */
	line[pos++] = 0;
	param_start = pos;

	/* Scan parameters */
	while((isalnum(line[pos])) || (line[pos] == '_') || (line[pos] == ','))
	{
		pos++;
	}

	if(line[pos] == 0)
	{
		snprintf(g_errstring, MAX_ERROR, "Missing closing brace ')'");
		return -1;
	}

	if(line[pos] != ')')
	{
		snprintf(g_errstring, MAX_ERROR, "Invalid character %c, expected ')'", line[pos]);
		return -1;
	}

	if(line[pos+1] != 0)
	{
		snprintf(g_errstring, MAX_ERROR, "Trailing characters after bracket close %d", line[pos+1]);
		return -1;
	}

	line[pos] = 0;

	param_count = 0;
	next_param = strtok(&line[param_start], ",");
	while(next_param != NULL)
	{
		if(param_count == max_params)
		{
			snprintf(g_errstring, MAX_ERROR, "Run out of space for parameters");
			return -1;
		}

		params[param_count++] = next_param;
		next_param = strtok(NULL, ",");
	}

	return param_count;
}

void build_exports_output_extern(struct psp_export *pHead)
{
	struct psp_export *pExp;

	pExp = pHead;
	while(pExp != NULL)
	{
		fprintf(stdout, "extern void %s;\n", pExp->name);
		pExp = pExp->pNext;
	}
}

void build_exports_output_nids(struct psp_export *pHead)
{
	struct psp_export *pExp;

	pExp = pHead;
	while(pExp != NULL)
	{
		fprintf(stdout, "\t0x%08X,\n", pExp->nid);
		pExp = pExp->pNext;
	}
}

void build_exports_output_names(struct psp_export *pHead)
{
	struct psp_export *pExp;

	pExp = pHead;
	while(pExp != NULL)
	{
		fprintf(stdout, "\t(unsigned int) &%s,\n", pExp->name);
		pExp = pExp->pNext;
	}
}

void build_exports(void)
{
	struct psp_lib *pLib;

	fprintf(stdout, "#include <pspmoduleexport.h>\n");
	fprintf(stdout, "#define NULL ((void *) 0)\n\n");

	/* Write out the nid tables */
	pLib = g_libhead;
	while(pLib != NULL)
	{
		/* Print extern */
		build_exports_output_extern(pLib->pFuncHead);
		build_exports_output_extern(pLib->pVarHead);

		fprintf(stdout, "static const unsigned int __%s_exports[%d] __attribute__((section(\".rodata.sceResident\"))) = {\n", 
				pLib->name, (pLib->funcCount + pLib->varCount) * 2);

		/* Print nid */
		build_exports_output_nids(pLib->pFuncHead);
		build_exports_output_nids(pLib->pVarHead);
		/* Print names */
		build_exports_output_names(pLib->pFuncHead);
		build_exports_output_names(pLib->pVarHead);
		fprintf(stdout, "};\n\n");

		pLib = pLib->pNext;
	}

	fprintf(stdout, "const struct _PspLibraryEntry __library_exports[%d] __attribute__((section(\".lib.ent\"), used)) = {\n", g_libcount);
	pLib = g_libhead;
	while(pLib != NULL)
	{
		if(strcmp(pLib->name, SYSTEM_LIB_NAME) == 0)
		{
			fprintf(stdout, "\t{ NULL, ");
		}
		else
		{
			fprintf(stdout, "\t{ \"%s\", ", pLib->name);
		}

		fprintf(stdout, "0x%04X, 0x%04X, 4, %d, %d, &__%s_exports },\n", pLib->ver, pLib->attr, 
				pLib->varCount, pLib->funcCount, pLib->name);

		pLib = pLib->pNext;
	}
	fprintf(stdout, "};\n");
}

void build_stubs_output_lib(struct psp_lib *pLib)
{
	FILE *fp;
	char filename[256];

	snprintf(filename, 256, "%s.S", pLib->name);
	if(g_verbose)
	{
		fprintf(stderr, "Writing output file %s\n", filename);
	}
	fp = fopen(filename, "w");
	if(fp != NULL)
	{
		struct psp_export *pExp;

		fprintf(fp, "\t.set noreorder\n\n");
		fprintf(fp, "#include \"pspstub.s\"\n\n");
		fprintf(fp, "\tSTUB_START \"%s\",0x%08X,0x%08X\n", pLib->name, ((pLib->attr | 0x8) << 16) | pLib->ver,
						(pLib->funcCount << 16) | 5);

		pExp = pLib->pFuncHead;
		while(pExp != NULL)
		{
			const char *alias;

			alias = find_alias(pLib->pAliasHead, pExp->name);
			if(alias)
			{
				fprintf(fp, "\tSTUB_FUNC_WITH_ALIAS  0x%08X,%s,%s\n", pExp->nid, pExp->name,alias);
			}
			else
			{
				fprintf(fp, "\tSTUB_FUNC  0x%08X,%s\n", pExp->nid, pExp->name);
			}
			pExp = pExp->pNext;
		}

		fprintf(fp, "\tSTUB_END\n");

		fclose(fp);
	}
	else
	{
		fprintf(stderr, "Error, couldn't open file %s for writing\n", filename);
	}
}

void build_stubs_output_lib_new(struct psp_lib *pLib)
{
	FILE *fp;
	char filename[256];
	int i;

	snprintf(filename, 256, "%s.S", pLib->name);
	if(g_verbose)
	{
		fprintf(stderr, "Writing output file %s\n", filename);
	}
	fp = fopen(filename, "w");
	if(fp != NULL)
	{
		struct psp_export *pExp;

		fprintf(fp, "\t.set noreorder\n\n");
		fprintf(fp, "#include \"pspimport.s\"\n\n");

		fprintf(fp, "// Build files\n");
		fprintf(fp, "// %s_0000.o ", pLib->name);
		pExp = pLib->pFuncHead;
		i = 1;
		while(pExp != NULL)
		{
			fprintf(fp, "%s_%04d.o ", pLib->name, i++);
			pExp = pExp->pNext;
		}
		fprintf(fp, "\n\n");

		fprintf(fp, "#ifdef F_%s_0000\n", pLib->name);
		fprintf(fp, "\tIMPORT_START \"%s\",0x%08X\n", pLib->name, ((pLib->attr | 0x8) << 16) | pLib->ver);
		fprintf(fp, "#endif\n");

		pExp = pLib->pFuncHead;
		i = 1;
		while(pExp != NULL)
		{
			const char *alias;
			fprintf(fp, "#ifdef F_%s_%04d\n", pLib->name, i++);

			alias = find_alias(pLib->pAliasHead, pExp->name);
			if(alias)
			{
				fprintf(fp, "\tIMPORT_FUNC_WITH_ALIAS  \"%s\",0x%08X,%s,%s\n", pLib->name, pExp->nid, pExp->name, alias);
			}
			else
			{
				fprintf(fp, "\tIMPORT_FUNC  \"%s\",0x%08X,%s\n", pLib->name, pExp->nid, pExp->name);
			}

			fprintf(fp, "#endif\n");
			pExp = pExp->pNext;
		}

		fclose(fp);
	}
	else
	{
		fprintf(stderr, "Error, couldn't open file %s for writing\n", filename);
	}
}

void build_stubs(void)
{
	struct psp_lib *pLib;

	pLib = g_libhead;

	while(pLib != NULL)
	{
		if(strcmp(pLib->name, SYSTEM_LIB_NAME))
		{
			if(g_outputmode == PSP_BUILD_STUBS)
			{
				build_stubs_output_lib(pLib);
			}
			else
			{
				build_stubs_output_lib_new(pLib);
			}
		}

		pLib = pLib->pNext;
	}
}

int validate_number(const char *str, unsigned int *num)
{
	char *endp;

	assert(str != NULL);
	assert(num != NULL);

	if(!isxdigit(*str))
	{
		snprintf(g_errstring, MAX_ERROR, "'%s' is an invalid number", str);
		return 0;
	}

	*num = strtoul(str, &endp, 0);
	if(*endp != 0)
	{
		snprintf(g_errstring, MAX_ERROR, "'%s' has trailing non-numeric characters", str);
		return 0;
	}

	return 1;
}

int psp_begin_exports(char **params)
{
	/* Do nothing */
	return 1;
}

int psp_end_exports(char **params)
{
	if(g_currlib != NULL)
	{
		/* Error, missing end of exports */
	}

	return 1;
}

int psp_export_start(char **params)
{
	unsigned int ver;
	unsigned int attr;

	if(g_currlib != NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "Previous library '%s' not ended", g_currlib->name);
		return 0;
	}

	if(validate_number(params[1], &ver) == 0)
	{
		return 0;
	}

	if(validate_number(params[2], &attr) == 0)
	{
		return 0;
	}

	g_currlib = (struct psp_lib *) malloc(sizeof(struct psp_lib));
	if(g_currlib == NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "Could not allocate memory for library");
		return 0;
	}

	memset(g_currlib, 0, sizeof(struct psp_lib));
	g_libcount++;

	strncpy(g_currlib->name, params[0], MAX_LIB_NAME);
	g_currlib->ver = ver;
	g_currlib->attr = attr;

	return 1;
}

int psp_export_end(char **params)
{
	struct psp_lib *pNext;

	if(g_currlib == NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "No matching start command for library end");
		return 1;
	}

	/* Add to the end of the chain */
	if(g_libhead == NULL)
	{
		g_libhead = g_currlib;
	}
	else
	{
		pNext = g_libhead;
		while(pNext->pNext != NULL)
		{
			pNext = pNext->pNext;
		}

		pNext->pNext = g_currlib;
	}

	g_currlib = NULL;

	return 1;
}

int internal_do_export(const char *name, unsigned int nid, struct psp_export **pHead)
{
	struct psp_export *pNew;

	assert(name != NULL);
	assert(pHead != NULL);

	pNew = (struct psp_export *) malloc(sizeof(struct psp_export));

	if(pNew != NULL)
	{
		struct psp_export *pNext;

		memset(pNew, 0, sizeof(struct psp_export));
		strncpy(pNew->name, name, MAX_LIB_ENTRY_NAME);
		pNew->nid = nid;

		if(*pHead == NULL)
		{
			*pHead = pNew;
		}
		else
		{
			pNext = *pHead;
			while(pNext->pNext != NULL)
			{
				pNext = pNext->pNext;
			}

			pNext->pNext = pNew;
		}
	}
	else
	{
		snprintf(g_errstring, MAX_ERROR, "Could not allocate memory for export %s", name);
		return 0;
	}

	return 1;
}

int psp_export_func_nid(char **params)
{
	unsigned int nid;

	if(g_currlib == NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "Cannot export function, not in a library definition");
		return 0;
	}

	if(validate_number(params[1], &nid) == 0)
	{
		return 0;
	}

	if(g_currlib->funcCount < MAX_LIB_FUNCS)
	{
		if(internal_do_export(params[0], nid, &g_currlib->pFuncHead))
		{
			g_currlib->funcCount++;
			return 1;
		}
	}
	else
	{
		snprintf(g_errstring, MAX_ERROR, "Too many functions defined, cannot export another");
	}

	return 0;
}

int psp_export_func_hash(char **params)
{
	unsigned int nid;
	unsigned char hash[SHA1_DIGEST_SIZE];

	if(g_currlib == NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "Cannot export function, not in a library definition");
		return 0;
	}

	sha1(hash, (unsigned char *) params[0], strlen(params[0]));
	nid = hash[0] | (hash[1] << 8) | (hash[2] << 16) | (hash[3] << 24);

	if(g_currlib->funcCount < MAX_LIB_FUNCS)
	{
		if(internal_do_export(params[0], nid, &g_currlib->pFuncHead))
		{
			g_currlib->funcCount++;
			return 1;
		}
	}
	else
	{
		snprintf(g_errstring, MAX_ERROR, "Too many functions defined, cannot export another");
	}

	return 0;
}

int psp_export_var_nid(char **params)
{
	unsigned int nid;

	if(g_currlib == NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "Cannot export variable, not in a library definition");
		return 0;
	}

	if(validate_number(params[1], &nid) == 0)
	{
		return 0;
	}

	if(g_currlib->varCount < MAX_LIB_VARS)
	{
		if(internal_do_export(params[0], nid, &g_currlib->pVarHead))
		{
			g_currlib->varCount++;
			return 1;
		}
	}
	else
	{
		snprintf(g_errstring, MAX_ERROR, "Too many variables defined, cannot export another");
	}

	return 0;
}

int psp_export_var_hash(char **params)
{
	unsigned int nid;
	unsigned char hash[SHA1_DIGEST_SIZE];

	if(g_currlib == NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "Cannot export variable, not in a library definition");
		return 0;
	}

	sha1(hash, (unsigned char *) params[0], strlen(params[0]));
	nid = hash[0] | (hash[1] << 8) | (hash[2] << 16) | (hash[3] << 24);

	if(g_currlib->varCount < MAX_LIB_VARS)
	{
		if(internal_do_export(params[0], nid, &g_currlib->pVarHead))
		{
			g_currlib->varCount++;
			return 1;
		}
	}
	else
	{
		snprintf(g_errstring, MAX_ERROR, "Too many variables defined, cannot export another");
	}

	return 0;
}

int psp_export_alias(char **params)
{
	struct psp_alias *pAlias;

	if(g_currlib == NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "Cannot alias name, not in a library definition");
		return 0;
	}

	pAlias = (struct psp_alias *) malloc(sizeof(struct psp_alias));
	if(pAlias == NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "Cannot allocate memory for alias");
		return 0;
	}

	memset(pAlias, 0, sizeof(*pAlias));
	strncpy(pAlias->name, params[0], MAX_LIB_ENTRY_NAME);
	strncpy(pAlias->alias, params[1], MAX_LIB_ENTRY_NAME);

	if(g_currlib->pAliasHead == NULL)
	{
		g_currlib->pAliasHead = pAlias;
	}
	else
	{
		struct psp_alias *pNext = g_currlib->pAliasHead;

		while(pNext->pNext)
		{
			pNext = pNext->pNext;
		}

		pNext->pNext = pAlias;
	}

	fprintf(stderr, "Alias %s->%s\n", params[0], params[1]);

	return 1;
}

struct export_cmd commands[] = 
{
	{ "PSP_BEGIN_EXPORTS", 0, psp_begin_exports },
	{ "PSP_END_EXPORTS", 0, psp_end_exports },
	{ "PSP_EXPORT_START", 3, psp_export_start },
	{ "PSP_EXPORT_END", 0, psp_export_end },
	{ "PSP_EXPORT_FUNC_NID", 2, psp_export_func_nid },
	{ "PSP_EXPORT_FUNC_HASH", 1, psp_export_func_hash },
	{ "PSP_EXPORT_FUNC", 1, psp_export_func_hash },
	{ "PSP_EXPORT_VAR_NID", 2, psp_export_var_nid },
	{ "PSP_EXPORT_VAR", 1, psp_export_var_hash },
	{ "PSP_EXPORT_VAR_HASH", 1, psp_export_var_hash },
	{ "PSP_EXPORT_ALIAS", 2, psp_export_alias },
	{ NULL, 0, NULL }
};

int process_command(const char *cmd, char ** params, int param_count)
{
	int i;

	i = 0;

	while(commands[i].name != NULL)
	{
		if(strcmp(cmd, commands[i].name) == 0)
		{
			assert(commands[i].handler != NULL);
			if(param_count != commands[i].params)
			{
				snprintf(g_errstring, MAX_ERROR, "Incorrect number of parameters, have %d, expect %d\n", 
						param_count, commands[i].params);
				break;
			}
			else
			{
				return commands[i].handler(params);
			}
		}

		i++;
	}

	if(commands[i].name == NULL)
	{
		snprintf(g_errstring, MAX_ERROR, "Unknown command '%s'", cmd);
	}

	return 0;
}

int load_exports(void)
{
	FILE *fp;
	int line_no = 1;

	fp = fopen(g_infile, "r");
	if(fp != NULL)
	{
		char curr_line[MAX_LINE];
		char strip_line[MAX_LINE];

		while(fgets(curr_line, MAX_LINE, fp))
		{
			strip_whitespace(strip_line, curr_line);
			if((strip_line[0] != 0) && (strip_line[0] != '#'))
			{
				int ret;
				char *params[16];

				ret = parse_string(strip_line, params, 16);
				if(ret >= 0)
				{
					if(g_verbose)
					{
						int i;

						fprintf(stderr, "Line %d, Name: %s ", line_no, strip_line);
						for(i = 0; i < ret; i++)
						{
							fprintf(stderr, "Arg %d: %s ", i, params[i]);
						}
						fprintf(stderr, "\n");
					}

					if(process_command(strip_line, params, ret) == 0)
					{
						fprintf(stderr, "Error, line %d: %s\n", line_no, g_errstring);
						return 0;
					}
				}
				else
				{
					fprintf(stderr, "Error, line %d: %s\n", line_no, g_errstring);
					return 0;
				}
			}

			line_no++;
		}

		if(g_currlib)
		{
			fprintf(stderr, "Error, reached end of file while still exporting a library\n");
			return 0;
		}
	}
	else
	{
		fprintf(stderr, "Could not open file %s\n", g_infile);
		return 0;
	}

	return 1;
}

void dump_exports(void)
{
	struct psp_lib *pLib;
	int count;

	pLib = g_libhead;
	count = 1;

	while(pLib != NULL)
	{
		fprintf(stderr, "Export %d '%s', ver %04X, attr %04X\n", count, pLib->name, pLib->ver, pLib->attr);
		fprintf(stderr, "Funcs %d-%p, Vars %d-%p\n", pLib->funcCount, pLib->pFuncHead,  pLib->varCount, pLib->pVarHead);

		if(pLib->pFuncHead != NULL)
		{
			int func;
			struct psp_export *pFunc;

			func = 0;
			pFunc = pLib->pFuncHead;
			while(pFunc != NULL)
			{
				fprintf(stderr, "Function %d - '%s', nid %08X\n", func++, pFunc->name, pFunc->nid);
				pFunc = pFunc->pNext;
			}
		}

		if(pLib->pVarHead != NULL)
		{
			int var;
			struct psp_export *pVar;

			var = 0;
			pVar = pLib->pVarHead;
			while(pVar != NULL)
			{
				fprintf(stderr, "Variable %d - '%s', nid %08X\n", var++, pVar->name, pVar->nid);
				pVar = pVar->pNext;
			}
		}



		count++;
		pLib = pLib->pNext;
	}
}

int main(int argc, char **argv)
{
	if(process_args(argc, argv))
	{
		if(load_exports())
		{
			if(g_verbose)
			{
				dump_exports();
			}
			switch(g_outputmode)
			{
				case PSP_BUILD_EXPORTS: build_exports();
										break;
										/* Do the same for both */
				case PSP_BUILD_STUBS_NEW: 
				case PSP_BUILD_STUBS  : build_stubs();
										break;
				default				  : /* Argh */
										break;
			};
		}

		free_lib_data();
	}
	else
	{
		print_help();
	}

	return 0;
}
