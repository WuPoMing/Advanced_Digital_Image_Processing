#include "Header.h"
#define PI 3.1415926535

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

uchar* zero_padding(uchar* img, int width, int height, int pad) {
	int new_width = width + 2 * pad;
	int new_height = height + 2 * pad;
	int new_size = new_width * new_height;
	uchar* new_img = new uchar[new_size]{ 0 };

	for (int y = 0; y < new_height; y++) {
		for (int x = 0; x < new_width; x++) {
			if (x > pad - 1 && x < pad + width && y > pad - 1 && y < pad + height)
				new_img[x + y * new_width] = img[x - pad + (y - pad) * width];
		}
	}
	return new_img;
}

uchar* replication_padding(uchar* img, int width, int height, int pad) {
	int new_width = width + 2 * pad;
	int new_height = height + 2 * pad;
	int new_size = new_width * new_height;
	uchar* new_img = new uchar[new_size];

	for (int y = 0; y < new_height; y++) {
		for (int x = 0; x < new_width; x++) {
			// left
			if (x < pad && y > pad - 1 && y < pad + height)
				new_img[x + y * new_width] = img[(y - pad) * width];
			// right
			if (x > pad + width - 1 && y > pad - 1 && y < pad + height)
				new_img[x + y * new_width] = img[width - 1 + (y - pad) * width];
			// top
			if (y < pad && x > pad - 1 && x < pad + width)
				new_img[x + y * new_width] = img[x - pad];
			// botton
			if (y > pad + height - 1 && x > pad - 1 && x < pad + width)
				new_img[x + y * new_width] = img[x - pad + (height - 1) * width];
			// left top
			if (x < pad && y < pad)
				new_img[x + y * new_width] = img[0];
			// right top
			if (x > pad + width - 1 && y < pad)
				new_img[x + y * new_width] = img[width - 1];
			// left botton
			if (x < pad && y > pad + height - 1)
				new_img[x + y * new_width] = img[(height - 1) * width];
			// right botton
			if (x > pad + width - 1 && y > pad + height - 1)
				new_img[x + y * new_width] = img[height * width - 1];
			// origin
			if (x > pad - 1 && x < pad + width && y > pad - 1 && y < pad + height)
				new_img[x + y * new_width] = img[x - pad + (y - pad) * width];
		}
	}
	return new_img;
}

uchar* laplacian_filter(uchar* img, int width, int height, int kernel_type) {
	// kernel_type = 1
	double kernel_1[3][3] = {
		{0, -1, 0}, 
		{-1, 4, -1}, 
		{0, -1, 0} 
	};
	// kernel_type = 2
	double kernel_2[3][3] = {
		{-1, -1, -1},
		{-1, 8, -1},
		{-1, -1, -1}
	};

	int pad = 1;
	int NEW_WIDTH = width - 2 * pad;
	int NEW_HEIGHT = height - 2 * pad;
	uchar* new_img = new uchar[NEW_WIDTH * NEW_HEIGHT];
	double v = 0;
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			v = 0;
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					if(kernel_type == 1)
						v += img[x + dx + (y + dy) * width] * kernel_1[dy + 1][dx + 1];
					else
						v += img[x + dx + (y + dy) * width] * kernel_2[dy + 1][dx + 1];
				}
			}
			v = fmax(v, 0);
			v = fmin(v, 255);
			new_img[x - pad + (y - pad) * NEW_WIDTH] = (uchar)v;
		}
	}
	return new_img;
}

uchar* sobel_filter(uchar* img, int width, int height, int kernel_type) {
	// kernel_type = 1
	double kernel_1[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};
	// kernel_type = 2
	double kernel_2[3][3] = {
		{-1, -2, -1},
		{0, 0, 0},
		{1, 2, 1}
	};

	int pad = 1;
	int NEW_WIDTH = width - 2 * pad;
	int NEW_HEIGHT = height - 2 * pad;
	uchar* new_img = new uchar[NEW_WIDTH * NEW_HEIGHT];
	double v = 0;
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			v = 0;
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					if (kernel_type == 1)
						v += img[x + dx + (y + dy) * width] * kernel_1[dy + 1][dx + 1];
					else
						v += img[x + dx + (y + dy) * width] * kernel_2[dy + 1][dx + 1];
				}
			}
			v = fmax(v, 0);
			v = fmin(v, 255);
			new_img[x - pad + (y - pad) * NEW_WIDTH] = (uchar)v;
		}
	}
	return new_img;
}

uchar* mean_filter(uchar* img, int width, int height, int kernel_size) {
	int pad = floor(kernel_size / 2);
	int NEW_WIDTH = width - 2 * pad;
	int NEW_HEIGHT = height - 2 * pad;
	uchar* new_img = new uchar[NEW_WIDTH * NEW_HEIGHT];
	double v = 0;
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			v = 0;
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					v += (int)img[x + dx + (y + dy) * width];
				}
			}
			v /= (kernel_size * kernel_size);
			new_img[x - pad + (y - pad) * NEW_WIDTH] = (uchar)v;
		}
	}
	return new_img;
}

