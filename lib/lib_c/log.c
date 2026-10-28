#include "log.h"

void get_log_file_path(char *file_path)
{
	if(getcwd(file_path, 1024) != NULL)
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

void create_log_file(char *log_file_path)
{
	FILE* fp;
	const char *data = "**********This is the start of log file**********";
	
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
		fputs("\n", fp);
		fclose(fp);
		return 0;
	}	
}

void log_info(char *log_file_path, int time_stamp, char *f_name, char *msg)
{
	int msg_size = strlen(msg);
	msg_size = msg_size + 128; //adding 128 bytes exter for time_stamp + INFO + file_name
	char data[msg_size];
	
	//Implement LOG_INFO level(info,warning,error,debug) check before printing message.
	sprintf(data,"[%d] [INFO] [%s] [%s] \n", time_stamp, f_name, msg);
	logger(log_file_path, data);
}

void log_warning(char *log_file_path, int time_stamp, char *f_name, char *msg)
{
	int msg_size = strlen(msg);
	msg_size = msg_size + 128; //adding 128 bytes exter for time_stamp + WARNING + file_name
	char data[msg_size];
	
	//Implement LOG_INFO level(info,warning,error,debug) check before printing message.
	sprintf(data,"[%d] [INFO] [%s] [%s] \n", time_stamp, f_name, msg);
	logger(log_file_path, data);
}

void log_error(char *log_file_path, int time_stamp, char *f_name, char *msg)
{
	int msg_size = strlen(msg);
	msg_size = msg_size + 128; //adding 128 bytes exter for time_stamp + ERROR + file_name
	char data[msg_size];
	
	//Implement LOG_INFO level(info,warning,error,debug) check before printing message.
	sprintf(data,"[%d] [INFO] [%s] [%s] \n", time_stamp, f_name, msg);
	logger(log_file_path, data);
}

void log_debug(char *log_file_path, int time_stamp, char *f_name, char *msg)
{
	int msg_size = strlen(msg);
	msg_size = msg_size + 128; //adding 128 bytes exter for time_stamp + DEBUG + file_name
	char data[msg_size];
	
	//Implement LOG_INFO level(info,warning,error,debug) check before printing message.
	sprintf(data,"[%d] [INFO] [%s] [%s] \n", time_stamp, f_name, msg);
	logger(log_file_path, data);
}

