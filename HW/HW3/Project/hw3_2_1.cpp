#include "Header.h"

void hw3_2_1() {
	int WIDTH = 800;
	int HEIGHT = 600;

	/*----------------------------------------meerkat_dark----------------------------------------*/
	uchar* meerkat_dark = read_raw("meerkat_dark_800x600.raw", WIDTH, HEIGHT);

	uchar* meerkat_dark_pow_law_1 = power_law(meerkat_dark, WIDTH, HEIGHT, 1, 0.5);
	uchar* meerkat_dark_pow_law_2 = power_law(meerkat_dark, WIDTH, HEIGHT, 1.6, 0.8);

	save("10_meerkat_dark_pow_law_1.png", meerkat_dark_pow_law_1, WIDTH, HEIGHT);
	save("11_meerkat_dark_pow_law_2.png", meerkat_dark_pow_law_2, WIDTH, HEIGHT);

	/*----------------------------------------meerkat_bright----------------------------------------*/
	uchar* meerkat_bright = read_raw("meerkat_bright_800x600.raw", WIDTH, HEIGHT);

	uchar* meerkat_bright_pow_law_1 = power_law(meerkat_bright, WIDTH, HEIGHT, 1, 2);
	uchar* meerkat_bright_pow_law_2 = power_law(meerkat_bright, WIDTH, HEIGHT, 1, 2.5);

	save("12_meerkat_bright_pow_law_1.png", meerkat_bright_pow_law_1, WIDTH, HEIGHT);
	save("13_meerkat_bright_pow_law_2.png", meerkat_bright_pow_law_2, WIDTH, HEIGHT);

	/*----------------------------------------meerkat_high_contrast----------------------------------------*/
	uchar* meerkat_high_contrast = read_raw("meerkat_high_contrast_800x600.raw", WIDTH, HEIGHT);

	uchar* meerkat_high_contrast_pow_law_1 = power_law(meerkat_high_contrast, WIDTH, HEIGHT, 1, 0.5);
	uchar* meerkat_high_contrast_pow_law_2 = power_law(meerkat_high_contrast, WIDTH, HEIGHT, 1, 0.7);

	save("14_meerkat_high_contrast_pow_law_1.png", meerkat_high_contrast_pow_law_1, WIDTH, HEIGHT);
	save("15_meerkat_high_contrast_pow_law_2.png", meerkat_high_contrast_pow_law_2, WIDTH, HEIGHT);
}