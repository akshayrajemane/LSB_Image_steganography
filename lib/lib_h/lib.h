#ifndef LIB_H
#define LIB_H

#ifdef _WIN32
	#define WIN32_OS 1
	#define WIN64_OS 0
	#define LIN_OS 0
#elif _WIN64
	#define WIN32_OS 0
	#define WIN64_OS 1
	#define LIN_OS 0
#elif __linux__
	#define _GNU_SOURCE
	#define WIN32_OS 0
	#define WIN64_OS 0
	#define LIN_OS 1
#endif


#include <stdio.h>
#include <time.h>

void get_time(double *time_s, double *time_ns);
int get_time_stamp(double start_time_s, double start_time_ns);

#endif
