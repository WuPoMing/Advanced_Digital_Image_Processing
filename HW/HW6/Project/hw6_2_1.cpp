#include "Header.h"

void hw6_2_1() {
	int WIDTH = 613;
	int HEIGHT = 237;
	uchar* check = read_raw("check_613x237.raw", WIDTH, HEIGHT);

	uchar* check_erode_SE_5x5 = erode_SE_5x5(check, WIDTH, HEIGHT);
	Mat mat_check_erode_SE_5x5(HEIGHT, WIDTH, CV_8UC1, check_erode_SE_5x5);
	imwrite("02_check_erode_SE_5x5.png", mat_check_erode_SE_5x5);

	uchar* check_dilate_SE_5x5 = dilate_SE_5x5(check, WIDTH, HEIGHT);
	Mat mat_check_dilate_SE_5x5(HEIGHT, WIDTH, CV_8UC1, check_dilate_SE_5x5);
	imwrite("03_check_dilate_SE_5x5.png", mat_check_dilate_SE_5x5);

	uchar* check_open_SE_5x5 = open_SE_5x5(check, WIDTH, HEIGHT);
	Mat mat_check_open_SE_5x5(HEIGHT, WIDTH, CV_8UC1, check_open_SE_5x5);
	imwrite("04_check_open_SE_5x5.png", mat_check_open_SE_5x5);

	uchar* check_close_SE_5x5 = close_SE_5x5(check, WIDTH, HEIGHT);
	Mat mat_check_close_SE_5x5(HEIGHT, WIDTH, CV_8UC1, check_close_SE_5x5);
	imwrite("05_check_close_SE_5x5.png", mat_check_close_SE_5x5);
} 