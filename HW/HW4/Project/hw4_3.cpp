# include"Header.h"

void hw4_3() {
	int WIDTH = 683;
	int HEIGHT = 512;
	uchar* img = read_raw("tsukuba_683x512.raw", WIDTH, HEIGHT);
	Mat mat_img(HEIGHT, WIDTH, CV_8UC1, img);

	/*--------------------------------3x3--------------------------------*/
	int kernel_size = 3;
	int pad = floor(kernel_size / 2);
	int NEW_WIDTH = WIDTH + 2 * pad;
	int NEW_HEIGHT = HEIGHT + 2 * pad;

	uchar* img_replication_padding = replication_padding(img, WIDTH, HEIGHT, pad);
	uchar* img_replication_padding_local_histogram_equalization_3x3 = local_histogram_equalization(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, kernel_size);
	Mat mat_img_replication_padding_local_histogram_equalization_3x3(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_local_histogram_equalization_3x3);
	imwrite("32_tsukuba_local_histogram_equalization_3x3.png", mat_img_replication_padding_local_histogram_equalization_3x3);

	uchar* tsukuba_local_histogram_equalization_3x3_histogram = get_histogram(img_replication_padding_local_histogram_equalization_3x3, HEIGHT, WIDTH);
	Mat mat_tsukuba_local_histogram_equalization_3x3_histogram(256, 256, CV_8UC1, tsukuba_local_histogram_equalization_3x3_histogram);
	imwrite("33_tsukuba_local_histogram_equalization_3x3_histogram.png", mat_tsukuba_local_histogram_equalization_3x3_histogram);

	/*--------------------------------5x5--------------------------------*/
	kernel_size = 5;
	pad = floor(kernel_size / 2);
	NEW_WIDTH = WIDTH + 2 * pad;
	NEW_HEIGHT = HEIGHT + 2 * pad;

	img_replication_padding = replication_padding(img, WIDTH, HEIGHT, pad);
	uchar* img_replication_padding_local_histogram_equalization_5x5 = local_histogram_equalization(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, kernel_size);
	Mat mat_img_replication_padding_local_histogram_equalization_5x5(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_local_histogram_equalization_5x5);
	imwrite("34_tsukuba_local_histogram_equalization_5x5.png", mat_img_replication_padding_local_histogram_equalization_5x5);

	uchar* tsukuba_local_histogram_equalization_5x5_histogram = get_histogram(img_replication_padding_local_histogram_equalization_5x5, HEIGHT, WIDTH);
	Mat mat_tsukuba_local_histogram_equalization_5x5_histogram(256, 256, CV_8UC1, tsukuba_local_histogram_equalization_5x5_histogram);
	imwrite("35_tsukuba_local_histogram_equalization_5x5_histogram.png", mat_tsukuba_local_histogram_equalization_5x5_histogram);

	/*--------------------------------7x7--------------------------------*/
	kernel_size = 7;
	pad = floor(kernel_size / 2);
	NEW_WIDTH = WIDTH + 2 * pad;
	NEW_HEIGHT = HEIGHT + 2 * pad;

	img_replication_padding = replication_padding(img, WIDTH, HEIGHT, pad);
	uchar* img_replication_padding_local_histogram_equalization_7x7 = local_histogram_equalization(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, kernel_size);
	Mat mat_img_replication_padding_local_histogram_equalization_7x7(HEIGHT, WIDTH, CV_8UC1, img_replication_padding_local_histogram_equalization_7x7);
	imwrite("36_tsukuba_local_histogram_equalization_7x7.png", mat_img_replication_padding_local_histogram_equalization_7x7);

	uchar* tsukuba_local_histogram_equalization_7x7_histogram = get_histogram(img_replication_padding_local_histogram_equalization_7x7, HEIGHT, WIDTH);
	Mat mat_tsukuba_local_histogram_equalization_7x7_histogram(256, 256, CV_8UC1, tsukuba_local_histogram_equalization_7x7_histogram);
	imwrite("37_tsukuba_local_histogram_equalization_7x7_histogram.png", mat_tsukuba_local_histogram_equalization_7x7_histogram);
}