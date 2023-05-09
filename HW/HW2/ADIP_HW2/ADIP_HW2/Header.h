#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <math.h>
#include<time.h>
#include<queue>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void hw2_1();
void hw2_2_1();
void hw2_2_2();
void hw2_2_3();
void hw2_3();
void hw2_4();

unsigned char* read_raw(const char* img_name, int width, int height);
void write_raw(unsigned char* img, const char* img_name, int width, int height);

float get_MSE_from_two_imgs(unsigned char* img_1, unsigned char* img_2, int width, int height);
float get_PSNR_from_two_imgs(unsigned char* img_1, unsigned char* img_2, int width, int height);

unsigned char* nearest_neighbor(unsigned char* img, int src_width, int src_height, int dst_width, int dst_height);
unsigned char* bilinear(unsigned char* img, int src_width, int src_height, int dst_width, int dst_height);
Mat bicubic(cv::Mat img, double rx, double ry);

unsigned char* binarization(unsigned char* img, int width, int height);

Mat draw_D4_search_path(Mat img, int x, int y, int s, int t);
Mat draw_D8_search_path(Mat img, int x, int y, int s, int t);
Mat draw_Dm_search_path(Mat img, int x, int y, int s, int t);
Mat draw_shortest_path(Mat img1, Mat img2, int s, int t);