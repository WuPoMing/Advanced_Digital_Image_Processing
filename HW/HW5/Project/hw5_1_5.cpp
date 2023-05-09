#include "Header.h"

void hw5_1_5() {
	/*-----------------------------------------------rhombus-----------------------------------------------*/
	printf("============================rhombus============================\n");
	uchar* rhombus = read_raw("rhombus_256.raw", 256, 256);
	uchar* rhombus_DCT = DCT(rhombus, 256, 256);
	Mat mat_rhombus_DCT(256, 256, CV_8UC1, rhombus_DCT);
	imwrite("07_rhombus_magnitude_spectrum_DCT.png", mat_rhombus_DCT);

	/*-----------------------------------------------sine-----------------------------------------------*/
	printf("=============================sine==============================\n");
	uchar* sine = read_raw("sine_128.raw", 128, 128);
	uchar* sine_DCT = DCT(sine, 128, 128);
	Mat mat_sine_DCT(128, 128, CV_8UC1, sine_DCT);
	imwrite("08_sine_magnitude_spectrum_DCT.png", mat_sine_DCT);

	/*-----------------------------------------------lena-----------------------------------------------*/
	printf("=============================lena=============================\n");
	uchar* lena = read_raw("lena_256.raw", 256, 256);
	uchar* lena_DCT = DCT(lena, 256, 256);
	Mat mat_lena_DCT(256, 256, CV_8UC1, lena_DCT);
	imwrite("09_lena_magnitude_spectrum_DCT.png", mat_lena_DCT);
}