#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
	#include <direct.h>
#elif _WIN64
	#include <direct.h>
#elif __linux__
	#include <unistd.h>
#else //Default OS is Windows
	#include <direct.h>
#endif


#include "config.h"

extern char secret_msg_file_path[MAX_PATH_SIZE];

#endif