#include <decode.h>

int get_input_stego_object_file_path(const char *input_file_path, char *output_file_path)
{

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


        if(getcwd(output_file_path, MAX_PATH_SIZE) == NULL)
        {
                log_error(get_time_stamp(start_time_s,start_time_ns), "decode.c", "Error, getting the current working directory path.");
                return -1;
        }


        if(WIN32_OS || WIN64_OS)
        {
                strcat(stego_object_file_path, "\\out\\img\\");
        }

        if(LIN_OS)
        {
                strcat(stego_object_file_path, "/out/img/");
        }

        strcat(stego_object_file_path, file_name);

        return 0;

}
