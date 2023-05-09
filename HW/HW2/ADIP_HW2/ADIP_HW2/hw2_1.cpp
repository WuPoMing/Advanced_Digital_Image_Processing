#include "Header.h"

void hw2_1() {
	// initial variable
	int width = 256;
	int height = 256;

	// load .raw file
	unsigned char* lena_blur_1 = read_raw("HW2_images_file/lena256_blur_1.raw", width, height);
	unsigned char* lena_blur_2 = read_raw("HW2_images_file/lena256_blur_2.raw", width, height);

	// get MSE & PSNR
	printf("MSE against lena_blur_1.raw and lena_blur_2.raw: %.3f\n", get_MSE_from_two_imgs(lena_blur_1, lena_blur_2, width, height));
	printf("PSNR against lena_blur_1.raw and lena_blur_2.raw: %.3f\n", get_PSNR_from_two_imgs(lena_blur_1, lena_blur_2, width, height));
}