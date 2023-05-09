#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include "Header.h"

void hw1_1_2c() {
	// initial variable
	char  input_img[] = "HM1_images_file/lena256.raw";                 // Input raw image name
	char output_img[] = "output_images_file/lena256_out_1_2c.raw";              // Output raw image name
	FILE* input_file;
	FILE* output_file;
	int width = 256;
	int height = 256;
	int size = width * height;
	unsigned char* img_lena = new unsigned char[size];	// array for image data
	unsigned char* lena256_out_1_2c = new unsigned char[size];

	// read file
	input_file = fopen(input_img, "rb");

	if (input_file == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}

	fread(img_lena, 1, size, input_file);

	// processing
	for (int row = 0; row < 128; row++) {
		for (int col = 0; col < 128; col++) {
			*(lena256_out_1_2c + row * 256 - col + 127) = *(img_lena + row * 256 + col);	// upper_left
			*(lena256_out_1_2c + row * 256 - col + 255) = *(img_lena + col * 256 + row + 127);	// upper_right
			*(lena256_out_1_2c + (row + 127) * 256 + col) = *(img_lena + (col + 127) * 256 + row);	// bottom_left
			*(lena256_out_1_2c + (row + 127) * 256 + col + 127) = *(img_lena + (row + 127) * 256 + col + 127);	// bottom_left
		}
	}

	// save image as raw format
	output_file = fopen(output_img, "wb");
	fwrite(lena256_out_1_2c, 1, size, output_file);
	printf("Save %s successfully...\n", output_img);

	// release memory
	delete[] img_lena;
	delete[] lena256_out_1_2c;
	fclose(input_file);
	fclose(output_file);
}