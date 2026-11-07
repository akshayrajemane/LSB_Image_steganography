#include "log.h"

char log_file_path[2048]; //Don't add into project globals untill necessary

void get_log_file_path(char *file_path)
{
	if(getcwd(file_path, 2048) != NULL)
	{
		printf("CWD path = %s\n", file_path);
		if(WIN32_OS || WIN64_OS)
		{
			strcat(file_path, "\\log\\log.txt");
		}
		
		if(LIN_OS)
		{
			strcat(file_path, "/log/log.txt");
		}
			
		printf("Log file path = %s\n", file_path);
	}
	else
	{
		printf("Failed to get CWD...\n");
	}
}

void create_log_file()
{
	FILE* fp;
	const char *data = "**********This is the start of log file**********";
	
	get_log_file_path(log_file_path);
	fp = fopen(log_file_path, "w");
	if(fp == NULL)
	{
		printf("Error: Log file is not created.\n");
	}
	else
	{
		printf("Log file is created successfully.\n");
		fputs(data, fp);
		fputs("\n", fp);
		fclose(fp);
	}
}

int logger(char *log_file_path, char *data)
{
	FILE* fp;
	
	fp = fopen(log_file_path, "a");
	if(fp == NULL)
	{
		printf("Error: Log file is not opening...\n");
		return -1;
	}
	else
	{
		fputs(data, fp);
		//fputs("\n", fp);
		fclose(fp);
		return 0;
	}	
}

void log_info(int time_stamp, char *f_name, const char *fmt, ...)
{	
	char buffer[4096];
	char data[4096 + 128]; //adding 128 bytes extera for time_stamp + INFO + file_name
	
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	
	//Implement LOG_INFO level(info,warning,error,debug) check before printing message.
	sprintf(data,"[%d] [INFO] [%s] [%s] \n", time_stamp, f_name, buffer);
	logger(log_file_path, data);
}

void log_warning(int time_stamp, char *f_name, const char *fmt, ...)
{
	char buffer[4096];
	char data[4096 + 128]; //adding 128 bytes extera for time_stamp + INFO + file_name
	
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	
	//Implement LOG_INFO level(info,warning,error,debug) check before printing message.
	sprintf(data,"[%d] [WARNING] [%s] [%s] \n", time_stamp, f_name, buffer);
	logger(log_file_path, data);
}

void log_error(int time_stamp, char *f_name, const char *fmt, ...)
{
	char buffer[4096];
	char data[4096 + 128]; //adding 128 bytes extera for time_stamp + INFO + file_name
	
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	
	//Implement LOG_INFO level(info,warning,error,debug) check before printing message.
	sprintf(data,"[%d] [ERROR] [%s] [%s] \n", time_stamp, f_name, buffer);
	logger(log_file_path, data);
}

void log_debug(int time_stamp, char *f_name, const char *fmt, ...)
{
	char buffer[4096];
	char data[4096 + 128]; //adding 128 bytes extera for time_stamp + INFO + file_name
	
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	
	//Implement LOG_INFO level(info,warning,error,debug) check before printing message.
	sprintf(data,"[%d] [DEBUG] [%s] [%s] \n", time_stamp, f_name, buffer);
	logger(log_file_path, data);
}

