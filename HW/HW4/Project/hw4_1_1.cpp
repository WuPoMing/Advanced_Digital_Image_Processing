# include"Header.h"

void hw4_1_1() {
	int WIDTH = 640;
	int HEIGHT = 427;
	uchar* img = read_raw("roof_640x427.raw", WIDTH, HEIGHT);
	uchar* img_noise = read_raw("roof_640x427_noise.raw", WIDTH, HEIGHT);
	int pad = 1;
	int NEW_WIDTH = WIDTH + 2 * pad;
	int NEW_HEIGHT = HEIGHT + 2 * pad;
	/*----------------------------------------------smaller output----------------------------------------------*/
	// roof_640x427 filter 1
	uchar* img_laplacian_filter_1 = laplacian_filter(img, WIDTH, HEIGHT, 1);
	Mat mat_img_laplacian_filter_1(425, 638, CV_8UC1, img_laplacian_filter_1);
	imwrite("01_roof_laplacian_filter_1.png", mat_img_laplacian_filter_1);

	// roof_640x427 filter 2
	uchar* img_laplacian_filter_2 = laplacian_filter(img, WIDTH, HEIGHT, 2);
	Mat mat_img_laplacian_filter_2(425, 638, CV_8UC1, img_laplacian_filter_2);
	imwrite("02_roof_laplacian_filter_2.png", mat_img_laplacian_filter_2);

	// roof_640x427_noise filter 1
	uchar* img_noise_laplacian_filter_1 = laplacian_filter(img_noise, WIDTH, HEIGHT, 1);
	Mat mat_img_noise_laplacian_filter_1(425, 638, CV_8UC1, img_noise_laplacian_filter_1);
	imwrite("03_roof_noise_laplacian_filter_1.png", mat_img_noise_laplacian_filter_1);

	// roof_640x427_noise filter 2
	uchar* img_noise_laplacian_filter_2 = laplacian_filter(img_noise, WIDTH, HEIGHT, 2);
	Mat mat_img_noise_laplacian_filter_2(425, 638, CV_8UC1, img_noise_laplacian_filter_2);
	imwrite("04_roof_noise_laplacian_filter_2.png", mat_img_noise_laplacian_filter_2);

	/*----------------------------------------------ad-hoc filters----------------------------------------------*/
	// roof_640x427 filter 1
	uchar* img_high_boost_filter_1 = high_boost_filter(img, WIDTH, HEIGHT, 1.7, 1);
	Mat mat_img_high_boost_filter_1(425, 638, CV_8UC1, img_high_boost_filter_1);
	imwrite("05_roof_high_boost_filter_1.png", mat_img_high_boost_filter_1);

	// roof_640x427 filter 2
	uchar* img_high_boost_filter_2 = high_boost_filter(img, WIDTH, HEIGHT, 1.7, 2);
	Mat mat_img_high_boost_filter_2(425, 638, CV_8UC1, img_high_boost_filter_2);
	imwrite("06_roof_high_boost_filter_2.png", mat_img_high_boost_filter_2);

	// roof_640x427_noise filter 1
	uchar* img_noise_high_boost_filter_1 = high_boost_filter(img_noise, WIDTH, HEIGHT, 1.7, 1);
	Mat mat_img_noise_high_boost_filter_1(425, 638, CV_8UC1, img_noise_high_boost_filter_1);
	imwrite("07_roof_noise_high_boost_filter_1.png", mat_img_noise_high_boost_filter_1);

	// roof_640x427_noise filter 2
	uchar* img_noise_high_boost_filter_2 = high_boost_filter(img_noise, WIDTH, HEIGHT, 1.7, 2);
	Mat mat_img_noise_high_boost_filter_2(425, 638, CV_8UC1, img_noise_high_boost_filter_2);
	imwrite("08_roof_noise_high_boost_filter_2.png", mat_img_noise_high_boost_filter_2);

	/*----------------------------------------------zero-padding----------------------------------------------*/
	uchar* img_zero_padding = zero_padding(img, WIDTH, HEIGHT, pad);
	uchar* img_noise_zero_padding = zero_padding(img_noise, WIDTH, HEIGHT, pad);

	// roof_640x427 filter 1
	uchar* img_zero_padding_laplacian_filter_1 = laplacian_filter(img_zero_padding, NEW_WIDTH, NEW_HEIGHT, 1);
	Mat mat_img_zero_padding_laplacian_filter_1(HEIGHT, WIDTH, CV_8UC1, img_zero_padding_laplacian_filter_1);
	imwrite("09_roof_zero_padding_laplacian_filter_1.png", mat_img_zero_padding_laplacian_filter_1);

	// roof_640x427 filter 2
	uchar* img_zero_padding_laplacian_filter_2 = laplacian_filter(img_zero_padding, NEW_WIDTH, NEW_HEIGHT, 2);
	Mat mat_img_zero_padding_laplacian_filter_2(HEIGHT, WIDTH, CV_8UC1, img_zero_padding_laplacian_filter_2);
	imwrite("10_roof_zero_padding_laplacian_filter_2.png", mat_img_zero_padding_laplacian_filter_2);

	// roof_640x427_noise filter 1
	uchar* img_noise_zero_padding_laplacian_filter_1 = laplacian_filter(img_noise_zero_padding, NEW_WIDTH, NEW_HEIGHT, 1);
	Mat mat_img_noise_zero_padding_laplacian_filter_1(HEIGHT, WIDTH, CV_8UC1, img_noise_zero_padding_laplacian_filter_1);
	imwrite("11_roof_noise_zero_padding_laplacian_filter_1.png", mat_img_noise_zero_padding_laplacian_filter_1);

	// roof_640x427_noise filter 2
	uchar* img_noise_zero_padding_laplacian_filter_2 = laplacian_filter(img_noise_zero_padding, NEW_WIDTH, NEW_HEIGHT, 2);
	Mat mat_img_noise_zero_padding_laplacian_filter_2(HEIGHT, WIDTH, CV_8UC1, img_noise_zero_padding_laplacian_filter_2);
	imwrite("12_roof_noise_zero_padding_laplacian_filter_2.png", mat_img_noise_zero_padding_laplacian_filter_2);

	/*----------------------------------------------replication padding----------------------------------------------*/
	uchar* img_replication_padding = replication_padding(img, WIDTH, HEIGHT, pad);
	uchar* img_noise_replication_padding = replication_padding(img_noise, WIDTH, HEIGHT, pad);

	// roof_640x427 filter 1
	uchar* img_replication_padding_laplacian_filter_1 = laplacian_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 1);
	Mat mat_img_replication_padding_laplacian_filter_1(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_laplacian_filter_1);
	imwrite("13_roof_replication_padding_laplacian_filter_1.png", mat_img_replication_padding_laplacian_filter_1);

	// roof_640x427 filter 2
	uchar* img_replication_padding_laplacian_filter_2 = laplacian_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 2);
	Mat mat_img_replication_padding_laplacian_filter_2(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_laplacian_filter_2);
	imwrite("14_roof_replication_padding_laplacian_filter_2.png", mat_img_replication_padding_laplacian_filter_2);

	// roof_640x427_noise filter 1
	uchar* img_noise_replication_padding_laplacian_filter_1 = laplacian_filter(img_noise_replication_padding, NEW_WIDTH, NEW_HEIGHT, 1);
	Mat mat_img_noise_replication_padding_laplacian_filter_1(HEIGHT, WIDTH, CV_8UC1, img_noise_replication_padding_laplacian_filter_1);
	imwrite("15_roof_noise_replication_padding_laplacian_filter_1.png", mat_img_noise_replication_padding_laplacian_filter_1);

	// roof_640x427_noise filter 2
	uchar* img_noise_replication_padding_laplacian_filter_2 = laplacian_filter(img_noise_replication_padding, NEW_WIDTH, NEW_HEIGHT, 2);
	Mat mat_img_noise_replication_padding_laplacian_filter_2(HEIGHT, WIDTH, CV_8UC1, img_noise_replication_padding_laplacian_filter_2);
	imwrite("16_roof_noise_replication_padding_laplacian_filter_2.png", mat_img_noise_replication_padding_laplacian_filter_2);
}