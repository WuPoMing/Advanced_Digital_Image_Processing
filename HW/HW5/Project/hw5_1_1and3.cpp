#include "Header.h"

void hw5_1_1and3() {
	TickMeter time;

	/*-----------------------------------------------rhombus-----------------------------------------------*/
	printf("============================rhombus============================\n");
	uchar* rhombus = read_raw("rhombus_256.raw", 256, 256);
	time.start();
	complex<double>* rhombus_fourier_series = DFT(rhombus, 256, 256);
	time.stop();
	cout << "DFT execution time: " << time << endl;
	uchar* rhombus_magnitude_spectrum = get_magnitude_spectrum(rhombus_fourier_series, 256, 256);
	Mat mat_rhombus_magnitude_spectrum(256, 256, CV_8UC1, rhombus_magnitude_spectrum);
	imwrite("01_rhombus_magnitude_spectrum_DFT_C.png", mat_rhombus_magnitude_spectrum);

	time.reset(); time.start();
	uchar* rhombus_idft = IDFT(rhombus_fourier_series, 256, 256);
	time.stop();
	cout << "IDFT execution time: " << time << endl;
	Mat mat_rhombus_idft(256, 256, CV_8UC1, rhombus_idft);
	imwrite("04_rhombus_IDFT_C.png", mat_rhombus_idft);

	double rhombus_mse = get_MSE_from_two_imgs(rhombus, rhombus_idft, 256, 256);
	printf("MSE: %.3f\n", rhombus_mse);

	/*-----------------------------------------------sine-----------------------------------------------*/
	printf("=============================sine==============================\n");
	uchar* sine = read_raw("sine_128.raw", 128, 128);
	time.reset(); time.start();
	complex<double>* sine_fourier_series = DFT(sine, 128, 128);
	time.stop();
	cout << "DFT execution time: " << time << endl;
	uchar* sine_magnitude_spectrum = get_magnitude_spectrum(sine_fourier_series, 128, 128);
	Mat mat_sine_magnitude_spectrum(128, 128, CV_8UC1, sine_magnitude_spectrum);
	imwrite("02_sine_magnitude_spectrum_DFT_C.png", mat_sine_magnitude_spectrum);

	time.reset(); time.start();
	uchar* sine_idft = IDFT(sine_fourier_series, 128, 128);
	time.stop();
	cout << "IDFT execution time: " << time << endl;
	Mat mat_sine_idft(128, 128, CV_8UC1, sine_idft);
	imwrite("05_sine_IDFT_C.png", mat_sine_idft);

	double sine_mse = get_MSE_from_two_imgs(sine, sine_idft, 128, 128);
	printf("MSE: %.3f\n", sine_mse);

	/*-----------------------------------------------lena-----------------------------------------------*/
	printf("=============================lena=============================\n");
	uchar* lena = read_raw("lena_256.raw", 256, 256);
	time.reset(); time.start();
	complex<double>* lena_fourier_series = DFT(lena, 256, 256);
	time.stop();
	cout << "DFT execution time: " << time << endl;
	uchar* lena_magnitude_spectrum = get_magnitude_spectrum(lena_fourier_series, 256, 256);
	Mat mat_lena_magnitude_spectrum(256, 256, CV_8UC1, lena_magnitude_spectrum);
	imwrite("03_lena_magnitude_spectrum_DFT_C.png", mat_lena_magnitude_spectrum);

	time.reset(); time.start();
	uchar* lena_idft = IDFT(lena_fourier_series, 256, 256);
	time.stop();
	cout << "IDFT execution time: " << time << endl;
	Mat mat_lena_idft(256, 256, CV_8UC1, lena_idft);
	imwrite("06_lena_IDFT_C.png", mat_lena_idft);

	double lena_mse = get_MSE_from_two_imgs(lena, lena_idft, 256, 256);
	printf("MSE: %.3f\n", lena_mse);
}