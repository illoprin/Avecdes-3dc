#ifndef A_PROGRAM_H
#define A_PROGRAM_H

#include "deps.h"
#include "a_log.h"

typedef struct a_Program {
	a_Logger* logger;
	unsigned vs, fs;
	unsigned id;
} a_Program;

a_Program* programInit(a_Logger* logger, const char* vs_path, const char* fs_path);
void programUse(a_Program* program);
void programRelease(a_Program* program);
void programCompileShader(a_Logger* logger, char** source,
		unsigned* id, GLuint type);
void programLink(a_Logger* logger, unsigned* vs_id,
		unsigned* fs_id, unsigned* pr_id);

/* Attributes */
void programBindAttribute(a_Program* prog, GLuint id, const char* name);

/* Uniform Setters */
void programSetFloatUniform(a_Program* prog, float value, const char* uniform_name);
void programSetIntUniform(a_Program* prog, int value, const char* uniform_name);
void programSetVector3Uniform(a_Program* prog, vec3 value, const char* uniform_name);
void programSetVector2Uniform(a_Program* prog, vec2 value, const char* uniform_name);
void programSetMatrix4Uniform(a_Program* prog, mat4 value, const char* uniform_name);

#endif