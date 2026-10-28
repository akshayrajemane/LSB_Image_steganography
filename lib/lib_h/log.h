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

typedef enum 
{
	LOG_INFO, //0
	LOG_WARNING, //1
	LOG_ERROR, //2
	LOG_DEBUG //3
} LOG_LEVEL; //4

void get_log_file_path(char *file_path);
void create_log_file(char *log_file_path);
int logger(char *log_file_path, char *msg);
void log_info(char *log_file_path, int time_stamp, char *f_name, char *msg);
void log_warning(char *log_file_path, int time_stamp, char *f_name, char *msg);
void log_error(char *log_file_path, int time_stamp, char *f_name, char *msg);
void log_debug(char *log_file_path, int time_stamp, char *f_name, char *msg);

#endif
