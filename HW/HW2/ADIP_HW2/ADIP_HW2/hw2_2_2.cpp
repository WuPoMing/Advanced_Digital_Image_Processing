#include "Header.h"

void hw2_2_2() {
	// initial variable
	int width = 512;
	int height = 512;
	clock_t start, end;

	// load .raw file
	unsigned char* lena512 = read_raw("HW2_images_file/lena512.raw", width, height);
	unsigned char* lena512_blur = read_raw("HW2_images_file/lena512_blur.raw", width, height);
	unsigned char* lena256 = read_raw("HW2_images_file/lena256.raw", 256, 256);
	unsigned char* lena128 = read_raw("HW2_images_file/lena128.raw", 128, 128);
	
	// process
	start = clock();
	unsigned char* lena512_to_256_nearest_neighbor = nearest_neighbor(lena512, width, height, 256, 256); end = clock();
	end = clock();
	double diff = end - start;

	start = clock();
	unsigned char* lena512_to_256_bilinear = bilinear(lena512, width, height, 256, 256);
	end = clock();
	double diff1 = end - start;

	start = clock();
	unsigned char* lena512_to_128_nearest_neighbor = nearest_neighbor(lena512, width, height, 128, 128);
	end = clock();
	double diff2 = end - start;

	start = clock();
	unsigned char* lena512_to_128_bilinear = bilinear(lena512, width, height, 128, 128);
	end = clock();
	double diff3 = end - start;

	start = clock();
	unsigned char* lena512_blur_to_256_nearest_neighbor = nearest_neighbor(lena512_blur, width, height, 256, 256);
	end = clock();
	double diff4 = end - start;

	start = clock();
	unsigned char* lena512_blur_to_256_bilinear = bilinear(lena512_blur, width, height, 256, 256);
	end = clock();
	double diff5 = end - start;

	start = clock();
	unsigned char* lena512_blur_to_128_nearest_neighbor = nearest_neighbor(lena512_blur, width, height, 128, 128);
	end = clock();
	double diff6 = end - start;

	start = clock();
	unsigned char* lena512_blur_to_128_bilinear = bilinear(lena512_blur, width, height, 128, 128);
	end = clock();
	double diff7 = end - start;

	// get MSE & PSNR
	printf("MSE against lena256 and lena512_to_256_nearest_neighbor: %.3f\n", get_MSE_from_two_imgs(lena256, lena512_to_256_nearest_neighbor, 256, 256));
	printf("PSNR against lena256 and lena512_to_256_nearest_neighbor: %.3f\n", get_PSNR_from_two_imgs(lena256, lena512_to_256_nearest_neighbor, 256, 256));
	printf("MSE against lena256 and lena512_to_256_bilinear: %.3f\n", get_MSE_from_two_imgs(lena256, lena512_to_256_bilinear, 256, 256));
	printf("PSNR against lena256 and lena512_to_256_bilinear: %.3f\n", get_PSNR_from_two_imgs(lena256, lena512_to_256_bilinear, 256, 256));
	printf("MSE against lena128 and lena512_to_128_nearest_neighbor: %.3f\n", get_MSE_from_two_imgs(lena128, lena512_to_128_nearest_neighbor, 128, 128));
	printf("PSNR against lena128 and lena512_to_128_nearest_neighbor: %.3f\n", get_PSNR_from_two_imgs(lena128, lena512_to_128_nearest_neighbor, 128, 128));
	printf("MSE against lena128 and lena512_to_128_bilinear: %.3f\n", get_MSE_from_two_imgs(lena128, lena512_to_128_bilinear, 128, 128));
	printf("PSNR against lena128 and lena512_to_128_bilinear: %.3f\n", get_PSNR_from_two_imgs(lena128, lena512_to_128_bilinear, 128, 128));
	
	printf("MSE against lena256 and lena512_blur_to_256_nearest_neighbor: %.3f\n", get_MSE_from_two_imgs(lena256, lena512_blur_to_256_nearest_neighbor, 256, 256));
	printf("PSNR against lena256 and lena512_blur_to_256_nearest_neighbor: %.3f\n", get_PSNR_from_two_imgs(lena256, lena512_blur_to_256_nearest_neighbor, 256, 256));
	printf("MSE against lena256 and lena512_blur_to_256_bilinear: %.3f\n", get_MSE_from_two_imgs(lena256, lena512_blur_to_256_bilinear, 256, 256));
	printf("PSNR against lena256 and lena512_blur_to_256_bilinear: %.3f\n", get_PSNR_from_two_imgs(lena256, lena512_blur_to_256_bilinear, 256, 256));
	printf("MSE against lena128 and lena512_blur_to_128_nearest_neighbor: %.3f\n", get_MSE_from_two_imgs(lena128, lena512_blur_to_128_nearest_neighbor, 128, 128));
	printf("PSNR against lena128 and lena512_blur_to_128_nearest_neighbor: %.3f\n", get_PSNR_from_two_imgs(lena128, lena512_blur_to_128_nearest_neighbor, 128, 128));
	printf("MSE against lena128 and lena512_blur_to_128_bilinear: %.3f\n", get_MSE_from_two_imgs(lena128, lena512_blur_to_128_bilinear, 128, 128));
	printf("PSNR against lena128 and lena512_blur_to_128_bilinear: %.3f\n", get_PSNR_from_two_imgs(lena128, lena512_blur_to_128_bilinear, 128, 128));

	// transform to CV
	Mat mat_lena512_to_256_nearest_neighbor(256, 256, CV_8UC1, lena512_to_256_nearest_neighbor);
	Mat mat_lena512_to_256_bilinear(256, 256, CV_8UC1, lena512_to_256_bilinear);
	Mat mat_lena512_to_128_nearest_neighbor(128, 128, CV_8UC1, lena512_to_128_nearest_neighbor);
	Mat mat_lena512_to_128_bilinear(128, 128, CV_8UC1, lena512_to_128_bilinear);
	Mat mat_lena512_blur_to_256_nearest_neighbor(256, 256, CV_8UC1, lena512_blur_to_256_nearest_neighbor);
	Mat mat_lena512_blur_to_256_bilinear(256, 256, CV_8UC1, lena512_blur_to_256_bilinear);
	Mat mat_lena512_blur_to_128_nearest_neighbor(128, 128, CV_8UC1, lena512_blur_to_128_nearest_neighbor);
	Mat mat_lena512_blur_to_128_bilinear(128, 128, CV_8UC1, lena512_blur_to_128_bilinear);

	// write file
	imwrite("output_images_file/lena512_to_256_nearest_neighbor.png", mat_lena512_to_256_nearest_neighbor);
	printf("Save lena512_to_256_nearest_neighbor.png successfully...\n");
	printf("Execution time: %.2fms\n", diff);

	imwrite("output_images_file/lena512_to_256_bilinear.png", mat_lena512_to_256_bilinear);
	printf("Save lena512_to_256_bilinear.png successfully...\n");
	printf("Execution time: %.2fms\n", diff1);

	imwrite("output_images_file/lena512_to_128_nearest_neighbor.png", mat_lena512_to_128_nearest_neighbor);
	printf("Save lena512_to_128_nearest_neighbor.png successfully...\n");
	printf("Execution time: %.2fms\n", diff2);

	imwrite("output_images_file/lena512_to_128_bilinear.png", mat_lena512_to_128_bilinear);
	printf("Save lena512_to_128_bilinear.png successfully...\n");
	printf("Execution time: %.2fms\n", diff3);

	imwrite("output_images_file/lena512_blur_to_256_nearest_neighbor.png", mat_lena512_blur_to_256_nearest_neighbor);
	printf("Save lena512_blur_to_256_nearest_neighbor.png successfully...\n");
	printf("Execution time: %.2fms\n", diff4);

	imwrite("output_images_file/lena512_blur_to_256_bilinear.png", mat_lena512_blur_to_256_bilinear);
	printf("Save lena512_blur_to_256_bilinear.png successfully...\n");
	printf("Execution time: %.2fms\n", diff5);

	imwrite("output_images_file/lena512_blur_to_128_nearest_neighbor.png", mat_lena512_blur_to_128_nearest_neighbor);
	printf("Save lena512_blur_to_128_nearest_neighbor.png successfully...\n");
	printf("Execution time: %.2fms\n", diff6);

	imwrite("output_images_file/lena512_blur_to_128_bilinear.png", mat_lena512_blur_to_128_bilinear);
	printf("Save lena512_blur_to_128_bilinear.png successfully...\n");
	printf("Execution time: %.2fms\n", diff7);

	// show image
	imshow("lena512_to_256_nearest_neighbor.png", mat_lena512_to_256_nearest_neighbor);
	imshow("lena512_to_256_bilinear.png", mat_lena512_to_256_bilinear);
	imshow("lena512_to_128_nearest_neighbor.png", mat_lena512_to_128_nearest_neighbor);
	imshow("lena512_to_128_bilinear.png", mat_lena512_to_128_bilinear);
	imshow("lena512_blur_to_256_nearest_neighbor.png", mat_lena512_blur_to_256_nearest_neighbor);
	imshow("lena512_blur_to_256_bilinear.png", mat_lena512_blur_to_256_bilinear);
	imshow("lena512_blur_to_128_nearest_neighbor.png", mat_lena512_blur_to_128_nearest_neighbor);
	imshow("lena512_blur_to_128_bilinear.png", mat_lena512_blur_to_128_bilinear);
	waitKey(0);
	destroyAllWindows();
}