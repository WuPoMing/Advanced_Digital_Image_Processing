#include "Header.h"

void hw5_3_1() {
	int WIDTH = 512;
	int HEIGHT = 512;
	double w = 100;
	uchar* raccoon = read_raw("raccoon_512.raw", WIDTH, HEIGHT);
	uchar* mark = read_raw("mark_512.raw", WIDTH, HEIGHT);

	FT_MY raccoon_mark_i = watermark_i(raccoon, mark, WIDTH, HEIGHT, w);
	Mat mat_raccoon_mark_i_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_mark_i.magnitude_spectrum);
	imwrite("47_raccoon_mark_i_raccoon_mark_i_magnitude_spectrum.png", mat_raccoon_mark_i_magnitude_spectrum);
	Mat mat_raccoon_mark_i_out_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_mark_i.out_idft);
	imwrite("48_raccoon_mark_i_raccoon_mark_i_out_idft.png", mat_raccoon_mark_i_out_idft);
}