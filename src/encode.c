#include "encode.h"

void get_secret_msg_info(const char *file_name, secret_msg_info_header *header)
{
	strcpy(header->magic_string, "#*");
	
	char *extension = strchr(file_name, '.');
	header->file_extension_length = strlen(extension);
	
	strcpy(header->file_extension, extension);
	
	header->secret_msg_data_size = get_file_size(file_name);
}

int get_output_stego_object_file_path(const char *input_file_path, char *output_file_path)
{
	char *relative_path;
	char *file_name; 
	
	if(WIN32_OS || WIN64_OS)
	{
		file_name = strrchr(input_file_path, '\\');
		if(file_name == NULL)
		{
			log_error(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Error, finding the file name.");
			return -1;
		}
		file_name++;
	}
	
	if(LIN_OS)
	{
		file_name = strrchr(input_file_path, '/');
		if(file_name == NULL)
		{
			log_error(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Error, finding the file name.");
			return -1;
		}
		file_name++;
	}
	
	char *ext = strchr(file_name, '.');

	if(ext == NULL)
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Error, finding the file type.");
		return -1;
	}
	else
	{
		if(!strcmp(ext,".jpg") || !strcmp(ext,".png") || !strcmp(ext,".jpeg") || !strcmp(ext,".bmp"))
		{
			if(WIN32_OS || WIN64_OS)
			{
				relative_path = "\\out\\img\\";
			}
	
			if(LIN_OS)
			{
				relative_path = "/out/img/";
			}
		}
		else
		{
			log_warning(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Unknown file type.");
			return -1;
		}
	}
	
	if(getcwd(output_file_path, MAX_PATH_SIZE) == NULL)
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Error, getting the current working directory path.");
		return -1;
	}
	else
	{
		strcat(output_file_path, relative_path);
		strcat(output_file_path, file_name);
		return 0;
	}		
	
}


int encode_secret_message_data(const char *secret_msg_file_path, const char *cover_medium_file_path)
{
	secret_msg_info_header info_header;
	
	get_secret_msg_info(secret_msg_file_path, &info_header);
	
	FILE *secret_msg_fptr = fopen(secret_msg_file_path, "rb");
	if(secret_msg_fptr == NULL)
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Error opening secret message file.");
		return -1;
	}
	
	FILE *cover_medium_fptr = fopen(cover_medium_file_path, "rb");
	if(cover_medium_fptr == NULL)
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Error opening cover medium image file.");
		return -1;
	}
	
	char stego_object_file_path[MAX_PATH_SIZE];
	if(get_output_stego_object_file_path(cover_medium_file_path, stego_object_file_path))
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Error getting stego object file path.");
		return -1;
	}
	
	FILE *stego_object_fptr = fopen(stego_object_file_path, "wb");
	if(stego_object_fptr == NULL)
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Error creating stego object file.");
		return -1;
	}
	
	int pixel_image_data_offset = bmp_new_header.file_header.bfOffBits;
	uint8_t buffer[pixel_image_data_offset];

	if(fread(&buffer, sizeof(buffer), 1, cover_medium_fptr) == 1)
	{
		log_info(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Successfully read the %lld bytes of infomation from cover medium file.", sizeof(buffer));
	}	
	if(fwrite(&buffer, sizeof(buffer), 1, stego_object_fptr) == 1)
	{
		log_info(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Successfully write the %lld bytes of infomation to stego object file.", sizeof(buffer));
	}
	
	uint8_t byte_buff;
	int byte_count = 0;
	while(fread(&byte_buff, sizeof(byte_buff), 1, secret_msg_fptr) == 1)
	{
		for(int count=0; count<8; count++)
		{
			uint8_t temp_byte_buff;
			if(fread(&temp_byte_buff, sizeof(temp_byte_buff), 1, cover_medium_fptr) == 1)
			{
				if(byte_buff && 0x01 == 0x01) //If bit set
				{
					temp_byte_buff = temp_byte_buff || 0x01; //set bit
				}
				else //If bit clear
				{
					temp_byte_buff = temp_byte_buff && 0xFE; //clear bit
				}
			
				if(fwrite(&temp_byte_buff, sizeof(temp_byte_buff), 1, stego_object_fptr) == 1)
				{
					//Supressed this as it floods the log file
					//log_info(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Successfully write the %lld bytes of infomation to stego object file.", sizeof(temp_byte_buff));
					byte_count++;
				}
			
				byte_buff = byte_buff >> 1;
					
			}
		}
	}
	
	log_info(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Successfully write the %lld bytes of secret message data into stego object file.", byte_count);
	log_info(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Secret message data encoded into cover medium image file.");
	fclose(secret_msg_fptr);
	
	uint8_t buff;
	while(fread(&buff, sizeof(buff), 1, cover_medium_fptr) == 1)
	{
		if(fwrite(&buff, sizeof(buff), 1, stego_object_fptr) == 1)
		{
			//Supressed this as it floods the log file
			//log_info(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Successfully write the %lld bytes of infomation to stego object file.", sizeof(buff));
			byte_count++;
		}
	}
	log_info(get_time_stamp(start_time_s,start_time_ns), "encode.c", "Successfully write the %lld bytes of infomation to stego object file.", byte_count);
	fclose(cover_medium_fptr);
	fclose(stego_object_fptr);
	return 0;

}
