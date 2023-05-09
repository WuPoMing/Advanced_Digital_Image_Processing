#include "Header.h"

void hw5_1_2and4() {
	/*-----------------------------------------------rhombus-----------------------------------------------*/
	printf("============================rhombus============================\n");
	uchar* rhombus = read_raw("rhombus_256.raw", 256, 256);
	FT_CV rhombus_FT = DFT_and_IDFT_CV(rhombus, 256, 256);
	imwrite("rhombus_magnitude_spectrum_DFT_CV.png", rhombus_FT.magnitude_spectrum);
	imwrite("rhombus_IDFT_CV.png", rhombus_FT.out_idft);

	/*-----------------------------------------------sine-----------------------------------------------*/
	printf("=============================sine==============================\n");
	uchar* sine = read_raw("sine_128.raw", 128, 128);
	FT_CV sine_FT = DFT_and_IDFT_CV(sine, 128, 128);
	imwrite("sine_magnitude_spectrum_DFT_CV.png", sine_FT.magnitude_spectrum);
	imwrite("sine_IDFT_CV.png", sine_FT.out_idft);

	/*-----------------------------------------------lena-----------------------------------------------*/
	printf("=============================lena=============================\n");
	uchar* lena = read_raw("lena_256.raw", 256, 256);
	FT_CV lena_FT = DFT_and_IDFT_CV(lena, 256, 256);
	imwrite("lena_magnitude_spectrum_DFT_CV.png", lena_FT.magnitude_spectrum);
	imwrite("lena_IDFT_CV.png", lena_FT.out_idft);
}