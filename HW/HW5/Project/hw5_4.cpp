#include "Header.h"

void hw5_4() {
	int WIDTH = 512;
	int HEIGHT = 512;
	uchar* house = read_raw("house512.raw", WIDTH, HEIGHT);

	double rH = 1.3;
	double rL = 0.85;
	double c = 0.35;
	double D0 = 0.4;
	uchar* house_homomorphic = homomorphic(house, WIDTH, HEIGHT, rH, rL, c, D0);
	Mat mat_house_homomorphic(HEIGHT, WIDTH, CV_8UC1, house_homomorphic);
	imwrite("51_house_homomorphic.png", mat_house_homomorphic);

	uchar* house_histogram_equalization = histogram_equalization(house, WIDTH, HEIGHT);
	Mat mat_house_histogram_equalization(HEIGHT, WIDTH, CV_8UC1, house_histogram_equalization);
	imwrite("52_house_histogram_equalization.png", mat_house_histogram_equalization);
}