#include "Header.h"

void hw5_2_2() {
	int WIDTH = 512;
	int HEIGHT = 512;
	uchar* owl = read_raw("owl_blur_512.raw", WIDTH, HEIGHT);

	FT_MY owl_HFE = HFE(owl, WIDTH, HEIGHT, 50, 2, 0.5, 1);
	uchar* out = histogram_equalization(owl_HFE.out_idft, WIDTH, HEIGHT);
	Mat owl_HFE_idft(HEIGHT, WIDTH, CV_8UC1, out);
	imwrite("46_owl_HFE_idft.png", owl_HFE_idft);
}