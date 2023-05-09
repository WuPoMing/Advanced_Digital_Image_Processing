#include "Header.h"

void hw3_1() {
	int WIDTH = 512;
	int HEIGHT = 512;

	uchar* cat = read_raw("cat_512.raw", WIDTH, HEIGHT);
	uchar* JackieChen = read_raw("JackieChen.raw", 621, 466);

	uchar* JackieChen_512 = nearest_neighbor(JackieChen, 621, 466, WIDTH, HEIGHT);		// Resize
	uchar* JackieChen_512_binarization = binarization(JackieChen_512, WIDTH, HEIGHT);	// Binarize

	// Replace bit-plane 0 with JackieChen
	uchar* eight_bit_plane = new uchar[WIDTH * HEIGHT];
	for (int i = 0; i < WIDTH * HEIGHT; i++) 
		eight_bit_plane[i] = (cat[i] & 254) + (JackieChen_512_binarization[i] & 1);

	// Get bit-plane 0 from eight_bit_plane
	uchar* bit_plane_0 = get_bit_plane(eight_bit_plane, WIDTH, HEIGHT, 0);
	uchar* bit_plane_1 = get_bit_plane(eight_bit_plane, WIDTH, HEIGHT, 1);
	uchar* bit_plane_2 = get_bit_plane(eight_bit_plane, WIDTH, HEIGHT, 2);
	uchar* bit_plane_3 = get_bit_plane(eight_bit_plane, WIDTH, HEIGHT, 3);
	uchar* bit_plane_4 = get_bit_plane(eight_bit_plane, WIDTH, HEIGHT, 4);
	uchar* bit_plane_5 = get_bit_plane(eight_bit_plane, WIDTH, HEIGHT, 5);
	uchar* bit_plane_6 = get_bit_plane(eight_bit_plane, WIDTH, HEIGHT, 6);
	uchar* bit_plane_7 = get_bit_plane(eight_bit_plane, WIDTH, HEIGHT, 7);

	// Save images
	save("01_eight_bit_plane.png", eight_bit_plane, WIDTH, HEIGHT);
	save("02_bit_plane_0.png", bit_plane_0, WIDTH, HEIGHT);
	save("03_bit_plane_1.png", bit_plane_1, WIDTH, HEIGHT);
	save("04_bit_plane_2.png", bit_plane_2, WIDTH, HEIGHT);
	save("05_bit_plane_3.png", bit_plane_3, WIDTH, HEIGHT);
	save("06_bit_plane_4.png", bit_plane_4, WIDTH, HEIGHT);
	save("07_bit_plane_5.png", bit_plane_5, WIDTH, HEIGHT);
	save("08_bit_plane_6.png", bit_plane_6, WIDTH, HEIGHT);
	save("09_bit_plane_7.png", bit_plane_7, WIDTH, HEIGHT);
}