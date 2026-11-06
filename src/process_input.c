#include "process_input.h"

int get_input_secret_message_file_path(const char *file_name, char *full_file_path)
{
	char *relative_path = "\\data\\secret_msg\\txt\\";
	
	if(getcwd(full_file_path, MAX_PATH_SIZE) == NULL)
	{
		printf("Error, getting the current working directory path.\n");
		return -1;
	}
	else
	{
		strcat(full_file_path, relative_path);
		strcat(full_file_path, file_name);
		return 0;
	}		
}

int get_input_cover_medium_file_path(const char *file_name, char *full_file_path)
{
	char *relative_path;
	char *ext = strchr(file_name, '.');

	if(ext == NULL)
	{
		printf("Error finding the file type.\n");
		return -1;
	}
	else
	{
		if(!strcmp(ext,".txt"))
		{
			relative_path = "\\data\\cover_medium\\txt\\";
		}
		else if(!strcmp(ext,".jpg") || !strcmp(ext,".png") || !strcmp(ext,".jpeg") || !strcmp(ext,".bmp"))
		{
			relative_path = "\\data\\cover_medium\\img\\";			
		}
		else if(!strcmp(ext,".mp3") || !strcmp(ext,".wav"))
		{
			relative_path = "\\data\\cover_medium\\aud\\";			
		}
		else if(!strcmp(ext,".mp4") || !strcmp(ext,".mkv") || !strcmp(ext,".avi"))
		{
			relative_path = "\\data\\cover_medium\\vid\\";			
		}
		else if(!strcmp(ext,".bin"))
		{
			relative_path = "\\data\\cover_medium\\bin\\";
		}
		else
		{
			printf("Unknown file type.\n");
			return -1;
		}
	}
	
	if(getcwd(full_file_path, MAX_PATH_SIZE) == NULL)
	{
		printf("Error, getting the current working directory path.\n");
		return -1;
	}
	else
	{
		strcat(full_file_path, relative_path);
		strcat(full_file_path, file_name);
		return 0;
	}	
	
}