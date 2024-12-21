#ifndef A_TEXTURE_H
#define A_TEXTURE_H

#include "deps.h"

typedef GLuint a_Texture_t;

a_Texture_t loadTexture(const char* assets_path);
extern void writeImage(const char* path_and_name, char* byte_data);

#endif