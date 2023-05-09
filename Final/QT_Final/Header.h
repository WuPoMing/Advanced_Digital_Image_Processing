#define _CRT_SECURE_NO_DEPRECATE
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/img_hash.hpp"

//CUDA structures and methods
#include <opencv2/core/cuda.hpp>
#include <opencv2/gapi/ocl/core.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudaimgproc.hpp>

using namespace std;
using namespace cv;
using namespace cv::img_hash;

struct BufferMSSIM                                     // Optimized CUDA versions
{   // Data allocations are very expensive on CUDA. Use a buffer to solve: allocate once reuse later.
	cuda::GpuMat gI1, gI2, gs, t1, t2;

	cuda::GpuMat I1_2, I2_2, I1_I2;
	vector<cuda::GpuMat> vI1, vI2;

	cuda::GpuMat mu1, mu2;
	cuda::GpuMat mu1_2, mu2_2, mu1_mu2;

	cuda::GpuMat sigma1_2, sigma2_2, sigma12;
	cuda::GpuMat t3;

	cuda::GpuMat ssim_map;

	cuda::GpuMat buf;
};

void load_data(string& path, vector<Mat>& images);
void CurvatureFilter(Mat& images, int iteration);
void contrast(vector<Mat>& images);
Scalar getMSSIM_CUDA_optimized(Mat& i1, Mat& i2, BufferMSSIM& b);
Scalar getMSSIM(Mat& i1, Mat& i2);
void sort_frames_L2S(map<int, double> map, vector<int>& frame_sequence, int n_frames, int RATIO);
void sort_frames_S2L(map<int, double> map, vector<int>& frame_sequence, int n_frames, int RATIO);
void write_txt(string path, vector<int> frame_sequence);
void write_video(string path, vector<Mat> images_RGB, vector<int> frame_sequence, int fps);
double cal_SRCC(string& predict_path, string& truth_path);
double cal_SRCC_reverse(string& predict_path, string& truth_path);
double cal_MSE(vector<Mat> images_RGB, vector<int> frame_sequence, string Ground_Truth_path);
double cal_MSE_reverse(vector<Mat> images_RGB, vector<int> frame_sequence, string Ground_Truth_path);