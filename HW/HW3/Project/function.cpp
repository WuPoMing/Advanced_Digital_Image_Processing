#include "Header.h"

uchar* read_raw(const char* img_name, int width, int height) {
	// initial variable
	FILE* input_file;
	int size = width * height;
	uchar* img = new uchar[size];

	// read file
	input_file = fopen(img_name, "rb");

	if (input_file == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	fread(img, 1, size, input_file);
	fclose(input_file);
	return img;
}

void save(const char* img_name, uchar* img, int width, int height) {
	Mat mat_img(height, width, CV_8UC1, img);
	imwrite(img_name, mat_img);
}

uchar* nearest_neighbor(uchar* img, int src_width, int src_height, int dst_width, int dst_height) {
	uchar* new_img = new uchar[dst_width * dst_height];

	for (int row = 0; row < dst_height; row++) {
		for (int col = 0; col < dst_width; col++) {
			int srcX = round(col * ((src_width - 1.0) / (dst_width - 1.0)));
			int srcY = round(row * ((src_height - 1.0) / (dst_height - 1.0)));
			*(new_img + row * dst_width + col) = *(img + src_width * srcY + srcX);
		}
	}
	return new_img;
}

uchar* binarization(uchar* img, int width, int height) {
	uchar* new_img = new uchar[width * height];

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (*(img + row * width + col) <= 127) {
				*(new_img + row * width + col) = 0;
			}
			else {
				*(new_img + row * width + col) = 255;
			}
		}
	}
	return new_img;
}

uchar* get_bit_plane(uchar* img, int width, int height, int plane) {
	uchar* bit_plane_x = new uchar[width * height];
	int x = pow(2, plane);

	for (int i = 0; i < width * height; i++) {
		bit_plane_x[i] = (img[i] & x);
		if (bit_plane_x[i] > 0) bit_plane_x[i] = 255;
	}
	return bit_plane_x;
}

uchar* power_law(uchar* img, int width, int height, double c, double gamma) {
	uchar* new_img = new uchar[width * height];

	for (int i = 0; i < width * height; i++) {
		int s = 255 * c * pow(img[i] / 255.0, gamma);
		if (s > 255) s = 255;
		if (s < 0) s = 0;
		new_img[i] = s;
	}
	return new_img;
}

uchar* piecewise_linear(uchar* img, int width, int height, int r1, int s1, int r2, int s2) {
	uchar* new_img = new uchar[width * height];

	for (int i = 0; i < width * height; i++) {
		int r = img[i];
		if (r < r1) {
			int s = r * (s1 / r1);
			if (s > 255) s = 255;
			if (s < 0) s = 0;
			new_img[i] = s;
		}
		else if (r1 <= r < r2) {
			int s = (r - r1) * ((s2 - s1) / (r2 - r1));
			if (s > 255) s = 255;
			if (s < 0) s = 0;
			new_img[i] = s;
		}
		else {
			int s = (r - r2) * ((255 - s2) / (255 - r2));
			if (s > 255) s = 255;
			if (s < 0) s = 0;
			new_img[i] = s;
		}
			
	}		
	return new_img;
}

void find_min_max(uchar* img, int width, int height) {
	int r_min = 255, r_max = 0;

	for (int i = 0; i < width * height; i++) {
		int r = img[i];
		if (r > r_max) r_max = r;
		if (r < r_min) r_min = r;
	}
	printf("(r_min, r_max) = (%d, %d)\n", r_min, r_max);
}

uchar* get_histogram(uchar* img, int width, int height) {
	int* histogram_count = new int[256]{ 0 };
	int max = 0;
	uchar* histogram = new uchar[256 * 256];

	for (int i = 0; i < width * height; i++) 
		histogram_count[img[i]]++;		// 計算各像素累積值
	
	for (int i = 0; i < 256; i++)
		if (histogram_count[i] > max) max = histogram_count[i];		// 找累積的最大值

	for (int i = 0; i < 256; i++)
		histogram_count[i] = round(255 * histogram_count[i] / max);	// 正規化 0 ~ 255

	// Draw Histogram
	for (int i = 0; i < 256 * 256; i++) histogram[i] = 255;		// 畫布背景填白

	for (int i = 0; i < 256; i++) {
		int val = 0;
		for (int j = 0; j < 256; j++) {
			if (histogram_count[i] > val) {
				histogram[256 * (255 - val) + i] = 0;
				val++;
			}
			else break;
		}
	}
	return histogram;
}

uchar* histogram_equalization(uchar* img, int width, int height) {
	int* histogram_count = new int[256]{ 0 };
	uchar* new_img = new uchar[width * height];

	for (int i = 0; i < width * height; i++)
		histogram_count[img[i]]++;		// 計算各像素累積值
	
	for (int i = 0; i < width * height; i++) {
		int count = 0;
		for (int j = 0; j < img[i]; j++) {
			count += histogram_count[j];
		}
		new_img[i] = (255.0 / (width * height)) * count;
	}

	return new_img;
}

uchar* histogram_matching(uchar* src_img, int src_width, int src_height, uchar* dst_img, int dst_width, int dst_height) {
	double* src_histogram_count = new double[256]{ 0 };
	double* dst_histogram_count = new double[256]{ 0 };
	double* src_cdf = new double[256]{ 0 };
	double* dst_cdf = new double[256]{ 0 };
	double* diff = new double[256]{ 0 };
	uchar* M = new uchar[256]{ 0 };
	uchar* new_img = new uchar[dst_width * dst_height];

	// src image
	for (int i = 0; i < src_width * src_height; i++)
		src_histogram_count[src_img[i]]++;		// 計算各像素累積值

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < i; j++) {
			src_cdf[i] += src_histogram_count[j] / (double)(src_width * src_height);		// 累加
		}
	}

	// dst image
	for (int i = 0; i < dst_width * dst_height; i++)
		dst_histogram_count[dst_img[i]]++;		// 計算各像素累積值

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < i; j++) {
			dst_cdf[i] += dst_histogram_count[j] / (double)(dst_width * dst_height);		// 累加
		}
	}

	// diff
	for (int i = 0; i < 256; i++) {

		for (int j = 0; j < 256; j++) {
			diff[j] = abs(dst_cdf[i] - src_cdf[j]);
		}

		int idx = 0;
		double val = diff[0];
		for (int k = 0; k < 256; k++) {
			if (diff[k] < val) {
				val = diff[k];
				idx = k;
			}
		}
		M[i] = idx;
	}

	for (int i = 0; i < dst_width * dst_height; i++) {
		new_img[i] = M[dst_img[i]];
	}

	return new_img;
}