#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
	#include <direct.h>
	#include <stdint.h>
#elif _WIN64
	#include <direct.h>
	#include <stdint.h>
#elif __linux__
	#include <unistd.h>
#else //Default OS is Windows
	#include <direct.h>
	#include <unistd.h>
#endif


#include "config.h"

extern char secret_msg_txt_file_name[MAX_FILE_NAME_SIZE];
extern char secret_msg_txt_file_path[MAX_PATH_SIZE];
extern char cover_medium_bmp_image_file_name[MAX_FILE_NAME_SIZE];
extern char cover_medium_bmp_image_file_path[MAX_PATH_SIZE];


typedef struct //Total - 14 Bytes
{
	uint16_t bfType;		//must be BM 0x424D
	uint32_t bfSize;		//size of BMP file in byes
	uint16_t bfReserved1;	//must be 0
	uint16_t bfReserved2;	//must be 0
	uint32_t bfOffBits;		//starting byte address of image data
} bmp_bit_map_file_header;


//BIT_MAP_CORE_HEADER
typedef struct //Total - 12 Bytes
{
	uint32_t bcSize;		//must be 12 (size of this header file)
	uint16_t bcWidth;		//pixel width
	uint16_t bcHeight;		//pixel height
	uint16_t bcPlanes;		//No. of color planes
	uint16_t bcBitCount;	//bits per pixel
} bmp_bit_map_core_header;

//BIT_MAP_INFO_HEADER
typedef struct //Total - 40 Bytes
{
	uint32_t biSize;			//must be 40 (size of this header file) (can be 108 for BITMAPV4HEADER or 124 for BITMAPV5HEADER)
	uint32_t biWidth;			//pixel width
	uint32_t biHeight;			//pixel height (can be negative, can not be zero)
	uint16_t biPlanes;			//The number of color planes
	uint16_t biBitCount;		//bits per pixel (1,4,8,16.24,32)
	uint32_t biCompression;		//compression method being used.
	uint32_t biSizeImage;		//image size(pixel data size) (can be 0 for BI_RGB image)
	uint32_t biXPelsPerMeter;	//horizontal Resolution (pixel per meter)
	uint32_t biYPelsPerMeter;	//vertical Resolution (pixel per meter)
	uint32_t biClrUsed;			//color palette
	uint32_t biClrImportant;	//no. of important color table entries
} bmp_bit_map_info_header;

//BIT_MAP_V4_HEADER - extension to BIT_MAP_INFO_HEADER
typedef struct //Total - (108-40=68) Bytes
{
	uint32_t bV4RedMask;	//mask selecting red bits of each pixel
	uint32_t bV4GreeMask;	//mask selecting green bist of each pixel
	uint32_t bV4BlueMask;	//mask selecting blue bits of each pixel
	uint32_t bV4AlphaMask;	//mask selecting alpha bits of ach pixel
	uint32_t bV4CSType;		//color space of the DIB
	uint32_t bV4Endpoints0;	//xyz coordinates of RGB endpoints
	uint32_t bV4Endpoints1;	//xyz coordinates of RGB endpoints
	uint32_t bV4Endpoints2;	//xyz coordinates of RGB endpoints
	uint32_t bV4Endpoints3;	//xyz coordinates of RGB endpoints
	uint32_t bV4Endpoints4;	//xyz coordinates of RGB endpoints
	uint32_t bV4Endpoints5;	//xyz coordinates of RGB endpoints
	uint32_t bV4Endpoints6;	//xyz coordinates of RGB endpoints
	uint32_t bV4Endpoints7;	//xyz coordinates of RGB endpoints
	uint32_t bV4Endpoints8;	//xyz coordinates of RGB endpoints
	uint32_t bV4GammaRed;	//Gamma response curve for red
	uint32_t bV4GammaGreen;	//Gamma response curve for green
	uint32_t bV4GammaBlue;	//Gamma response curve for Blue
} bmp_bit_map_v4_header;

//BIT_MAP_V5_HEADER - extension to BIT_MAP_V4_HEADER
typedef struct //Total - (124-108=16)
{
	uint32_t bV5Intent;		//rendering intent
	uint32_t bV5ProfileData;//offset to ICC profile
	uint32_t bV5ProfileSize;//size in bytes of embedded profile data
	uint32_t bV5Reserved;	//must be zero
} bmp_bit_map_v5_header;

//BIT_MAP_OLD_HEADER - file_header + core_header
typedef struct //Total - (14+12=26)
{
	bmp_bit_map_file_header file_header;
	bmp_bit_map_core_header core_header;
} bmp_bit_map_old_header;

//BIT_MAP_NEW_HEADER - file_header + info_header + v4_header(optional) + v5_header(optional)
typedef struct //Total - (14+40+68+16=138)
{
	bmp_bit_map_file_header file_header;
	bmp_bit_map_info_header info_header;
	bmp_bit_map_v4_header v4_header;
	bmp_bit_map_v5_header v5_header;
} bmp_bit_map_new_header;

#endif