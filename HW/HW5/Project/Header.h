#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void hw5_1_1and3();
void hw5_1_2and4();
void hw5_1_5();
void hw5_2_1();
void hw5_2_2();
void hw5_3_1();
void hw5_3_2();
void hw5_4();

/*------------------------------------------------------------------------------hw1------------------------------------------------------------------------------*/
uchar* read_raw(const char* img_name, int width, int height);

/*------------------------------------------------------------------------------hw2------------------------------------------------------------------------------*/
double get_MSE_from_two_imgs(uchar* img_1, uchar* img_2, int width, int height);
double get_PSNR_from_two_imgs(uchar* img_1, uchar* img_2, int width, int height);
uchar* nearest_neighbor(uchar* img, int src_width, int src_height, int dst_width, int dst_height);
uchar* binarization(uchar* img, int width, int height);

/*------------------------------------------------------------------------------hw3------------------------------------------------------------------------------*/
uchar* get_bit_plane(uchar* img, int width, int height, int plane);
uchar* power_law(uchar* img, int width, int height, double c, double gamma);
uchar* piecewise_linear(uchar* img, int width, int height, int r1, int s1, int r2, int s2);
uchar* get_histogram(uchar* img, int width, int height);
uchar* histogram_equalization(uchar* img, int width, int height);
uchar* histogram_matching(uchar* src_img, int src_width, int src_height, uchar* dst_img, int dst_width, int dst_height);

/*------------------------------------------------------------------------------hw4------------------------------------------------------------------------------*/
uchar* zero_padding(uchar* img, int width, int height, int pad);
uchar* replication_padding(uchar* img, int width, int height, int pad);
uchar* laplacian_filter(uchar* img, int width, int height, int kernel_type);
uchar* sobel_filter(uchar* img, int width, int height, int kernel_type);
uchar* mean_filter(uchar* img, int width, int height, int kernel_size);
uchar* median_filter(uchar* img, int width, int height, int kernel_size);
uchar* gaussian_filter(uchar* img, int width, int height, double sigma, int kernel_size);
uchar* high_boost_filter(uchar* img, int width, int height, double A, int kernel_type);
uchar* original_plus_laplacian_filter(uchar* img, int width, int height, int kernel_type);
uchar* local_histogram_equalization(uchar* img, int width, int height, int kernel_size);

/*------------------------------------------------------------------------------hw5------------------------------------------------------------------------------*/
complex<double>* DFT(uchar* img, int width, int height);
uchar* get_magnitude_spectrum(complex<double>* fourier_series, int width, int height);
uchar* IDFT(complex<double>* fourier_series, int width, int height);
struct FT_CV{
	Mat magnitude_spectrum;
	Mat out_idft;
};
struct FT_MY {
	uchar* magnitude_spectrum;
	uchar* out_idft;
};
FT_CV DFT_and_IDFT_CV(uchar* img, int width, int height);
uchar* DCT(uchar* img, int width, int height);
FT_MY BLPF(uchar* img, int width, int height, int D0, int n);
FT_MY BHPF(uchar* img, int width, int height, int D0, int n);
FT_MY HFE(uchar* img, int width, int height, int D0, int n, double a, double b);
FT_MY watermark_i(uchar* img, uchar* watermark, int width, int height, double w);
FT_MY watermark_ii(uchar* img, uchar* watermark, int width, int height, double w);
uchar* homomorphic(uchar* img, int width, int height, double rH, double rL, double c, double D0);