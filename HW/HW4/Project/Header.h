#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void hw4_1_1();
void hw4_1_2();
void hw4_2_1();
void hw4_2_2();
void hw4_2_3();
void hw4_3();

uchar* read_raw(const char* img_name, int width, int height);
uchar* nearest_neighbor(uchar* img, int src_width, int src_height, int dst_width, int dst_height);
uchar* binarization(uchar* img, int width, int height);
uchar* get_bit_plane(uchar* img, int width, int height, int plane);
uchar* power_law(uchar* img, int width, int height, double c, double gamma);
uchar* piecewise_linear(uchar* img, int width, int height, int r1, int s1, int r2, int s2);
uchar* get_histogram(uchar* img, int width, int height);
uchar* histogram_equalization(uchar* img, int width, int height);
uchar* histogram_matching(uchar* src_img, int src_width, int src_height, uchar* dst_img, int dst_width, int dst_height);

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