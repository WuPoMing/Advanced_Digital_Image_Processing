#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include "Header.h"

void hw1_1_2a() {
	// initial variable
	char  input_img[] = "HM1_images_file/lena256.raw";	// Input raw image name
	FILE* input_file;
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

	// print
	printf("The intensity values of the pixel at the coordinate of the 123rd row & 234th column is: %d\n", *(img_lena + 256 * 123 + 234));
	printf("The intensity values of the 5043th pixel stored in lena.256.raw file is: %d\n", *(img_lena + 5043));

	// release memory
	delete[] img_lena;
	fclose(input_file);
}