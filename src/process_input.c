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

int get_file_paths_from_file_names()
{
	if(get_input_cover_medium_file_path(cover_medium_bmp_image_file_name, cover_medium_bmp_image_file_path))
	{
		printf("process_input.h : Error getting cover medium image file path\n");
		return -1;
	}
	
	if(get_input_secret_message_file_path(secret_msg_txt_file_name, secret_msg_txt_file_path))
	{
		printf("process_input.h : Error getting secret message txt file path\n");
		return -1;
	}
	
	return 0;
}

int get_new_header_from_bmp_image_file(bmp_bit_map_new_header *new_header)
{
	FILE* fptr = fopen(cover_medium_bmp_image_file_path, "rb");
		
	if(fptr == NULL)
	{
		printf("process_input.h : Error opening cover medium image file.\n");
		return -1;
	}
	else
	{
		if(fread(&(new_header->file_header.bfType), sizeof(new_header->file_header.bfType), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->file_header.bfType));
		}
		
		if(fread(&(new_header->file_header.bfSize), sizeof(new_header->file_header.bfSize), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->file_header.bfSize));
		}
		
		if(fread(&(new_header->file_header.bfReserved1), sizeof(new_header->file_header.bfReserved1), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->file_header.bfReserved1));
		}
		
		if(fread(&(new_header->file_header.bfReserved2), sizeof(new_header->file_header.bfReserved2), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->file_header.bfReserved2));
		}
		
		if(fread(&(new_header->file_header.bfOffBits), sizeof(new_header->file_header.bfOffBits), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->file_header.bfOffBits));
		}
		
	}
	
	printf("bfType = %X\n", new_header->file_header.bfType);
	printf("bfSize = %d\n", new_header->file_header.bfSize);
	printf("bfReserved1 = %d\n", new_header->file_header.bfReserved1);
	printf("bfReserved2 = %d\n", new_header->file_header.bfReserved2);
	printf("bfOffBits = %d\n", new_header->file_header.bfOffBits);
	
	if(new_header->file_header.bfType == 0x4D42)
	{
		printf("Valid BMP file.\n");
		
		if(fread(&(new_header->info_header.biSize), sizeof(new_header->info_header.biSize), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biSize));
		}
		
		if(fread(&(new_header->info_header.biWidth), sizeof(new_header->info_header.biWidth), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biWidth));
		}
		
		if(fread(&(new_header->info_header.biHeight), sizeof(new_header->info_header.biHeight), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biHeight));
		}
		
		if(fread(&(new_header->info_header.biPlanes), sizeof(new_header->info_header.biPlanes), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biPlanes));
		}
		
		if(fread(&(new_header->info_header.biBitCount), sizeof(new_header->info_header.biBitCount), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biBitCount));
		}
		
		if(fread(&(new_header->info_header.biCompression), sizeof(new_header->info_header.biCompression), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biCompression));
		}
		
		if(fread(&(new_header->info_header.biSizeImage), sizeof(new_header->info_header.biSizeImage), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biSizeImage));
		}
		
		if(fread(&(new_header->info_header.biXPelsPerMeter), sizeof(new_header->info_header.biXPelsPerMeter), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biXPelsPerMeter));
		}
		
		if(fread(&(new_header->info_header.biYPelsPerMeter), sizeof(new_header->info_header.biYPelsPerMeter), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biYPelsPerMeter));
		}
		
		if(fread(&(new_header->info_header.biClrUsed), sizeof(new_header->info_header.biClrUsed), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biClrUsed));
		}
		
		if(fread(&(new_header->info_header.biClrImportant), sizeof(new_header->info_header.biClrImportant), 1, fptr) == 1)
		{
			printf("Successfully read the %lld bytes of infomation from file header\n", sizeof(new_header->info_header.biClrImportant));
		}
	}
	else
	{
		printf("process_input.c, Error: Incorrect BMP file.\n");
		fclose(fptr);
		return -1;
	}
	
	printf("Printing header information...\n");
	
	printf("bfType = %X\n", (new_header->file_header.bfType));
	printf("bfSize = %d\n", new_header->file_header.bfSize);
	printf("bfReserved1 = %d\n", new_header->file_header.bfReserved1);
	printf("bfReserved2 = %d\n", new_header->file_header.bfReserved2);
	printf("bfOffBits = %d\n", new_header->file_header.bfOffBits);
	
	printf("biSize = %d\n", new_header->info_header.biSize);
	printf("biWidth = %d\n", new_header->info_header.biWidth);
	printf("biHeight = %d\n", new_header->info_header.biHeight);
	printf("biPlanes = %d\n", new_header->info_header.biPlanes);
	printf("biBitCount = %d\n", new_header->info_header.biBitCount);
	printf("biCompression = %d\n", new_header->info_header.biCompression);
	printf("biSizeImage = %d\n", new_header->info_header.biSizeImage);
	printf("biXPelsPerMeter = %d\n", new_header->info_header.biXPelsPerMeter);
	printf("biYPelsPerMeter = %d\n", new_header->info_header.biYPelsPerMeter);
	printf("biClrUsed = %d\n", new_header->info_header.biClrUsed);
	printf("biClrImportant = %d\n", new_header->info_header.biClrImportant);
	
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
		printf("BMP image file is ok!");
		return 0;
	}
	else
	{
		printf("BMP image file is NOT ok!");
		return -1;
	}
	
}