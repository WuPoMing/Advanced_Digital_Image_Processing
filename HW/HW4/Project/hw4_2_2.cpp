# include"Header.h"

void hw4_2_2() {
	int WIDTH = 256;
	int HEIGHT = 256;
	uchar* img = read_raw("baboon_256.raw", WIDTH, HEIGHT);

	/*------------------------------------- 3x3 Gaussian filter-------------------------------------*/
	int kernel_size = 3;
	int pad = floor(kernel_size / 2);
	int NEW_WIDTH = WIDTH + 2 * pad;
	int NEW_HEIGHT = HEIGHT + 2 * pad;
	uchar* img_replication_padding = replication_padding(img, WIDTH, HEIGHT, pad);

	// sigma = 0.8
	uchar* img_replication_padding_gaussian_filter_3x3_0_point_8 = gaussian_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 0.8, 3);
	Mat mat_img_replication_padding_gaussian_filter_3x3_0_point_8(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_gaussian_filter_3x3_0_point_8);
	imwrite("25_baboon_gaussian_filter_3x3_0_point_8.png", mat_img_replication_padding_gaussian_filter_3x3_0_point_8);

	// sigma = 1.3
	uchar* img_replication_padding_gaussian_filter_3x3_1_point_3 = gaussian_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 1.3, 3);
	Mat mat_img_replication_padding_gaussian_filter_3x3_1_point_3(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_gaussian_filter_3x3_1_point_3);
	imwrite("26_baboon_gaussian_filter_3x3_1_point_3.png", mat_img_replication_padding_gaussian_filter_3x3_1_point_3);

	// sigma = 2
	uchar* img_replication_padding_gaussian_filter_3x3_2 = gaussian_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 2, 3);
	Mat mat_img_replication_padding_gaussian_filter_3x3_2(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_gaussian_filter_3x3_2);
	imwrite("27_baboon_gaussian_filter_3x3_2.png", mat_img_replication_padding_gaussian_filter_3x3_2);

	/*------------------------------------- 5x5 Gaussian filter-------------------------------------*/
	kernel_size = 5;
	pad = floor(kernel_size / 2);
	NEW_WIDTH = WIDTH + 2 * pad;
	NEW_HEIGHT = HEIGHT + 2 * pad;
	img_replication_padding = replication_padding(img, WIDTH, HEIGHT, pad);

	// sigma = 0.8
	uchar* img_replication_padding_gaussian_filter_5x5_0_point_8 = gaussian_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 0.8, 5);
	Mat mat_img_replication_padding_gaussian_filter_5x5_0_point_8(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_gaussian_filter_5x5_0_point_8);
	imwrite("28_baboon_gaussian_filter_5x5_0_point_8.png", mat_img_replication_padding_gaussian_filter_5x5_0_point_8);

	// sigma = 1.3
	uchar* img_replication_padding_gaussian_filter_5x5_1_point_3 = gaussian_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 1.3, 5);
	Mat mat_img_replication_padding_gaussian_filter_5x5_1_point_3(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_gaussian_filter_5x5_1_point_3);
	imwrite("29_baboon_gaussian_filter_5x5_1_point_3.png", mat_img_replication_padding_gaussian_filter_5x5_1_point_3);
	// sigma = 2
	uchar* img_replication_padding_gaussian_filter_5x5_2 = gaussian_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 2, 5);
	Mat mat_img_replication_padding_gaussian_filter_5x5_2(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_gaussian_filter_5x5_2);
	imwrite("30_baboon_gaussian_filter_5x5_2.png", mat_img_replication_padding_gaussian_filter_5x5_2);
}