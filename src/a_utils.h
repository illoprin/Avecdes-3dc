#ifndef A_UTILS_H
#define A_UTILS_H

#include "deps.h"
#include "defs.h"


char* get_full_path(const char* assets_path, const char* concat_with)
{
	char* fullpath = (char*)malloc(sizeof(char) * PATH_CHAR_MAX);
	strcpy(fullpath, concat_with);
	strcat(fullpath, assets_path);
	printf("Full path: %s\n", fullpath);
	return fullpath;
};

int file_read_lines(FILE* fs, char** dest)
{
	char buffer[MAX_LINE];
	
	unsigned line_len;
	unsigned line_count = 0;
	while (fgets(buffer, MAX_LINE, fs) != NULL)
	{
		line_len = strlen(buffer);
		if (line_count == 0)
		{
			// Plus one byte for \0 symbol
			*dest = (char*)malloc(line_len + 1);
			if (*dest == NULL)
            {
                fprintf(stderr, "FileReadLines: ERROR Could not allocate memory for destination string.\n");
                return 1;
            }
			(*dest)[0] = '\0';
		}
		else
		{
			unsigned prev_len = strlen(*dest);
			// Plus one byte for \0 symbol
			*dest = (char*)realloc(*dest, line_len + prev_len + 1);
			if (*dest == NULL)
            {
                fprintf(stderr, "FileReadLines: ERROR Could not reallocate memory for destination string.\n");
                free(*dest); // Release memory
                return 1;
            }
		}
		strncat(*dest, buffer, line_len);
		line_count++;
	}
	if (strlen(*dest) > 1)
		return 0;
	else
	{
		fprintf(stderr, "FileReadLines: WARNING Length of destination string is less then 1\n");
		return 1;
	}
}


#endif