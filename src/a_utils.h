#ifndef A_UTILS_H
#define A_UTILS_H

#include "deps.h"

/* -- Files */
char* get_full_path(const char* assets_path, const char* concat_with);
int file_read_lines(FILE* fs, char** dest);

/* -- Math */
float getFovH(float fov_v, float aspect);

#endif