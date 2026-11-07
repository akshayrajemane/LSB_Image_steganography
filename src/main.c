#include "globals.h"
#include "process_input.h"

//Global Variables
char secret_msg_txt_file_name[MAX_FILE_NAME_SIZE] = "msg.txt";
char secret_msg_txt_file_path[MAX_PATH_SIZE] = " ";
char cover_medium_bmp_image_file_name[MAX_FILE_NAME_SIZE] = "image.bmp";
char cover_medium_bmp_image_file_path[MAX_PATH_SIZE] = "";

double start_time_s;
double start_time_ns;

void init()
{
	get_time(&start_time_s, &start_time_ns);
	create_log_file();
	get_file_paths_from_file_names();
}

int main()
{
	init();
	
	check_cover_medium_image_file_ok();
	
	
	return 0;
}

