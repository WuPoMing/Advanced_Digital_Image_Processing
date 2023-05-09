#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include "Header.h"

void hw1_1_2b() {
	// initial variable
	char  input_img[] = "HM1_images_file/lena256.raw";                 // Input  raw image name
	char output_img[] = "output_images_file/lena256_out.raw";              // Output raw image name
	FILE* input_file;
	FILE* output_file;
	int width = 256;
	int height = 256;
	int size = width * height;
	unsigned char* img_lena = new unsigned char[size]; // array for image data

	// read file
	input_file = fopen(input_img, "rb");

	if (input_file == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}

	fread(img_lena, 1, size, input_file);

	// save image as raw format
	output_file = fopen(output_img, "wb");
	fwrite(img_lena, 1, size, output_file);
	printf("Save %s successfully...\n", output_img);

	// release memory
	delete[] img_lena;
	fclose(input_file);
	fclose(output_file);
}