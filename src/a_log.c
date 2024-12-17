#ifndef A_LOG_C
#define A_LOG_C

#include "a_log.h"

a_Logger* loggerInit (const char* dir_path)
{
	a_Logger* logger = (a_Logger*)malloc(sizeof(a_Logger));
	if (logger == NULL)
	{
		fprintf(stderr, "Cannot allocate memory for logger\n");
		exit(EXIT_FAILURE);
	}

	char file_path[PATH_CHAR_MAX];
	char file_name[PATH_CHAR_MAX - strlen(dir_path)];
	time_t current_time = time(NULL);
	strftime(
		file_name, 
		PATH_CHAR_MAX - strlen(dir_path), 
		"%d.%m.%Y %H:%M:%S", 
		localtime(&current_time)
	);
	snprintf(file_path, PATH_CHAR_MAX, "%s/%s.log", dir_path, file_name);

	logger->log_file = fopen(file_path, "w");
	if (logger->log_file == NULL)
	{
        fprintf(stderr, "Logger: %s Cannot open log file for writing\n", file_path);
        free(logger);
		exit(EXIT_FAILURE);
    }
	return logger;
};

extern void lLog(a_Logger* logger, const char* format, ...)
{
	/* VaList can be passed once to func that receives va_list */
	va_list args, args2;
	va_start(args, format);
	va_copy(args2, args);
	// print stdout
	vprintf(format, args); 
	va_end(args);
	// print to file
	vfprintf(logger->log_file, format, args2); 
	va_end(args2);

	/* Write buffer to file */
	fflush(logger->log_file);
};

extern void loggerRelease(a_Logger* logger)
{
	if (logger != NULL)
	{
		if (logger->log_file != NULL)
			fclose(logger->log_file);
		free(logger);
	}
};

#endif