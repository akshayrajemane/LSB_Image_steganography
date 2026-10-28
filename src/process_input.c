#include "process_input.h"

int get_input_cover_medium_file_path(char *file, char *file_path)
{
	char prj_dir_path[MAX_PATH_SIZE];
	char file_name[MAX_FILE_NAME_SIZE];
	char extension[MAX_FILE_NAME_SIZE];
	
	if(getcwd(prj_dir_path, MAX_PATH_SIZE) == 0)
	{
		//Later put log_error
		printf("Error : process_input.c project directory path not found.\n");
		file_path = NULL;
		return 1; //error
	}
	
	char temp[MAX_FILE_NAME_SIZE];
	int i=0;
	while(*file != '\0')
	{
		if(*file != '.')
		{
			temp[i] = *file;
			i++;
			
		}
		else
		{
			temp[i] = '\0';
			strcpy(file_name,temp);
			i=0;
			temp[0] = '\0';	
		}
		file++;
	}
	temp[i] = '\0';
	strcpy(extension,temp);
	
	strcpy(file_path, prj_dir_path);
	
	if(strcmp(extension,"txt") == 0) //Text files
	{
		strcat(file_path, "\\data\\cover_medium\\txt\\");
	}
	else if(strcmp(extension,"jpg") == 0 || strcmp(extension,"png") == 0 || strcmp(extension,"jpeg") == 0) //Image files
	{
		strcat(file_path, "\\data\\cover_medium\\img\\");
	}
	else if(strcmp(extension,"mp3") == 0 || strcmp(extension,"wav") == 0) //Audio files
	{
		strcat(file_path, "\\data\\cover_medium\\audi\\");
	}
	else if(strcmp(extension,"mp4") == 0 || strcmp(extension,"mkv") == 0 || strcmp(extension,"avi") == 0) //Video files
	{
		strcat(file_path, "\\data\\cover_medium\\vid\\");
	}
	else if(strcmp(extension,"bin") == 0 || strcmp(extension,"exe") == 0) //Binary files
	{
		strcat(file_path, "\\data\\cover_medium\\bin\\");
	}
	else
	{
		printf("Error: Unknown file type.\n");
		file_path = NULL;
		return 1; //error
	}
	
	strcat(file_path, file_name);
	strcat(file_path, ".");
	strcat(file_path, extension);
	return 0;
}


int get_input_secret_message_file_path(char *file, char *file_path)
{
	char prj_dir_path[MAX_PATH_SIZE];
	char file_name[MAX_FILE_NAME_SIZE];
	char extension[MAX_FILE_NAME_SIZE];
	
	if(getcwd(prj_dir_path, MAX_PATH_SIZE) == 0)
	{
		//Later put log_error
		printf("Error : process_input.c project directory path not found.\n");
		file_path = NULL;
		return 1; //error
	}
	
	char temp[MAX_FILE_NAME_SIZE];
	int i=0;
	while(*file != '\0')
	{
		if(*file != '.')
		{
			temp[i] = *file;
			i++;
			
		}
		else
		{
			temp[i] = '\0';
			strcpy(file_name,temp);
			i=0;
			temp[0] = '\0';	
		}
		file++;
	}
	temp[i] = '\0';
	strcpy(extension,temp);
	
	strcpy(file_path, prj_dir_path);
	
	if(strcmp(extension,"txt") == 0) //Text files
	{
		strcat(file_path, "\\data\\secret_msg\\txt\\");
	}
	else if(strcmp(extension,"jpg") == 0 || strcmp(extension,"png") == 0 || strcmp(extension,"jpeg") == 0) //Image files
	{
		strcat(file_path, "\\data\\secret_msg\\img\\");
	}
	else if(strcmp(extension,"mp3") == 0 || strcmp(extension,"wav") == 0) //Audio files
	{
		strcat(file_path, "\\data\\secret_msg\\audi\\");
	}
	else if(strcmp(extension,"mp4") == 0 || strcmp(extension,"mkv") == 0 || strcmp(extension,"avi") == 0) //Video files
	{
		strcat(file_path, "\\data\\secret_msg\\vid\\");
	}
	else if(strcmp(extension,"bin") == 0 || strcmp(extension,"exe") == 0) //Binary files
	{
		strcat(file_path, "\\data\\secret_msg\\bin\\");
	}
	else
	{
		printf("Error: Unknown file type.\n");
		file_path = NULL;
		return 1; //error
	}
	
	strcat(file_path, file_name);
	strcat(file_path, ".");
	strcat(file_path, extension);
	return 0;
}
