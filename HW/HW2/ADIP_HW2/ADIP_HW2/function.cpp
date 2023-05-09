#include "Header.h"

unsigned char* read_raw(const char* img_name, int width, int height) {
	// initial variable
	FILE* input_file;
	int size = width * height;
	unsigned char* img = new unsigned char[size];

	// read file
	input_file = fopen(img_name, "rb");

	if (input_file == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	fread(img, 1, size, input_file);
	fclose(input_file);
	return img;
}

void write_raw(unsigned char *img, const char* img_name, int width, int height) {
	// initial variable
	FILE* output_file;
	int size = width * height;

	// save file
	output_file = fopen(img_name, "wb");
	fwrite(img, 1, size, output_file);
	fclose(output_file);
}

float get_MSE_from_two_imgs(unsigned char *img_1, unsigned char *img_2, int width, int height) {
	double error = 0;
	int size = width * height;

	for (int i = 0; i < size; i++) {
		error += pow(*(img_2 + i) - *(img_1 + i), 2);
	}
	return error / size;
}

float get_PSNR_from_two_imgs(unsigned char *img_1, unsigned char *img_2, int width, int height) {
	int MAX = 255;
	return 10 * log10(pow(MAX, 2) / get_MSE_from_two_imgs(img_1, img_2, width, height));
}

unsigned char* nearest_neighbor(unsigned char* img, int src_width, int src_height, int dst_width, int dst_height) {
	unsigned char* new_img = new unsigned char[dst_width * dst_height];

	for (int row = 0; row < dst_height; row++) {
		for (int col = 0; col < dst_width; col++) {
			int srcX = round(col * ((src_width - 1.0) / (dst_width - 1.0)));
			int srcY = round(row * ((src_height - 1.0) / (dst_height - 1.0)));
			*(new_img + row * dst_width + col) = *(img + src_width * srcY + srcX);
		}
	}
	return new_img;
}

unsigned char* bilinear(unsigned char* img, int src_width, int src_height, int dst_width, int dst_height) {
	unsigned char* new_img = new unsigned char[dst_width * dst_height];

	for (int row = 0; row < dst_height; row++) {
		for (int col = 0; col < dst_width; col++) {

			double x = col * ((src_width - 1.0) / (dst_width - 1.0));
			double y = row * ((src_height - 1.0) / (dst_height - 1.0));

			int x1 = floor(x);
			int x2 = ceil(x); 
			int y1 = floor(y);
			int y2 = ceil(y);

			int A = *(img + src_width * y1 + x1);	// P(x1, y1)
			int B = *(img + src_width * y1 + x2);	// P(x2, y1)
			int C = *(img + src_width * y2 + x1);	// P(x1, y2)
			int D = *(img + src_width * y2 + x2);	// P(x2, y2)

			float dx1 = x - x1;
			float dx2 = 1 - dx1;
			float dy1 = y - y1;
			float dy2 = 1 - dy1;

			float AB = A * dx2 + B * dx1;
			float CD = C * dx2 + D * dx1;
			float Pxy = AB * dy2 + CD * dy1;

			*(new_img + row * dst_width + col) = Pxy;
		}
	}
	return new_img;
}

unsigned char* binarization(unsigned char* img, int width, int height) {
	unsigned char* new_img = new unsigned char[width * height];

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (*(img + row * width + col) <= 127) {
				*(new_img + row * width + col) = 0;
			}
			else {
				*(new_img + row * width + col) = 255;
			}
		}
	}
	return new_img;
}