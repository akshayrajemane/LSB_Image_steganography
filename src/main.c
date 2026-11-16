#include "globals.h"
#include "process_input.h"
#include "encode.h"

//Global Variables
double start_time_s;
double start_time_ns;

char secret_msg_txt_file_name[MAX_FILE_NAME_SIZE] = "msg.txt";
char secret_msg_txt_file_path[MAX_PATH_SIZE] = " ";
char cover_medium_bmp_image_file_name[MAX_FILE_NAME_SIZE] = "image.bmp";
char cover_medium_bmp_image_file_path[MAX_PATH_SIZE] = "";
char stego_object_file_path[MAX_PATH_SIZE] = "";

bmp_bit_map_new_header bmp_new_header;
	
	
void init()
{
	get_time(&start_time_s, &start_time_ns);
	create_log_file();
	get_file_paths_from_file_names();
}

int main()
{
	init();
	
	get_new_header_from_bmp_image_file(&bmp_new_header);
	if(bmp_new_header.file_header.bfType == 0x4D42)
	{
		log_info(get_time_stamp(start_time_s,start_time_ns), "main.c", "Valid BMP file.");
		check_cover_medium_image_file_ok();
		if(encode_secret_message_data(secret_msg_txt_file_path, cover_medium_bmp_image_file_path))
		{
			log_error(get_time_stamp(start_time_s,start_time_ns), "main.c", "Error encoding secret message data.");
		}
	}
	
	
	return 0;
}

