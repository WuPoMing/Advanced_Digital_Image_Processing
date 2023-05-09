#include "Header.h"

void hw3_3_1() {
	int WIDTH = 800;
	int HEIGHT = 600;

	/*----------------------------------------meerkat_dark----------------------------------------*/
	uchar* meerkat_dark = read_raw("meerkat_dark_800x600.raw", WIDTH, HEIGHT);
	uchar* meerkat_dark_histogram = get_histogram(meerkat_dark, WIDTH, HEIGHT);
	save("19_meerkat_dark_histogram.png", meerkat_dark_histogram, 256, 256);

	/*----------------------------------------meerkat_bright----------------------------------------*/
	uchar* meerkat_bright = read_raw("meerkat_bright_800x600.raw", WIDTH, HEIGHT);
	uchar* meerkat_bright_histogram = get_histogram(meerkat_bright, WIDTH, HEIGHT);
	save("20_meerkat_bright_histogram.png", meerkat_bright_histogram, 256, 256);

	/*----------------------------------------meerkat_high_contrast----------------------------------------*/
	uchar* meerkat_high_contrast = read_raw("meerkat_high_contrast_800x600.raw", WIDTH, HEIGHT);
	uchar* meerkat_high_contrast_histogram = get_histogram(meerkat_high_contrast, WIDTH, HEIGHT);
	save("21_meerkat_high_contrast_histogram.png", meerkat_high_contrast_histogram, 256, 256);
}