uchar* median_filter(uchar* img, int width, int height, int kernel_size) {
	int pad = floor(kernel_size / 2);
	int NEW_WIDTH = width - 2 * pad;
	int NEW_HEIGHT = height - 2 * pad;
	uchar* new_img = new uchar[NEW_WIDTH * NEW_HEIGHT];
	double v = 0;
	int* vs = new int[kernel_size * kernel_size];
	int count = 0;
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			v = 0;
			count = 0;

			for (int i = 0; i < kernel_size * kernel_size; i++) {
				vs[i] = 999;
			}

			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					vs[count++] = (int)img[x + dx + (y + dy) * width];
				}
			}

			sort(vs, vs + (kernel_size * kernel_size));
			new_img[x - pad + (y - pad) * NEW_WIDTH] = (uchar)vs[int(floor(count / 2)) + 1];
		}
	}
	return new_img;
}

uchar* gaussian_filter(uchar* img, int width, int height, double sigma, int kernel_size) {
	int pad = floor(kernel_size / 2);
	int NEW_WIDTH = width - 2 * pad;
	int NEW_HEIGHT = height - 2 * pad;

	uchar* new_img = new uchar[NEW_WIDTH * NEW_HEIGHT];

	// kernel
	int _x = 0, _y = 0;
	double kernel_sum = 0;

	// get gaussian kernel
	float* kernel = new float[kernel_size * kernel_size];

	for (int y = 0; y < kernel_size; y++) {
		for (int x = 0; x < kernel_size; x++) {
			_y = y - pad;
			_x = x - pad;
			kernel[x + y * kernel_size] = 1 / (2 * PI * sigma * sigma) * exp(-(_x * _x + _y * _y) / (2 * sigma * sigma));
			kernel_sum += kernel[x + y * kernel_size];
		}
	}

	for (int y = 0; y < kernel_size; y++) {
		for (int x = 0; x < kernel_size; x++) {
			kernel[x + y * kernel_size] /= kernel_sum;
		}
	}

	// filtering
	double v = 0;
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			v = 0;
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					v += (double)img[x + dx + (y + dy) * width] * kernel[dx + pad + (dy + pad) * kernel_size];
				}
			}
			new_img[x - pad + (y - pad) * NEW_WIDTH] = (uchar)v;
		}
	}
	return new_img;
}

uchar* high_boost_filter(uchar* img, int width, int height, double A, int kernel_type) {
	// kernel_type = 1
	double kernel_1[3][3] = {
		{0, -1, 0},
		{-1, A+4, -1},
		{0, -1, 0}
	};
	// kernel_type = 2
	double kernel_2[3][3] = {
		{-1, -1, -1},
		{-1, A+8, -1},
		{-1, -1, -1}
	};

	int pad = 1;
	int NEW_WIDTH = width - 2 * pad;
	int NEW_HEIGHT = height - 2 * pad;
	uchar* new_img = new uchar[NEW_WIDTH * NEW_HEIGHT];
	double v = 0;
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			v = 0;
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					if (kernel_type == 1)
						v += img[x + dx + (y + dy) * width] * kernel_1[dy + 1][dx + 1];
					else
						v += img[x + dx + (y + dy) * width] * kernel_2[dy + 1][dx + 1];
				}
			}
			v = fmax(v, 0);
			v = fmin(v, 255);
			new_img[x - pad + (y - pad) * NEW_WIDTH] = (uchar)v;
		}
	}
	return new_img;
}

uchar* original_plus_laplacian_filter(uchar* img, int width, int height, int kernel_type) {
	// kernel_type = 1
	double kernel_1[3][3] = {
		{0, -1, 0},
		{-1, 5, -1},
		{0, -1, 0}
	};
	// kernel_type = 2
	double kernel_2[3][3] = {
		{-1, -1, -1},
		{-1, 9, -1},
		{-1, -1, -1}
	};

	int pad = 1;
	int NEW_WIDTH = width - 2 * pad;
	int NEW_HEIGHT = height - 2 * pad;
	uchar* new_img = new uchar[NEW_WIDTH * NEW_HEIGHT];
	double v = 0;
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			v = 0;
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					if (kernel_type == 1)
						v += img[x + dx + (y + dy) * width] * kernel_1[dy + 1][dx + 1];
					else
						v += img[x + dx + (y + dy) * width] * kernel_2[dy + 1][dx + 1];
				}
			}
			v = fmax(v, 0);
			v = fmin(v, 255);
			new_img[x - pad + (y - pad) * NEW_WIDTH] = (uchar)v;
		}
	}
	return new_img;
}

uchar* local_histogram_equalization(uchar* img, int width, int height, int kernel_size) {
	int pad = floor(kernel_size / 2);
	int NEW_WIDTH = width - 2 * pad;
	int NEW_HEIGHT = height - 2 * pad;
	uchar* new_img = new uchar[NEW_WIDTH * NEW_HEIGHT];
	int v;
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			v = 0;
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					if (img[x + y * width] > img[x + dx + (y + dy) * width]) v ++;
				}
			}
			new_img[x - pad + (y - pad) * NEW_WIDTH] = v * 255.0 / (kernel_size * kernel_size);
		}
	}
	return new_img;
}