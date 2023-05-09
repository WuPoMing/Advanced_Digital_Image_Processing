#include "Header.h"

void hw2_3() {
	// initial variable
	int width = 256;
	int height = 256;

	// load .raw file
	unsigned char* lena256 = read_raw("HW2_images_file/lena256.raw", width, height);
	unsigned char* baboon256 = read_raw("HW2_images_file/baboon256.raw", width, height);

	// process
	unsigned char* lena256_binarization = binarization(lena256, width, height);
	unsigned char* baboon256_binarization = binarization(baboon256, width, height);

	// get MSE & PSNR
	printf("MSE against lena256 and lena256_binarization: %.3f\n", get_MSE_from_two_imgs(lena256, lena256_binarization, width, height));
	printf("PSNR against lena256 and lena256_binarization: %.3f\n", get_PSNR_from_two_imgs(lena256, lena256_binarization, width, height));
	printf("MSE against baboon256 and baboon256_binarization: %.3f\n", get_MSE_from_two_imgs(baboon256, baboon256_binarization, width, height));
	printf("PSNR against baboon256 and baboon256_binarization: %.3f\n", get_PSNR_from_two_imgs(baboon256, baboon256_binarization, width, height));

	// transform to CV
	Mat mat_lena256_binarization(height, width, CV_8UC1, lena256_binarization);
	Mat mat_baboon256_binarization(height, width, CV_8UC1, baboon256_binarization);

	// write file
	imwrite("output_images_file/lena256_binarization.png", mat_lena256_binarization);
	printf("Save lena256_binarization.png successfully...\n");

	imwrite("output_images_file/baboon256_binarization.png", mat_baboon256_binarization);
	printf("Save baboon256_binarization.png successfully...\n");

	// show image
	imshow("lena256_binarization", mat_lena256_binarization);
	imshow("baboon256_binarization", mat_baboon256_binarization);
	waitKey(0);
	destroyAllWindows();
}