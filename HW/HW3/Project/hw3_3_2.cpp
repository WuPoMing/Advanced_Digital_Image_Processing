#include "Header.h"

void hw3_3_2() {
	int WIDTH = 800;
	int HEIGHT = 600;

	/*----------------------------------------meerkat_dark----------------------------------------*/
	uchar* meerkat_dark = read_raw("meerkat_dark_800x600.raw", WIDTH, HEIGHT);

	uchar* meerkat_dark_histogram_equalization = histogram_equalization(meerkat_dark, WIDTH, HEIGHT);
	uchar* meerkat_dark_histogram_equalization_histogram = get_histogram(meerkat_dark_histogram_equalization, WIDTH, HEIGHT);
	save("22_meerkat_dark_histogram_equalization.png", meerkat_dark_histogram_equalization, WIDTH, HEIGHT);
	save("23_meerkat_dark_histogram_equalization_histogram.png", meerkat_dark_histogram_equalization_histogram, 256, 256);

	/*----------------------------------------meerkat_bright----------------------------------------*/
	uchar* meerkat_bright = read_raw("meerkat_bright_800x600.raw", WIDTH, HEIGHT);

	uchar* meerkat_bright_histogram_equalization = histogram_equalization(meerkat_bright, WIDTH, HEIGHT);
	uchar* meerkat_bright_histogram_equalization_histogram = get_histogram(meerkat_bright_histogram_equalization, WIDTH, HEIGHT);
	save("24_meerkat_bright_histogram_equalization.png", meerkat_bright_histogram_equalization, WIDTH, HEIGHT);
	save("25_meerkat_bright_histogram_equalization_histogram.png", meerkat_bright_histogram_equalization_histogram, 256, 256);

	/*----------------------------------------meerkat_high_contrast----------------------------------------*/
	uchar* meerkat_high_contrast = read_raw("meerkat_high_contrast_800x600.raw", WIDTH, HEIGHT);

	uchar* meerkat_high_contrast_histogram_equalization = histogram_equalization(meerkat_high_contrast, WIDTH, HEIGHT);
	uchar* meerkat_high_contrast_histogram_equalization_histogram = get_histogram(meerkat_high_contrast_histogram_equalization, WIDTH, HEIGHT);
	save("26_meerkat_high_contrast_histogram_equalization.png", meerkat_high_contrast_histogram_equalization, WIDTH, HEIGHT);
	save("27_meerkat_high_contrast_histogram_equalization_histogram.png", meerkat_high_contrast_histogram_equalization_histogram, 256, 256);
}