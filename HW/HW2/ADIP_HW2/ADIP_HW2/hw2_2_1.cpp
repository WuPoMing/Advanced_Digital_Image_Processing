#include "Header.h"

void hw2_2_1() {
	// initial variable
	int width = 128;
	int height = 128;
	clock_t start, end;

	// load .raw file
	unsigned char* lena128 = read_raw("HW2_images_file/lena128.raw", width, height);
	unsigned char* lena256 = read_raw("HW2_images_file/lena256.raw", 256, 256);
	unsigned char* lena512 = read_raw("HW2_images_file/lena512.raw", 512, 512);

	// process
	start = clock();
	unsigned char* lena128_to_256_nearest_neighbor = nearest_neighbor(lena128, width, height, 256, 256);
	end = clock();
	double diff = end - start;

	start = clock();
	unsigned char* lena128_to_256_bilinear = bilinear(lena128, width, height, 256, 256);
	end = clock();
	double diff1 = end - start;

	start = clock();
	unsigned char* lena128_to_512_nearest_neighbor = nearest_neighbor(lena128, width, height, 512, 512);
	end = clock();
	double diff2 = end - start;

	start = clock();
	unsigned char* lena128_to_512_bilinear = bilinear(lena128, width, height, 512, 512);
	end = clock();
	double diff3 = end - start;

	// get MSE & PSNR
	printf("MSE against lena256.raw and lena128_to_256_nearest_neighbor.raw: %.3f\n", get_MSE_from_two_imgs(lena256, lena128_to_256_nearest_neighbor, 256, 256));
	printf("PSNR against lena256.raw and lena128_to_256_nearest_neighbor.raw: %.3f\n", get_PSNR_from_two_imgs(lena256, lena128_to_256_nearest_neighbor, 256, 256));
	printf("MSE against lena256.raw and lena128_to_256_bilinear.raw: %.3f\n", get_MSE_from_two_imgs(lena256, lena128_to_256_bilinear, 256, 256));
	printf("PSNR against lena256.raw and lena128_to_256_bilinear.raw: %.3f\n", get_PSNR_from_two_imgs(lena256, lena128_to_256_bilinear, 256, 256));
	printf("MSE against lena512.raw and lena128_to_512_nearest_neighbor.raw: %.3f\n", get_MSE_from_two_imgs(lena512, lena128_to_512_nearest_neighbor, 512, 512));
	printf("PSNR against lena512.raw and lena128_to_512_nearest_neighbor.raw: %.3f\n", get_PSNR_from_two_imgs(lena512, lena128_to_512_nearest_neighbor, 512, 512));
	printf("MSE against lena512.raw and lena128_to_512_bilinear.raw: %.3f\n", get_MSE_from_two_imgs(lena512, lena128_to_512_bilinear, 512, 512));
	printf("PSNR against lena512.raw and lena128_to_512_bilinear.raw: %.3f\n", get_PSNR_from_two_imgs(lena512, lena128_to_512_bilinear, 512, 512));

	// transform to CV
	Mat mat_lena128_to_256_nearest_neighbor(256, 256, CV_8UC1, lena128_to_256_nearest_neighbor);
	Mat mat_lena128_to_256_bilinear(256, 256, CV_8UC1, lena128_to_256_bilinear);
	Mat mat_lena128_to_512_nearest_neighbor(512, 512, CV_8UC1, lena128_to_512_nearest_neighbor);
	Mat mat_lena128_to_512_bilinear(512, 512, CV_8UC1, lena128_to_512_bilinear);

	// write file
	imwrite("output_images_file/lena128_to_256_nearest_neighbor.png", mat_lena128_to_256_nearest_neighbor);
	printf("Save lena128_to_256_nearest_neighbor.png successfully...\n");
	printf("Execution time: %.2fms\n", diff);

	imwrite("output_images_file/lena128_to_256_bilinear.png", mat_lena128_to_256_bilinear);
	printf("Save lena128_to_256_bilinear.png successfully...\n");
	printf("Execution time: %.2fms\n", diff1);

	imwrite("output_images_file/lena128_to_512_nearest_neighbor.png", mat_lena128_to_512_nearest_neighbor);
	printf("Save lena128_to_512_nearest_neighbor.png successfully...\n");
	printf("Execution time: %.2fms\n", diff2);

	imwrite("output_images_file/lena128_to_512_bilinear.png", mat_lena128_to_512_bilinear);
	printf("Save lena128_to_512_bilinear.png successfully...\n");
	printf("Execution time: %.2fms\n", diff3);

	// show imamge
	imshow("lena128_to_256_nearest_neighbor.png", mat_lena128_to_256_nearest_neighbor);
	imshow("lena128_to_256_bilinear.png", mat_lena128_to_256_bilinear);
	imshow("lena128_to_512_nearest_neighbor.png", mat_lena128_to_512_nearest_neighbor);
	imshow("lena128_to_512_bilinear.png", mat_lena128_to_512_bilinear);
	waitKey(0);
	destroyAllWindows();
}