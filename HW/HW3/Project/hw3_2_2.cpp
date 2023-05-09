#include "Header.h"

void hw3_2_2() {
	int WIDTH = 800;
	int HEIGHT = 600;

	/*----------------------------------------meerkat_dark----------------------------------------*/
	uchar* meerkat_dark = read_raw("meerkat_dark_800x600.raw", WIDTH, HEIGHT);
	uchar* meerkat_dark_piecewise_linear = piecewise_linear(meerkat_dark, WIDTH, HEIGHT, 0, 0, 127, 255);
	save("16_meerkat_dark_piecewise_linear.png", meerkat_dark_piecewise_linear, WIDTH, HEIGHT);

	/*----------------------------------------meerkat_bright----------------------------------------*/
	uchar* meerkat_bright = read_raw("meerkat_bright_800x600.raw", WIDTH, HEIGHT);
	uchar* meerkat_bright_piecewise_linear = piecewise_linear(meerkat_bright, WIDTH, HEIGHT, 126, 0, 230, 255);
	save("17_meerkat_bright_piecewise_linear.png", meerkat_bright_piecewise_linear, WIDTH, HEIGHT);

	/*----------------------------------------meerkat_high_contrast----------------------------------------*/
	uchar* meerkat_high_contrast = read_raw("meerkat_high_contrast_800x600.raw", WIDTH, HEIGHT);
	uchar* meerkat_high_contrast_piecewise_linear = piecewise_linear(meerkat_high_contrast, WIDTH, HEIGHT, 0, 0, 251, 255);
	save("18_meerkat_high_contrast_piecewise_linear.png", meerkat_high_contrast_piecewise_linear, WIDTH, HEIGHT);
}