#include "Header.h"

void hw5_3_2() {
	int WIDTH = 512;
	int HEIGHT = 512;
	double w = 1;
	uchar* raccoon = read_raw("raccoon_512.raw", WIDTH, HEIGHT);
	uchar* mark = read_raw("mark_512.raw", WIDTH, HEIGHT);

	FT_MY raccoon_mark_ii = watermark_ii(raccoon, mark, WIDTH, HEIGHT, w);
	Mat mat_raccoon_mark_ii_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_mark_ii.magnitude_spectrum);
	imwrite("49_raccoon_mark_ii_raccoon_mark_ii_magnitude_spectrum.png", mat_raccoon_mark_ii_magnitude_spectrum);
	Mat mat_raccoon_mark_ii_out_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_mark_ii.out_idft);
	imwrite("50_raccoon_mark_ii_raccoon_mark_ii_out_idft.png", mat_raccoon_mark_ii_out_idft);
}