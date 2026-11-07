#include "process_input.h"

int get_input_secret_message_file_path(const char *file_name, char *full_file_path)
{
	char *relative_path = "\\data\\secret_msg\\txt\\";
	
	if(getcwd(full_file_path, MAX_PATH_SIZE) == NULL)
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Error, getting the current working directory path.");
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
		log_error(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Error, finding the file type.");
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
			log_warning(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Unknown file type.");
			return -1;
		}
	}
	
	if(getcwd(full_file_path, MAX_PATH_SIZE) == NULL)
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Error, getting the current working directory path.");
		return -1;
	}
	else
	{
		strcat(full_file_path, relative_path);
		strcat(full_file_path, file_name);
		return 0;
	}	
	
}

int get_file_paths_from_file_names()
{
	if(get_input_cover_medium_file_path(cover_medium_bmp_image_file_name, cover_medium_bmp_image_file_path))
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Error getting cover medium image file path.");
		return -1;
	}
	
	if(get_input_secret_message_file_path(secret_msg_txt_file_name, secret_msg_txt_file_path))
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Error getting secret message txt file path");
		return -1;
	}
	
	return 0;
}

int get_new_header_from_bmp_image_file(bmp_bit_map_new_header *new_header)
{
	FILE* fptr = fopen(cover_medium_bmp_image_file_path, "rb");
		
	if(fptr == NULL)
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Error opening cover medium image file.");
		return -1;
	}
	else
	{
		if(fread(&(new_header->file_header.bfType), sizeof(new_header->file_header.bfType), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->file_header.bfType));
		}
		
		if(fread(&(new_header->file_header.bfSize), sizeof(new_header->file_header.bfSize), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->file_header.bfSize));
		}
		
		if(fread(&(new_header->file_header.bfReserved1), sizeof(new_header->file_header.bfReserved1), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->file_header.bfReserved1));
		}
		
		if(fread(&(new_header->file_header.bfReserved2), sizeof(new_header->file_header.bfReserved2), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->file_header.bfReserved2));
		}
		
		if(fread(&(new_header->file_header.bfOffBits), sizeof(new_header->file_header.bfOffBits), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->file_header.bfOffBits));
		}
		
	}
	
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfType = %X", new_header->file_header.bfType);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfSize = %d", new_header->file_header.bfSize);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfReserved1 = %d", new_header->file_header.bfReserved1);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfReserved2 = %d", new_header->file_header.bfReserved2);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfOffBits = %d", new_header->file_header.bfOffBits);
	
	if(new_header->file_header.bfType == 0x4D42)
	{
		log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Valid BMP file.");
		
		if(fread(&(new_header->info_header.biSize), sizeof(new_header->info_header.biSize), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biSize));
		}
		
		if(fread(&(new_header->info_header.biWidth), sizeof(new_header->info_header.biWidth), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biWidth));
		}
		
		if(fread(&(new_header->info_header.biHeight), sizeof(new_header->info_header.biHeight), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biHeight));
		}
		
		if(fread(&(new_header->info_header.biPlanes), sizeof(new_header->info_header.biPlanes), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biPlanes));
		}
		
		if(fread(&(new_header->info_header.biBitCount), sizeof(new_header->info_header.biBitCount), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biBitCount));
		}
		
		if(fread(&(new_header->info_header.biCompression), sizeof(new_header->info_header.biCompression), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biCompression));
		}
		
		if(fread(&(new_header->info_header.biSizeImage), sizeof(new_header->info_header.biSizeImage), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biSizeImage));
		}
		
		if(fread(&(new_header->info_header.biXPelsPerMeter), sizeof(new_header->info_header.biXPelsPerMeter), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biXPelsPerMeter));
		}
		
		if(fread(&(new_header->info_header.biYPelsPerMeter), sizeof(new_header->info_header.biYPelsPerMeter), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biYPelsPerMeter));
		}
		
		if(fread(&(new_header->info_header.biClrUsed), sizeof(new_header->info_header.biClrUsed), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biClrUsed));
		}
		
		if(fread(&(new_header->info_header.biClrImportant), sizeof(new_header->info_header.biClrImportant), 1, fptr) == 1)
		{
			log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Successfully read the %lld bytes of infomation from file header", sizeof(new_header->info_header.biClrImportant));
		}
	}
	else
	{
		log_error(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Error: Incorrect BMP file.");
		fclose(fptr);
		return -1;
	}
	
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "Printing header information...");

	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfType = %X", new_header->file_header.bfType);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfSize = %d", new_header->file_header.bfSize);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfReserved1 = %d", new_header->file_header.bfReserved1);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfReserved2 = %d", new_header->file_header.bfReserved2);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "bfOffBits = %d", new_header->file_header.bfOffBits);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "");
	
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biSize = %d", new_header->info_header.biSize);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biWidth = %d", new_header->info_header.biWidth);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biHeight = %d", new_header->info_header.biHeight);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biPlanes = %d", new_header->info_header.biPlanes);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biBitCount = %d", new_header->info_header.biBitCount);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biCompression = %d", new_header->info_header.biCompression);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biSizeImage = %d", new_header->info_header.biSizeImage);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biXPelsPerMeter = %d", new_header->info_header.biXPelsPerMeter);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biYPelsPerMeter = %d", new_header->info_header.biYPelsPerMeter);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biClrUsed = %d", new_header->info_header.biClrUsed);
	log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "biClrImportant = %d", new_header->info_header.biClrImportant);
	
	fclose(fptr);		
	return 0;
	
}

int check_cover_medium_image_file_ok()
{
	long int byte_image_pixel_data_size;
	long int byte_txt_file_size = 0;
	long int required_pixel_data_size = 0;
	
	
	bmp_bit_map_new_header new_header;
	get_new_header_from_bmp_image_file(&new_header);
	
	byte_image_pixel_data_size = new_header.info_header.biWidth * new_header.info_header.biHeight * new_header.info_header.biBitCount;
	//byte_txt_file_size = function_call(check_txt_file_size);
	
	required_pixel_data_size += 2;						//2 Bytes - (#*) Magic string
	required_pixel_data_size += 4;						//4 Bytes - File extension length
	required_pixel_data_size += 4;						//4 Bytes - (.txt) File extension
	required_pixel_data_size += 4;						//4 Bytes - secret message data size
	required_pixel_data_size += byte_txt_file_size;     //n Bytes - secret message size
	required_pixel_data_size *= 8;						//multiplication factor - 8 Bytes needed to embedded 1 Byte of data
	
	if(byte_image_pixel_data_size > required_pixel_data_size)
	{
		log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "BMP image file is ok!");
		return 0;
	}
	else
	{
		log_info(get_time_stamp(start_time_s,start_time_ns), "process_input.c", "BMP image file is NOT ok!");
		return -1;
	}
	
}