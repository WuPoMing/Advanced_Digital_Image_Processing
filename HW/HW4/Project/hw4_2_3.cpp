# include"Header.h"

void hw4_2_3() {
	int WIDTH = 790;
	int HEIGHT = 720;
	uchar* img = read_raw("house_blur_noise_790x720.raw", WIDTH, HEIGHT);
	Mat mat_img(HEIGHT, WIDTH, CV_8UC1, img);

	int kernel_size = 3;
	int pad = floor(kernel_size / 2);
	int NEW_WIDTH = WIDTH + 2 * pad;
	int NEW_HEIGHT = HEIGHT + 2 * pad;

	// median filter
	uchar* img_replication_padding = replication_padding(img, WIDTH, HEIGHT, pad);
	uchar* img_out = median_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, kernel_size);

	img_replication_padding = replication_padding(img_out, WIDTH, HEIGHT, pad);
	img_out = median_filter(img_replication_padding, NEW_WIDTH, NEW_HEIGHT, kernel_size);

	uchar* img_histogram_equalization = histogram_equalization(img_out, WIDTH, HEIGHT);

	Mat out(HEIGHT, WIDTH, CV_8UC1, img_histogram_equalization);
	imwrite("31_house.png", out);
}