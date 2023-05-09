#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include "Header.h"


void hw1_1_2d_horizontal() {
	// initial variable
	char  input_img[] = "HM1_images_file/lena256.raw";                 // Input raw image name
	char output_img[] = "output_images_file/lena256_out_1_2d_horizontal.raw";              // Output raw image name
	FILE* input_file;
	FILE* output_file;
	int width = 256;
	int height = 256;
	int size = width * height;
	unsigned char* img_lena = new unsigned char[size];	// array for image data
	unsigned char* lena256_out_1_2d_horizontal = new unsigned char[size];

	// read file
	input_file = fopen(input_img, "rb");

	if (input_file == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}

	fread(img_lena, 1, size, input_file);

	// random
	int x[8] = {0};
	for (int i = 0; i <= 7; i++) {
		x[i] = i;
	}
	time_t xx;
	srand((unsigned)time(NULL));	// 用時間重設亂數表

	for (int ii = 0; ii <= 1000; ii++) {
		// 產生0～7的亂數
		int n1 = rand() % 8;
		int n2 = rand() % 8;
		// 將陣列資料進行交換
		int temp = x[n1];
		x[n1] = x[n2];
		x[n2] = temp;
	}

	// processing
	for (int i = 0; i < 8; i++) {
		for (int row = 0; row < 32; row ++) {
			for (int col = 0; col < 256; col++) {
				*(lena256_out_1_2d_horizontal + (row + i * 32) * 256 + col) = *(img_lena + (row + x[i] * 32) * 256 + col);
			}
		}
	}

	// save image as raw format
	output_file = fopen(output_img, "wb");
	fwrite(lena256_out_1_2d_horizontal, 1, size, output_file);
	printf("Save %s successfully...\n", output_img);

	// release memory
	delete[] img_lena;
	delete[] lena256_out_1_2d_horizontal;
	fclose(input_file);
	fclose(output_file);
}