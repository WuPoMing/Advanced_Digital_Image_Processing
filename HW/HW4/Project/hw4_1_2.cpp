# include"Header.h"

void hw4_1_2() {
	int WIDTH = 640;
	int HEIGHT = 427;
	uchar* img = read_raw("roof_640x427.raw", WIDTH, HEIGHT);
	uchar* img_noise = read_raw("roof_640x427_noise.raw", WIDTH, HEIGHT);
	int pad = 1;
	int NEW_WIDTH = WIDTH + 2 * pad;
	int NEW_HEIGHT = HEIGHT + 2 * pad;

	uchar* img_replication_padding = replication_padding(img, WIDTH, HEIGHT, pad);
	uchar* img_noise_replication_padding = replication_padding(img_noise, WIDTH, HEIGHT, pad);

	// roof_640x427 filter 1
	uchar* img_replication_padding_sobel_filter_1 = sobel_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 1);
	Mat mat_img_replication_padding_sobel_filter_1(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_sobel_filter_1);
	imwrite("17_roof_sobel_filter_1.png", mat_img_replication_padding_sobel_filter_1);

	// roof_640x427 filter 2
	uchar* img_replication_padding_sobel_filter_2 = sobel_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, 2);
	Mat mat_img_replication_padding_sobel_filter_2(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_sobel_filter_2);
	imwrite("18_roof_sobel_filter_2.png", mat_img_replication_padding_sobel_filter_2);

	// roof_640x427_noise filter 1
	uchar* img_noise_replication_padding_sobel_filter_1 = sobel_filter(img_noise_replication_padding, NEW_WIDTH, NEW_HEIGHT, 1);
	Mat mat_img_noise_replication_padding_sobel_filter_1(HEIGHT, WIDTH, CV_8UC1, img_noise_replication_padding_sobel_filter_1);
	imwrite("19_roof_noise_sobel_filter_1.png", mat_img_noise_replication_padding_sobel_filter_1);

	// roof_640x427_noise filter 2
	uchar* img_noise_replication_padding_sobel_filter_2 = sobel_filter(img_noise_replication_padding, NEW_WIDTH, NEW_HEIGHT, 2);
	Mat mat_img_noise_replication_padding_sobel_filter_2(HEIGHT, WIDTH, CV_8UC1, img_noise_replication_padding_sobel_filter_2);
	imwrite("20_roof_noise_sobel_filter_2.png", mat_img_noise_replication_padding_sobel_filter_2);
}