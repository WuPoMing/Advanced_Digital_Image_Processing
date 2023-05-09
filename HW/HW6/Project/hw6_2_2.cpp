#include "Header.h"

void hw6_2_2() {
	int WIDTH = 613;
	int HEIGHT = 237;
	uchar* check = read_raw("check_613x237.raw", WIDTH, HEIGHT);

	uchar* check_erode_SE_5x5_90 = erode_SE_5x5_90(check, WIDTH, HEIGHT);
	Mat mat_check_erode_SE_5x5_90(HEIGHT, WIDTH, CV_8UC1, check_erode_SE_5x5_90);
	imwrite("06_check_erode_SE_5x5_90.png", mat_check_erode_SE_5x5_90);

	uchar* check_dilate_SE_5x5_90 = dilate_SE_5x5_90(check, WIDTH, HEIGHT);
	Mat mat_check_dilate_SE_5x5_90(HEIGHT, WIDTH, CV_8UC1, check_dilate_SE_5x5_90);
	imwrite("07_check_dilate_SE_5x5_90.png", mat_check_dilate_SE_5x5_90);
}