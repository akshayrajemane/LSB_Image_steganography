#ifndef ENCODE_H
#define ENCODE_H

#include "globals.h"

void get_secret_msg_info(const char *file_name, secret_msg_info_header *header);
int get_output_stego_object_file_path(const char *input_file_path, char *output_file_path);
int encode_secret_message_data(const char *secret_msg_file_path, const char *cover_medium_file_path);

#endif