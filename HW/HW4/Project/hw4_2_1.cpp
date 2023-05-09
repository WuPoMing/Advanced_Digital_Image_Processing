# include"Header.h"

void hw4_2_1() {
	int WIDTH = 256;
	int HEIGHT = 256;
	uchar* block_and_white = read_raw("block&white_256.raw", WIDTH, HEIGHT);
	uchar* chessboard = read_raw("chessboard_256.raw", WIDTH, HEIGHT);
	int kernel_size = 5;
	int pad = floor(kernel_size / 2);
	int NEW_WIDTH = WIDTH + 2 * pad;
	int NEW_HEIGHT = HEIGHT + 2 * pad;

	uchar* block_and_white_replication_padding = replication_padding(block_and_white, WIDTH, HEIGHT, pad);
	uchar* block_and_white_replication_padding_mean_filter = mean_filter(block_and_white_replication_padding, NEW_WIDTH, NEW_HEIGHT, kernel_size);
	Mat mat_block_and_white_replication_padding_mean_filter(HEIGHT, WIDTH, CV_8UC1, block_and_white_replication_padding_mean_filter);
	imwrite("21_block_and_white_mean_filter.png", mat_block_and_white_replication_padding_mean_filter);

	uchar* block_and_white_replication_padding_mean_filter_histogram = get_histogram(block_and_white_replication_padding_mean_filter, HEIGHT, WIDTH);
	Mat mat_block_and_white_replication_padding_mean_filter_histogram(HEIGHT, WIDTH, CV_8UC1, block_and_white_replication_padding_mean_filter_histogram);
	imwrite("22_block_and_white_mean_filter_histogram.png", mat_block_and_white_replication_padding_mean_filter_histogram);

	uchar* chessboard_replication_padding = replication_padding(chessboard, WIDTH, HEIGHT, pad);
	uchar* chessboard_replication_padding_mean_filter = mean_filter(chessboard_replication_padding, NEW_WIDTH, NEW_HEIGHT, kernel_size);
	Mat mat_chessboard_replication_padding_mean_filter(HEIGHT, WIDTH, CV_8UC1, chessboard_replication_padding_mean_filter);
	imwrite("23_chessboard_mean_filter.png", mat_chessboard_replication_padding_mean_filter);

	uchar* chessboard_replication_padding_mean_filter_histogram = get_histogram(chessboard_replication_padding_mean_filter, HEIGHT, WIDTH);
	Mat mat_chessboard_replication_padding_mean_filter_histogram(HEIGHT, WIDTH, CV_8UC1, chessboard_replication_padding_mean_filter_histogram);
	imwrite("24_chessboard_mean_filter_histogram.png", mat_chessboard_replication_padding_mean_filter_histogram);
}