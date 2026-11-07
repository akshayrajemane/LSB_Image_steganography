#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#define WIN32_OS 1
	#define WIN64_OS 0
	#define LIN_OS 0
	#include <direct.h>
#elif _WIN64
	#define WIN32_OS 0
	#define WIN64_OS 1
	#define LIN_OS 0
	#include <direct.h>
#elif __linux__
	#define _GNU_SOURCE
	#define WIN32_OS 0
	#define WIN64_OS 0
	#define LIN_OS 1
	#include <unistd.h>
#endif

#include <stdarg.h>

typedef enum 
{
	LOG_INFO, //0
	LOG_WARNING, //1
	LOG_ERROR, //2
	LOG_DEBUG //3
} LOG_LEVEL; //4

void get_log_file_path(char *file_path);
void create_log_file();
int logger(char *log_file_path, char *data);
void log_info(int time_stamp, char *f_name, const char *fmt, ...);
void log_warning(int time_stamp, char *f_name, const char *fmt, ...);
void log_error(int time_stamp, char *f_name, const char *fmt, ...);
void log_debug(int time_stamp, char *f_name, const char *fmt, ...);

#endif
