#ifndef A_LOG_H
#define A_LOG_H

#include "deps.h"

typedef struct a_Logger {
	FILE* log_file;
} a_Logger;

a_Logger* loggerInit (const char* file_path);
extern void lLog(a_Logger* logger, const char* format, ...);
extern void loggerRelease(a_Logger* logger);

#endif