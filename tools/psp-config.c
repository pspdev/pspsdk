#if defined(__MINGW32__) && !defined(__CYGWIN__)
#include <windows.h>
#endif
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define PSPDEV_ENV "PSPDEV"
#define PATH_ENV "PATH"

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

/***** Might need to change these for different platforms */
#define PATH_SEP ":"
#define DIR_SEP '/'
#define DIR_SEP_STR "/"

/* The suffix to the path to strip off, if this is not there then we have an error */
#ifdef __MINGW32__
#define PSPDEV_PATH_SUFFIX "/bin/psp-config.exe"
#else
#define PSPDEV_PATH_SUFFIX "/bin/psp-config"
#endif
/************************/

enum PspConfigMode
{
	PSP_CONFIG_UNKNOWN,
	PSP_CONFIG_PSPSDK_PATH,
	PSP_CONFIG_PSPDEV_PATH,
	PSP_CONFIG_PSP_PREFIX,
};

/* Specifies that the current usage is to the print the pspsdk path */
static enum PspConfigMode g_configmode;

static struct option arg_opts[] = 
{
	{"pspsdk-path", no_argument, NULL, 'p'},
	{"pspdev-path", no_argument, NULL, 'd'},
	{"psp-prefix",  no_argument, NULL, 'P'},
	{ NULL, 0, NULL, 0 }
};

/* Process the arguments */
int process_args(int argc, char **argv)
{
	int ret = 0;
	int ch;

	g_configmode = PSP_CONFIG_UNKNOWN;

	ch = getopt_long(argc, argv, "pdP", arg_opts, NULL);
	while(ch != -1)
	{
		switch(ch)
		{
			case 'p' : g_configmode = PSP_CONFIG_PSPSDK_PATH;
					   ret = 1;
					   break;
			case 'd' : g_configmode = PSP_CONFIG_PSPDEV_PATH;
					   ret = 1;
					   break;
			case 'P' : g_configmode = PSP_CONFIG_PSP_PREFIX;
					   ret = 1;
					   break;
			default  : fprintf(stderr, "Invalid option '%c'\n", ch);
					   break;
		};

		ch = getopt_long(argc, argv, "p", arg_opts, NULL);
	}

	return ret;
}

void print_help(void)
{
	fprintf(stderr, "Usage: psp-config [opts]\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-p, --pspsdk-path       : Print the base directory of PSPSDK\n");
	fprintf(stderr, "-d, --pspdev-path       : Print the base install directory\n");
	fprintf(stderr, "-P, --psp-prefix        : Print the prefix of PSP-hosted software\n");
}

void normalize_path (char *out)
{
       int i;
       int j;

       /* Convert "//" to "/" */
       for (i = 0; out[i + 1]; i++) {
               if (out[i] == '/' && out[i + 1] == '/') {
                       for (j = i + 1; out[j]; j++) {
                               out[j] = out[j + 1];
                       }
                       i--;
               }
       }
}

/* Find the path to the pspdev dir (e.g. /usr/local/pspdev) */
char *find_pspdev_path(char *name)
{
	static char path[MAX_PATH];
	int found = 0;

	/* Check if name is an absolute path, if so our job is done */

#ifdef __MINGW32__

	char *writableName = malloc(strlen(name) + 2);
	char *ptr = writableName;
	char temp;

	while (*(name)) {
		temp = *(name++);
		if (temp == '\\') temp = '/';
		*(ptr++) = temp;
	}

	*(ptr) = '\0';
	name = writableName;
#endif

	if(name[0] == DIR_SEP 
#ifdef __MINGW32__
	   || name[1] == ':' 
#endif
		)
	{
		/* Absolute path */
		strncpy(path, name, MAX_PATH);
		/* Ensure NUL termination */
		path[MAX_PATH-1] = 0;
		found = 1;
	}
	else 
	{
		/* relative path */
		if(strchr(name, DIR_SEP) != NULL)
		{
			if(getcwd(path, MAX_PATH) != NULL)
			{
				strncat(path, DIR_SEP_STR, MAX_PATH-1);
				strncat(path, name, MAX_PATH-1);
				found = 1;
			}
			else
			{
				fprintf(stderr, "Error getting current working directory\n");
			}
		}
		else
		{
			char *path_env;
			/* Scan the PATH variable */
			path_env = getenv(PATH_ENV);
			if(path_env != NULL)
			{
				char *curr_tok;
				char new_path[MAX_PATH];

				/* Should really use the path separator from the 
				   environment but who on earth changes it? */
				curr_tok = strtok(path_env, PATH_SEP);
				while(curr_tok != NULL)
				{
					strcpy(new_path, curr_tok);
					strcat(new_path, DIR_SEP_STR);
					strcat(new_path, name);

					if(access(new_path, X_OK) == 0)
					{
						found = 1;
						strcpy(path, new_path);
						break;
					}
					
					curr_tok = strtok(NULL, PATH_SEP);
				}
			}
			else
			{
				fprintf(stderr, "Error, couldn't get PATH environment variable\n");
			}
		}
	}

	normalize_path(path);
	char *result = NULL;

	if(found)
	{
		int suffix_len;
		int path_len;

		suffix_len = strlen(PSPDEV_PATH_SUFFIX);
		path_len = strlen(path);

		if(suffix_len <= path_len)
		{
			if(strcmp(PSPDEV_PATH_SUFFIX, &path[path_len - suffix_len]) == 0)
			{
				/* Oki valid path add a NUL */
				path[path_len - suffix_len] = 0;
				result = path;
			}
			else
			{
				fprintf(stderr, "Error, invalid suffix on the end of the path. Should be %s\n", PSPDEV_PATH_SUFFIX);
			}
		}
		else
		{
			fprintf(stderr, "Error, path not large enough for creating the PSPSDK path\n");
		}

	}

#ifdef __MINGW32__
	free(writableName);
#endif

	return result;
}

void print_path(char *name)
{
	char *pspdev_env;

	pspdev_env = getenv(PSPDEV_ENV);
	if(pspdev_env == NULL)
	{
		/* Could not find the PSPDEV environment variable */
		/* Let's try and find where psp-config is */
		pspdev_env = find_pspdev_path(name);
	}

	if (pspdev_env != NULL) {
		switch(g_configmode)
		{
			case PSP_CONFIG_PSPSDK_PATH : printf("%s%c%s\n", pspdev_env, DIR_SEP, PSPSDK_TOPDIR);
										  break;
			case PSP_CONFIG_PSPDEV_PATH : printf("%s\n", pspdev_env);
										  break;
			case PSP_CONFIG_PSP_PREFIX :  printf("%s%c%s\n", pspdev_env, DIR_SEP, "psp");
										  break;
			default : fprintf(stderr, "Error, invalida configuration mode\n");
					  break;
		};
	}
}

int main(int argc, char **argv)
{
#if defined(__MINGW32__) && !defined(__CYGWIN__)
	// this will store the fully-qualified path
	char psp_config_path[MAX_PATH] = "";
	
	// fetch the path of the executable
	if(GetModuleFileName(0, psp_config_path, sizeof(psp_config_path) - 1) == 0)
	{
	  // fall back
	  strcpy(psp_config_path, argv[0]);
	}
#endif
	if(process_args(argc, argv))
	{
	#if defined(__MINGW32__) && !defined(__CYGWIN__)
		print_path(psp_config_path);
	#else
		print_path(argv[0]);
	#endif
	}
	else
	{
		print_help();
	}

	return 0;
}
