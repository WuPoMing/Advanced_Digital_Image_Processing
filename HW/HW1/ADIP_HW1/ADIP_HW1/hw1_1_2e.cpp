#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include "Header.h"

void hw1_1_2e() {
	// initial variable
	char  input_img_A1[] = "HM1_images_file/A1.raw";	// Input raw image name
	char  input_img_A2[] = "HM1_images_file/A2.raw";
	char  input_img_A3[] = "HM1_images_file/A3.raw";
	char  input_img_A4[] = "HM1_images_file/A4.raw";
	char  input_img_A5[] = "HM1_images_file/A5.raw";
	char output_img[] = "output_images_file/out_1_2e.raw";	// Output raw image name
	FILE* input_file_A1;
	FILE* input_file_A2;
	FILE* input_file_A3;
	FILE* input_file_A4;
	FILE* input_file_A5;
	FILE* output_file;
	int width = 256;
	int height = 256;
	int size = width * height;
	unsigned char* img_A1 = new unsigned char[128 * 128];	// array for image data
	unsigned char* img_A2 = new unsigned char[128 * 64];
	unsigned char* img_A3 = new unsigned char[192 * 128];
	unsigned char* img_A4 = new unsigned char[192 * 192];
	unsigned char* img_A5 = new unsigned char[64 * 64];
	unsigned char* out_1_2e = new unsigned char[size];

	// read file
	input_file_A1 = fopen(input_img_A1, "rb");
	input_file_A2 = fopen(input_img_A2, "rb");
	input_file_A3 = fopen(input_img_A3, "rb");
	input_file_A4 = fopen(input_img_A4, "rb");
	input_file_A5 = fopen(input_img_A5, "rb");

	fread(img_A1, 1, 128 * 128, input_file_A1);
	fread(img_A2, 1, 128 * 64, input_file_A2);
	fread(img_A3, 1, 192 * 128, input_file_A3);
	fread(img_A4, 1, 192 * 192, input_file_A4);
	fread(img_A5, 1, 64 * 64, input_file_A5);

	// initialize output image
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			*(out_1_2e + i * 256 + j) = 0;
		}
	}

	// processing
	for (int row = 0; row < 128; row++) {
		for (int col = 0; col < 128; col++) {
			*(out_1_2e + (row + 128) * 256 + col) = *(img_A1 + row * 128 + col);
		}
	}
	for (int row = 0; row < 128; row++) {
		for (int col = 0; col < 64; col++) {
			*(out_1_2e + row * 256 + col) = *(img_A2 + col * 128 - row + 127);
		}
	 }
	for (int row = 0; row < 128; row++) {
		for (int col = 0; col < 192; col++) {
			*(out_1_2e + row * 256 + col + 64) = *(img_A3 + (127 - row) * 192 - col + 191);
		}
	}
	for (int row = 0; row < 192; row++) {
		for (int col = 0; col < 192; col++) {
			*(out_1_2e + (row + 64) * 256 - col + 255) |= *(img_A4 + col * 192 + row);
		}
	}
	for (int row = 0; row < 64; row++) {
		for (int col = 0; col < 64; col++) {
			*(out_1_2e + (row + 192) * 256 + col + 192) = *(img_A5 + col * 64 - row + 63);
		}
	}

	// save image as raw format
	output_file = fopen(output_img, "wb");
	fwrite(out_1_2e, 1, size, output_file);
	printf("Save %s successfully...\n", output_img);

	// release memory
	delete[] img_A1;
	delete[] img_A2;
	delete[] img_A3;
	delete[] img_A4;
	delete[] img_A5;
	delete[] out_1_2e;
	fclose(input_file_A1);
	fclose(input_file_A2);
	fclose(input_file_A3);
	fclose(input_file_A4);
	fclose(input_file_A5);
	fclose(output_file);
}