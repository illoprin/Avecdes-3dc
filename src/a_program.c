#ifndef A_PROGRAM_C
#define A_PROGRAM_C

#include "a_program.h"

/*
 * ShaderProgram
 * Constructor
*/
a_Program* programInit(a_Logger* logger, const char* vs_filename, const char* fs_filename)
{
	if (!vs_filename || !fs_filename ||
		 strlen(vs_filename) < 2 || strlen(fs_filename) < 2)
	{
		fprintf(stderr, "a_Program: Could not load shader program\n");
		return NULL;
	}
	char* vs_full_path = get_full_path(vs_filename, "assets/shaders/");
	char* fs_full_path = get_full_path(fs_filename, "assets/shaders/");
	
	// Open vertex shader
	FILE* vs_source_file = fopen(vs_full_path, "r");

	if (!vs_source_file)
	{
		lLog(logger, "[ERROR] a_Program: Could not open Vertex shader file on path %s\n", vs_full_path);
		return NULL;
	}

	char* vs_source = NULL;
	if (file_read_lines(vs_source_file, &vs_source))
	/* CASE: String length of source file is less then one */
	{
		lLog(logger, "[WARNING] a_Program init: shader source string is less then one %s\n", vs_full_path);
		return NULL;
	}

	
	// Open fragment shader
	FILE* fs_source_file = fopen(fs_full_path, "r");

	if (!fs_source_file)
	{
		lLog(logger, "[ERROR] a_Program: Could not open Fragment shader file on path %s\n", fs_full_path);
		return NULL;
	}

	char* fs_source = NULL;
	if (file_read_lines(fs_source_file, &fs_source))
	/* CASE: String length of source file is less then one */
	{
		lLog(logger, "[WARNING] a_Program init: shader source string is less then one %s\n", fs_full_path);
		return NULL;
	}

	/* == Release files and helper strings == */
	// Free path strings
	free(vs_full_path);
	free(fs_full_path);

	// Close files
	fclose(vs_source_file); // Close vertex shader file
	fclose(fs_source_file); // Close fragment shader file
	/* ===================================== */

	a_Program* prog = (a_Program*)malloc(sizeof(a_Program));
	prog->logger = logger;

	// Compile vertex and fragment shader
	programCompileShader(logger, &vs_source, &prog->vs, GL_VERTEX_SHADER);
	programCompileShader(logger, &fs_source, &prog->fs, GL_FRAGMENT_SHADER);
	// Create programs and link shaders
	programLink(logger, &prog->vs, &prog->fs, &prog->id);

	// Free source files
	free(vs_source);
	free(fs_source);
	return prog;
}

/*f
	Compile Vertex and Fragment shaders
	Returns compiled compild vertex and fragment shader indices
*/
void programCompileShader(a_Logger* logger, char** source, unsigned* id, GLuint type)
{
	*id = glCreateShader(type);
	glShaderSource(*id, 1, (const GLchar * const*)source, NULL);
	glCompileShader(*id);
	int success;
	char log[512];
	glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*id, 512, NULL, log);
		lLog(logger, "[ERROR] Shader: Could not compile %X shader\nError log:\n%s\n", type, log);
	}
	lLog(logger, "[INFO] Program: Shader id %d compiled successfully!\n", *id);
}

void programLink(a_Logger* logger, unsigned* vs_id, unsigned* fs_id, unsigned* pr_id)
{
	*pr_id = glCreateProgram();
	glAttachShader(*pr_id, *vs_id);
	glAttachShader(*pr_id, *fs_id);
	glLinkProgram(*pr_id);
	int success; char log[512];
	glGetProgramiv(*pr_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*pr_id, 512, NULL, log);
		lLog(logger,
			"[ERROR] Program: Could not link program with id %d\nError log:\n%s\n", *pr_id, log);
	}
	lLog(logger, "[INFO] Program: Program id %d linked successfully!\n", *pr_id);
}

GLuint getUniformID(a_Program* prog, const char* uniform_name)
{
	GLint id = glGetUniformLocation(prog->id, uniform_name);
	if (id >= 0)
		return id;
	else
	{
		lLog(prog->logger, "[WARNING] Program: Non-existent uniform with name %s\n", uniform_name);
		return -1;
	}
}

void programSetFloatUniform(a_Program* prog, float value, const char* uniform_name)
{
	GLint id = getUniformID(prog, uniform_name);
	if (id >= 0) glUniform1f(id, value);
}

void programSetIntUniform(a_Program* prog, int value, const char* uniform_name)
{
	GLint id = getUniformID(prog, uniform_name);
	if (id >= 0) glUniform1i(id, value);
}

void programSetVector3Uniform(a_Program* prog, vec3 value, const char* uniform_name)
{
	GLint id = getUniformID(prog, uniform_name);
	if (id >= 0) glUniform3f(id, (GLfloat)value[0], (GLfloat)value[1], (GLfloat)value[2]);
}

void programSetVector2Uniform(a_Program* prog, vec2 value, const char* uniform_name)
{
	GLint id = getUniformID(prog, uniform_name);
	if (id >= 0) glUniform2f(id, (GLfloat)value[0], (GLfloat)value[1]);
}

void programSetMatrix4Uniform(a_Program* prog, mat4 value, const char* uniform_name)
{
	GLint id = getUniformID(prog, uniform_name);
	if (id >= 0) glUniformMatrix4fv(id, 1, GL_FALSE, (const GLfloat *)value[0]);
}

void programUse(a_Program* program)
{
	glUseProgram(program->id);
}

void programRelease(a_Program* program)
{
	if (program)
	{
		// Detach shaders
		glDetachShader(program->id, program->vs);
		glDetachShader(program->id, program->fs);
		// Delete shaders from OpenGL
		glDeleteShader(program->vs);
		glDeleteShader(program->fs);
		// Delete program
		glDeleteProgram(program->id);
		// Log about that
		lLog(program->logger,
			"[INFO] Program: Shaders id vs-%d and fs-%d and program id %d released\n",
			program->vs, program->fs, program->id);
		// Release resources
		free(program);
	}
}

#endif
