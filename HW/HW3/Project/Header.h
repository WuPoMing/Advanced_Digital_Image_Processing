#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void hw3_1();
void hw3_2_1();
void hw3_2_2();
void hw3_3_1();
void hw3_3_2();
void hw3_3_3();

uchar* read_raw(const char* img_name, int width, int height);
void save(const char* img_name, uchar* img, int width, int height);
uchar* nearest_neighbor(uchar* img, int src_width, int src_height, int dst_width, int dst_height);
uchar* binarization(uchar* img, int width, int height);
uchar* get_bit_plane(uchar* img, int width, int height, int plane);
uchar* power_law(uchar* img, int width, int height, double c, double gamma);
uchar* piecewise_linear(uchar* img, int width, int height, int r1, int s1, int r2, int s2);
void find_min_max(uchar* img, int width, int height);
uchar* get_histogram(uchar* img, int width, int height);
uchar* histogram_equalization(uchar* img, int width, int height);
uchar* histogram_matching(uchar* src_img, int src_width, int src_height, uchar* dst_img, int dst_width, int dst_height);