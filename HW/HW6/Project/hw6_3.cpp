#include "Header.h"

void hw6_3() {
	int WIDTH = 600;
	int HEIGHT = 600;
	uchar* monster = read_raw("monster_600.raw", WIDTH, HEIGHT);

	uchar* monster_binarize = binarization(monster, WIDTH, HEIGHT, 245);
	uchar* monster_morphology = get_close(monster_binarize, WIDTH, HEIGHT, 3);
	for (int _ = 0; _ < 13; _++) {
		monster_morphology = get_close(monster_morphology, WIDTH, HEIGHT, 3);
	}
	uchar* monster_trimap = get_dilation(monster_morphology, WIDTH, HEIGHT, 1, 5);
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		int diff = monster_trimap[i] - monster_morphology[i];
		if (diff != 0)
			monster_trimap[i] = 128;
		else
			monster_trimap[i] = monster_morphology[i];
	}
	Mat out(HEIGHT, WIDTH, CV_8UC1, monster_trimap);
	imwrite("08_monster_trimap.png", out);
}