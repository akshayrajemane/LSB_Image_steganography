#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

#include "globals.h"

int get_input_secret_message_file_path(const char *file_name, char *full_file_path);
int get_input_cover_medium_file_path(const char *file_name, char *full_file_path);
int get_file_paths_from_file_names();
int get_new_header_from_bmp_image_file(bmp_bit_map_new_header *new_header);
int check_cover_medium_image_file_ok();

#endif