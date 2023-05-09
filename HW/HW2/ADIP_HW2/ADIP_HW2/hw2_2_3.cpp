#include "Header.h"

void hw2_2_3() {
	// initial variable
	unsigned char* duck_region = new unsigned char[100 * 142];
	unsigned char* duck500x710_bilinear = new unsigned char[500 * 710];

	// load .raw file
	unsigned char* duck = read_raw("HW2_images_file/duck900x660.raw", 900, 660);

	// get duck_region
	for (int col = 0; col < 100; col++) {
		for (int row = 0; row < 142; row++) {
			*(duck_region + 100 * row + col) = *(duck + 900 * (row + 108) + col + 177);
		}
	}
	Mat mat_duck_region(142, 100, CV_8UC1, duck_region);

	// zoom in duck_region
	duck500x710_bilinear = bilinear(duck_region, 100, 142, 500, 710);
	Mat mat_duck500x710_bilinear(710, 500, CV_8UC1, duck500x710_bilinear);
	Mat mat_duck500x710_bicubic = bicubic(mat_duck_region, 5, 5);

	imshow("duck500x710_bilinear", mat_duck500x710_bilinear);
	imshow("duck500x710_bicubic", mat_duck500x710_bicubic);
	waitKey(0);
	destroyAllWindows();

	// write file
	imwrite("output_images_file/duck500x710_bilinear.png", mat_duck500x710_bilinear);
	printf("Save duck500x710_bilinear.png successfully...\n");

	imwrite("output_images_file/duck500x710_bicubic.png", mat_duck500x710_bicubic);
	printf("Save duck500x710_bicubic.png successfully...\n");
}