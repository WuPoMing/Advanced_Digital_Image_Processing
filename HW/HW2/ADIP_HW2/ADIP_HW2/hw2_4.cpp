#include "Header.h"

void hw2_4() {
	// initial variable
	int width = 100;
	int height = 100;

	// read image
	unsigned char* map100x100 = read_raw("HW2_images_file/map100x100.raw", width, height);

	// transform to CV
	Mat mat_map100x100(height, width, CV_8UC1, map100x100);

	// 畫搜尋路徑
	Mat D4_search_path = draw_D4_search_path(mat_map100x100, 0, 14, 34, 93);
	Mat D8_search_path = draw_D8_search_path(mat_map100x100, 0, 14, 34, 93);
	Mat Dm_search_path = draw_Dm_search_path(mat_map100x100, 0, 14, 34, 93);

	// 畫最短路徑
	Mat D4_shortest_path = draw_shortest_path(mat_map100x100, D4_search_path, 34, 93);
	Mat D8_shortest_path = draw_shortest_path(mat_map100x100, D8_search_path, 34, 93);
	Mat Dm_shortest_path = draw_shortest_path(mat_map100x100, Dm_search_path, 34, 93);

	// write file
	imwrite("output_images_file/D4_search_path.png", D4_search_path);
	printf("Save D4_search_path.png successfully...\n");
	imwrite("output_images_file/D4_shortest_path.png", D4_shortest_path);
	printf("Save D4_shortest_path.png successfully...\n");

	imwrite("output_images_file/D8_search_path.png", D8_search_path);
	printf("Save D8_search_path.png successfully...\n");
	imwrite("output_images_file/D8_shortest_path.png", D8_shortest_path);
	printf("Save D8_shortest_path.png successfully...\n");

	imwrite("output_images_file/Dm_search_path.png", Dm_search_path);
	printf("Save Dm_search_path.png successfully...\n");
	imwrite("output_images_file/Dm_shortest_path.png", Dm_shortest_path);
	printf("Save Dm_shortest_path.png successfully...\n");
}