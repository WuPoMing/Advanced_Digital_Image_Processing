#include "Header.h"

void hw3_3_3() {
	uchar* cat = read_raw("cat_512.raw", 512, 512);
	uchar* Catch = read_raw("catch_300x168.raw", 300, 168);
	uchar* traffic = read_raw("traffic_970x646.raw", 970, 646);

	uchar* cat_histogram = get_histogram(cat, 512, 512);
	save("28_cat_histogram.png", cat_histogram, 256, 256);

	/*----------------------------------------catch----------------------------------------*/
	uchar* histogram_matching_cat_with_catch = histogram_matching(Catch, 300, 168, cat, 512, 512);
	save("29_histogram_matching_cat_with_catch.png", histogram_matching_cat_with_catch, 512, 512);

	uchar* catch_histogram = get_histogram(Catch, 300, 168);
	save("30_catch_histogram.png", catch_histogram, 256, 256);

	uchar* histogram_matching_cat_with_catch_histogram = get_histogram(histogram_matching_cat_with_catch, 512, 512);
	save("31_histogram_matching_cat_with_catch_histogram.png", histogram_matching_cat_with_catch_histogram, 256, 256);

	/*----------------------------------------traffic----------------------------------------*/
	uchar* histogram_matching_cat_with_traffic = histogram_matching(traffic, 970, 646, cat, 512, 512);
	save("32_histogram_matching_cat_with_traffic.png", histogram_matching_cat_with_traffic, 512, 512);

	uchar* traffic_histogram = get_histogram(traffic, 970, 646);
	save("33_traffic_histogram.png", traffic_histogram, 256, 256);

	uchar* histogram_matching_cat_with_traffic_histogram = get_histogram(histogram_matching_cat_with_traffic, 512, 512);
	save("34_histogram_matching_cat_with_traffic_histogram.png", histogram_matching_cat_with_traffic_histogram, 256, 256);
}