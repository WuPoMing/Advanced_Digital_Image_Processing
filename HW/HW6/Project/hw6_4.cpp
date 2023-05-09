#include "Header.h"

void hw6_4() {
	int WIDTH = 512;
	int HEIGHT = 512;
	uchar* map = read_raw("map_512.raw", WIDTH, HEIGHT);

	uchar* map_morphology = get_erosion(map, WIDTH, HEIGHT, 1, 5);
	uchar* map_thin = thin(map_morphology, WIDTH, HEIGHT);
	for (int _ = 0; _ < 20; _++) {
		map_thin = thin(map_thin, WIDTH, HEIGHT);
	}
	Mat mat_map_thin(HEIGHT, WIDTH, CV_8UC1, map_thin);
	imwrite("09_map_thin.png", mat_map_thin);

	int* map_thin_search_path = draw_D8_search_path(mat_map_thin, 406, 510, 121, 205);
	Mat map_thin_shortest_path = draw_shortest_path(mat_map_thin, map_thin_search_path, 121, 205);
	imwrite("10_map_thin_path.png", map_thin_shortest_path);
}