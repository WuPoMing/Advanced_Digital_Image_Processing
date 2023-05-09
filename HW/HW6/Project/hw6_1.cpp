#include "Header.h"

void hw6_1() {
	int WIDTH = 512;
	int HEIGHT = 512;
	uchar* words = read_raw("words_512.raw", WIDTH, HEIGHT);

	uchar* words_morphology = get_erosion(words, WIDTH, HEIGHT, 2, 1);
	words_morphology = get_dilation(words_morphology, WIDTH, HEIGHT, 2, 1);
	words_morphology = get_erosion(words_morphology, WIDTH, HEIGHT, 2, 1);
	words_morphology = get_dilation(words_morphology, WIDTH, HEIGHT, 3, 1);
	words_morphology = get_erosion(words_morphology, WIDTH, HEIGHT, 4, 1);
	words_morphology = get_dilation(words_morphology, WIDTH, HEIGHT, 1, 1);

	Mat out(HEIGHT, WIDTH, CV_8UC1, words_morphology);
	imwrite("01_words_morphology.png", out);
}