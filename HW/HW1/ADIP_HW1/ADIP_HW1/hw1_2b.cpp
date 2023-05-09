#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "Header.h"
using namespace cv;

void hw1_2b() {
	// initial variable
	char  input_img[] = "HM1_images_file/JackieChen.raw";	// Input  raw image name
	char output_img[] = "output_images_file/JackieChen_out.raw";	// Output raw image name
	FILE* input_file;
	FILE* output_file;
	int width = 621;
	int height = 466;
	int size = width * height;
	unsigned char* img_JackieChen = new unsigned char[size]; // array for image data

	// read file
	input_file = fopen(input_img, "rb");

	if (input_file == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}

	fread(img_JackieChen, 1, size, input_file);

	// Transfer data type to OpenCV
	// OpenCV uses Mat as image data type
	// create a Mat and input raw image data, beware of image type
	Mat mat_JackieChen(height, width, CV_8UC1, img_JackieChen);

	// put text
	putText(mat_JackieChen, "111318096", Point(130, 50), FONT_HERSHEY_SCRIPT_COMPLEX, 2, CV_RGB(0, 0, 0), 3, 8);
	putText(mat_JackieChen, "WFT?", Point(230, 430), FONT_HERSHEY_SCRIPT_COMPLEX, 2, CV_RGB(0, 0, 0), 3, 8);

	// Create window and show your Image
	imshow("JackieChen in opencv", mat_JackieChen);
	waitKey(0);
	destroyAllWindows();

	// Save Image as raw format
	output_file = fopen(output_img, "wb");
	fwrite(img_JackieChen, 1, size, output_file);
	printf("Save %s successfully...\n", output_img);

	// Save Image using opencv
	cv::imwrite("output_images_file/JackieChen_out_opencv.png", mat_JackieChen);
	printf("Save output_images_file/JackieChen_out_opencv.png successfully...\n");

	// Release memory
	delete[] img_JackieChen;
	fclose(input_file);
	fclose(output_file);
}