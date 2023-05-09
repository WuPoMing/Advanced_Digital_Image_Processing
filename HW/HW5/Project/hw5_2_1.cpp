#include "Header.h"

void hw5_2_1() {
	int WIDTH = 512;
	int HEIGHT = 512;
	uchar* raccoon = read_raw("raccoon_512.raw", WIDTH, HEIGHT);

	/*----------------------------------------------Butterworth LPF----------------------------------------------*/
	FT_MY raccoon_BLPF_5_1 = BLPF(raccoon, WIDTH, HEIGHT, 5, 1);
	Mat raccoon_BLPF_5_1_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_5_1.magnitude_spectrum);
	imwrite("10_raccoon_BLPF_5_1_magnitude_spectrum.png", raccoon_BLPF_5_1_magnitude_spectrum);
	Mat raccoon_BLPF_5_1_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_5_1.out_idft);
	imwrite("11_raccoon_BLPF_5_1_idft.png", raccoon_BLPF_5_1_idft);

	FT_MY raccoon_BLPF_5_2 = BLPF(raccoon, WIDTH, HEIGHT, 5, 2);
	Mat raccoon_BLPF_5_2_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_5_2.magnitude_spectrum);
	imwrite("12_raccoon_BLPF_5_2_magnitude_spectrum.png", raccoon_BLPF_5_2_magnitude_spectrum);
	Mat raccoon_BLPF_5_2_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_5_2.out_idft);
	imwrite("13_raccoon_BLPF_5_2_idft.png", raccoon_BLPF_5_2_idft);

	FT_MY raccoon_BLPF_5_3 = BLPF(raccoon, WIDTH, HEIGHT, 5, 3);
	Mat raccoon_BLPF_5_3_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_5_3.magnitude_spectrum);
	imwrite("14_raccoon_BLPF_5_3_magnitude_spectrum.png", raccoon_BLPF_5_3_magnitude_spectrum);
	Mat raccoon_BLPF_5_3_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_5_3.out_idft);
	imwrite("15_raccoon_BLPF_5_3_idft.png", raccoon_BLPF_5_3_idft);

	FT_MY raccoon_BLPF_20_1 = BLPF(raccoon, WIDTH, HEIGHT, 20, 1);
	Mat raccoon_BLPF_20_1_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_20_1.magnitude_spectrum);
	imwrite("16_raccoon_BLPF_20_1_magnitude_spectrum.png", raccoon_BLPF_20_1_magnitude_spectrum);
	Mat raccoon_BLPF_20_1_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_20_1.out_idft);
	imwrite("17_raccoon_BLPF_20_1_idft.png", raccoon_BLPF_20_1_idft);

	FT_MY raccoon_BLPF_20_2 = BLPF(raccoon, WIDTH, HEIGHT, 20, 2);
	Mat raccoon_BLPF_20_2_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_20_2.magnitude_spectrum);
	imwrite("18_raccoon_BLPF_20_2_magnitude_spectrum.png", raccoon_BLPF_20_2_magnitude_spectrum);
	Mat raccoon_BLPF_20_2_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_20_2.out_idft);
	imwrite("19_raccoon_BLPF_20_2_idft.png", raccoon_BLPF_20_2_idft);

	FT_MY raccoon_BLPF_20_3 = BLPF(raccoon, WIDTH, HEIGHT, 20, 3);
	Mat raccoon_BLPF_20_3_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_20_3.magnitude_spectrum);
	imwrite("20_raccoon_BLPF_20_3_magnitude_spectrum.png", raccoon_BLPF_20_3_magnitude_spectrum);
	Mat raccoon_BLPF_20_3_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_20_3.out_idft);
	imwrite("21_raccoon_BLPF_20_3_idft.png", raccoon_BLPF_20_3_idft);

	FT_MY raccoon_BLPF_50_1 = BLPF(raccoon, WIDTH, HEIGHT, 50, 1);
	Mat raccoon_BLPF_50_1_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_50_1.magnitude_spectrum);
	imwrite("22_raccoon_BLPF_50_1_magnitude_spectrum.png", raccoon_BLPF_50_1_magnitude_spectrum);
	Mat raccoon_BLPF_50_1_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_50_1.out_idft);
	imwrite("23_raccoon_BLPF_50_1_idft.png", raccoon_BLPF_50_1_idft);

	FT_MY raccoon_BLPF_50_2 = BLPF(raccoon, WIDTH, HEIGHT, 50, 2);
	Mat raccoon_BLPF_50_2_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_50_2.magnitude_spectrum);
	imwrite("24_raccoon_BLPF_50_2_magnitude_spectrum.png", raccoon_BLPF_50_2_magnitude_spectrum);
	Mat raccoon_BLPF_50_2_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_50_2.out_idft);
	imwrite("25_raccoon_BLPF_50_2_idft.png", raccoon_BLPF_50_2_idft);

	FT_MY raccoon_BLPF_50_3 = BLPF(raccoon, WIDTH, HEIGHT, 50, 3);
	Mat raccoon_BLPF_50_3_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_50_3.magnitude_spectrum);
	imwrite("26_raccoon_BLPF_50_3_magnitude_spectrum.png", raccoon_BLPF_50_3_magnitude_spectrum);
	Mat raccoon_BLPF_50_3_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BLPF_50_3.out_idft);
	imwrite("27_raccoon_BLPF_50_3_idft.png", raccoon_BLPF_50_3_idft);

	/*----------------------------------------------Butterworth HPF----------------------------------------------*/
	FT_MY raccoon_BHPF_5_1 = BHPF(raccoon, WIDTH, HEIGHT, 5, 1);
	Mat raccoon_BHPF_5_1_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_5_1.magnitude_spectrum);
	imwrite("28_raccoon_BHPF_5_1_magnitude_spectrum.png", raccoon_BHPF_5_1_magnitude_spectrum);
	Mat raccoon_BHPF_5_1_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_5_1.out_idft);
	imwrite("29_raccoon_BHPF_5_1_idft.png", raccoon_BHPF_5_1_idft);

	FT_MY raccoon_BHPF_5_2 = BHPF(raccoon, WIDTH, HEIGHT, 5, 2);
	Mat raccoon_BHPF_5_2_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_5_2.magnitude_spectrum);
	imwrite("30_raccoon_BHPF_5_2_magnitude_spectrum.png", raccoon_BHPF_5_2_magnitude_spectrum);
	Mat raccoon_BHPF_5_2_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_5_2.out_idft);
	imwrite("31_raccoon_BHPF_5_2_idft.png", raccoon_BHPF_5_2_idft);

	FT_MY raccoon_BHPF_5_3 = BHPF(raccoon, WIDTH, HEIGHT, 5, 3);
	Mat raccoon_BHPF_5_3_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_5_3.magnitude_spectrum);
	imwrite("32_raccoon_BHPF_5_3_magnitude_spectrum.png", raccoon_BHPF_5_3_magnitude_spectrum);
	Mat raccoon_BHPF_5_3_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_5_3.out_idft);
	imwrite("33_raccoon_BHPF_5_3_idft.png", raccoon_BHPF_5_3_idft);

	FT_MY raccoon_BHPF_20_1 = BHPF(raccoon, WIDTH, HEIGHT, 20, 1);
	Mat raccoon_BHPF_20_1_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_20_1.magnitude_spectrum);
	imwrite("34_raccoon_BHPF_20_1_magnitude_spectrum.png", raccoon_BHPF_20_1_magnitude_spectrum);
	Mat raccoon_BHPF_20_1_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_20_1.out_idft);
	imwrite("35_raccoon_BHPF_20_1_idft.png", raccoon_BHPF_20_1_idft);

	FT_MY raccoon_BHPF_20_2 = BHPF(raccoon, WIDTH, HEIGHT, 20, 2);
	Mat raccoon_BHPF_20_2_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_20_2.magnitude_spectrum);
	imwrite("36_raccoon_BHPF_20_2_magnitude_spectrum.png", raccoon_BHPF_20_2_magnitude_spectrum);
	Mat raccoon_BHPF_20_2_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_20_2.out_idft);
	imwrite("37_raccoon_BHPF_20_2_idft.png", raccoon_BHPF_20_2_idft);

	FT_MY raccoon_BHPF_20_3 = BHPF(raccoon, WIDTH, HEIGHT, 20, 3);
	Mat raccoon_BHPF_20_3_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_20_3.magnitude_spectrum);
	imwrite("38_raccoon_BHPF_20_3_magnitude_spectrum.png", raccoon_BHPF_20_3_magnitude_spectrum);
	Mat raccoon_BHPF_20_3_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_20_3.out_idft);
	imwrite("39_raccoon_BHPF_20_3_idft.png", raccoon_BHPF_20_3_idft);

	FT_MY raccoon_BHPF_50_1 = BHPF(raccoon, WIDTH, HEIGHT, 50, 1);
	Mat raccoon_BHPF_50_1_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_50_1.magnitude_spectrum);
	imwrite("40_raccoon_BHPF_50_1_magnitude_spectrum.png", raccoon_BHPF_50_1_magnitude_spectrum);
	Mat raccoon_BHPF_50_1_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_50_1.out_idft);
	imwrite("41_raccoon_BHPF_50_1_idft.png", raccoon_BHPF_50_1_idft);

	FT_MY raccoon_BHPF_50_2 = BHPF(raccoon, WIDTH, HEIGHT, 50, 2);
	Mat raccoon_BHPF_50_2_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_50_2.magnitude_spectrum);
	imwrite("42_raccoon_BHPF_50_2_magnitude_spectrum.png", raccoon_BHPF_50_2_magnitude_spectrum);
	Mat raccoon_BHPF_50_2_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_50_2.out_idft);
	imwrite("43_raccoon_BHPF_50_2_idft.png", raccoon_BHPF_50_2_idft);

	FT_MY raccoon_BHPF_50_3 = BHPF(raccoon, WIDTH, HEIGHT, 50, 3);
	Mat raccoon_BHPF_50_3_magnitude_spectrum(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_50_3.magnitude_spectrum);
	imwrite("44_raccoon_BHPF_50_3_magnitude_spectrum.png", raccoon_BHPF_50_3_magnitude_spectrum);
	Mat raccoon_BHPF_50_3_idft(HEIGHT, WIDTH, CV_8UC1, raccoon_BHPF_50_3.out_idft);
	imwrite("45_raccoon_BHPF_50_3_idft.png", raccoon_BHPF_50_3_idft);
}