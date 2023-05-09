#include "Header.h"
#define PI 3.1415926535

/*------------------------------------------------------------------------------hw1------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------hw2------------------------------------------------------------------------------*/
double get_MSE_from_two_imgs(uchar* img_1, uchar* img_2, int width, int height) {
	double error = 0;
	int size = width * height;

	for (int i = 0; i < size; i++) {
		error += pow(*(img_2 + i) - *(img_1 + i), 2);
	}
	return error / size;
}

double get_PSNR_from_two_imgs(uchar* img_1, uchar* img_2, int width, int height) {
	int MAX = 255;
	return 10 * log10(pow(MAX, 2) / get_MSE_from_two_imgs(img_1, img_2, width, height));
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

uchar* binarization(uchar* img, int width, int height, int threshold) {
	uchar* new_img = new uchar[width * height];

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (*(img + row * width + col) <= threshold) {
				*(new_img + row * width + col) = 255;
			}
			else {
				*(new_img + row * width + col) = 0;
			}
		}
	}
	return new_img;
}

int* draw_D8_search_path(Mat img, int x, int y, int s, int t) {
	int width = img.cols;
	int height = img.rows;
	int d[512][512];
	int dx[8] = { -1, 1, 1, -1, 1, 0, -1, 0 };	// 左上 右上 右下 左下 右 下 左 上
	int dy[8] = { -1, -1, 1, 1, 0 , 1, 0, -1 };
	const int INF = 10000000000;
	typedef pair<int, int > P;
	queue<P> que;

	// 初始化所有點的距離為INF 
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			d[x][y] = INF;
		}
	}

	// 把起點加入佇列，並設距離為 0 
	que.push(P(x, y));
	d[x][y] = 0;

	while (que.size()) {
		P p = que.front();
		que.pop();
		if (p.first == s && p.second == t) break;	// 如果取出的狀態是終點，則搜尋結束

		for (int i = 0; i < 8; i++) {
			int nx = p.first + dx[i];
			int ny = p.second + dy[i];

			if (0 <= nx && nx < width && 0 <= ny && ny < height && img.at<uchar>(Point(nx, ny)) == 255 && d[nx][ny] == INF) {
				que.push(P(nx, ny));
				d[nx][ny] = d[p.first][p.second] + 1;
			}
		}
	}
	printf("The shortest distance using D8: %d\n", d[s][t]);	// 顯示從初始點走到終點的最短步數

	int* out = new int[width * height];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			out[x + y * width] = d[x][y];
		}
	}
	return out;
}

Mat draw_shortest_path(Mat img, int* search_path, int s, int t) {
	int width = img.cols;
	int height = img.rows;
	int dx[8] = { 1, 0, -1, 0, -1, 1, 1, -1 };	// 右 下 左 上 左上 右上 右下 左下
	int dy[8] = { 0, 1, 0, -1, -1, -1, 1, 1 };

	Mat out(img.rows, img.cols, CV_8UC1);
	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			//out.at<uchar>(Point(x, y)) = img.at<uchar>(Point(x, y));
			out.at<uchar>(Point(x, y)) = 0;
		}
	}

	out.at<uchar>(Point(s, t)) = 200;
	while (1) {
		if (search_path[s + t * width] == 0) break;

		for (int i = 0; i < 8; i++) {
			if (search_path[s + dx[i] + (t + dy[i]) * width] == (search_path[s + t * width] - 1)) {
				out.at<uchar>(Point(s + dx[i], t + dy[i])) = 255;
				s = s + dx[i];
				t = t + dy[i];
				break;
			}
		}
	}
	return out;
}

/*------------------------------------------------------------------------------hw3------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------hw4------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------hw5------------------------------------------------------------------------------*/
complex<double>* DFT(uchar* img, int width, int height) {
	double* fourier_series_real = new double[width * height];
	double* fourier_series_imag = new double[width * height];
	complex<double>* fourier_series = new complex<double>[width * height];

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			double real = 0;
			double imag = 0;
			for (int x = 0; x < width; x++) {
				double I = img[x + h * width];
				double theta = 2.0 * PI * (double)w * (double)x / (double)width;
				real += I * cos(theta) * pow(-1, x);
				imag += I * -sin(theta) * pow(-1, x);
			}
			fourier_series_real[w + h * width] = real;
			fourier_series_imag[w + h * width] = imag;
		}
	}

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			double real = 0;
			double imag = 0;
			for (int y = 0; y < height; y++) {
				double fs_real = fourier_series_real[w + y * width];
				double fs_imag = fourier_series_imag[w + y * width];
				double theta = 2.0 * PI * (double)h * (double)y / (double)height;
				real += (fs_real * cos(theta) + fs_imag * sin(theta)) * pow(-1, y);
				imag += (fs_imag * cos(theta) - fs_real * sin(theta)) * pow(-1, y);
			}
			fourier_series[w + h * width] = complex<double>(real, imag);
		}
	}

	return fourier_series;
}

uchar* get_magnitude_spectrum(complex<double>* fourier_series, int width, int height) {
	uchar* out = new uchar[width * height];
	double max = -1;

	for (int i = 0; i < width * height; i++) {
		double val = log(1 + sqrt(pow(fourier_series[i].real(), 2) + pow(fourier_series[i].imag(), 2)));
		if (val > max)
			max = val;
	}

	for (int i = 0; i < width * height; i++) {
		double val = log(1 + sqrt(pow(fourier_series[i].real(), 2) + pow(fourier_series[i].imag(), 2))) * 255.0 / max;
		if (val > 255) val = 255;
		out[i] = (uchar)val;
	}

	return out;
}

uchar* IDFT(complex<double>* fourier_series, int width, int height) {
	uchar* out = new uchar[width * height];
	double* fourier_series_real = new double[width * height];
	double* fourier_series_imag = new double[width * height];
	complex<double>* fs_idft = new complex<double>[width * height];

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double real = 0;
			double imag = 0;
			for (int w = 0; w < width; w++) {
				complex<double> fs_dft = fourier_series[w + y * width];
				double theta = 2.0 * PI * (double)w * (double)x / (double)width;
				real += (fs_dft.real() * cos(theta) - fs_dft.imag() * sin(theta));
				imag += (fs_dft.imag() * cos(theta) + fs_dft.real() * sin(theta));
			}
			fourier_series_real[x + y * width] = real;
			fourier_series_imag[x + y * width] = imag;
		}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double real = 0;
			double imag = 0;
			for (int h = 0; h < height; h++) {
				double fs_real = fourier_series_real[x + h * width];
				double fs_imag = fourier_series_imag[x + h * width];
				double theta = 2.0 * PI * (double)h * (double)y / (double)height;
				real += (fs_real * cos(theta) - fs_imag * sin(theta));
				imag += (fs_imag * cos(theta) + fs_real * sin(theta));
			}
			fs_idft[x + y * width] = complex<double>(real, imag);
		}
	}

	double max = -1;

	for (int i = 0; i < width * height; i++) {
		double val = sqrt(pow(fs_idft[i].real(), 2) + pow(fs_idft[i].imag(), 2));
		if (val > max)
			max = val;
	}

	for (int i = 0; i < width * height; i++) {
		double val = sqrt(pow(fs_idft[i].real(), 2) + pow(fs_idft[i].imag(), 2)) * 255.0 / max;
		if (val > 255) val = 255;
		out[i] = (uchar)val;
	}

	return out;
}

FT_CV DFT_and_IDFT_CV(uchar* img, int width, int height) {
	TickMeter time;
	Mat mat_img(height, width, CV_8UC1, img);
	FT_CV FT;
	Mat padded;
	int m = getOptimalDFTSize(mat_img.rows);
	int n = getOptimalDFTSize(mat_img.cols);
	copyMakeBorder(mat_img, padded, 0, m - mat_img.rows, 0, n - mat_img.cols, BORDER_CONSTANT, Scalar::all(0));
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat fourier_series;
	merge(planes, 2, fourier_series);

	time.reset(); time.start();
	dft(fourier_series, fourier_series);
	time.stop();
	cout << "DFT execution time: " << time << endl;

	split(fourier_series, planes);
	magnitude(planes[0], planes[1], planes[0]);
	FT.magnitude_spectrum = planes[0];
	FT.magnitude_spectrum += Scalar::all(1);
	log(FT.magnitude_spectrum, FT.magnitude_spectrum);
	FT.magnitude_spectrum = FT.magnitude_spectrum(Rect(0, 0, FT.magnitude_spectrum.cols & -2, FT.magnitude_spectrum.rows & -2));

	int cx = FT.magnitude_spectrum.cols / 2;
	int cy = FT.magnitude_spectrum.rows / 2;

	Mat tmp;
	Mat q0(FT.magnitude_spectrum, Rect(0, 0, cx, cy));
	Mat q1(FT.magnitude_spectrum, Rect(cx, 0, cx, cy));
	Mat q2(FT.magnitude_spectrum, Rect(0, cy, cx, cy));
	Mat q3(FT.magnitude_spectrum, Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(FT.magnitude_spectrum, FT.magnitude_spectrum, 0, 1, NORM_MINMAX);
	FT.magnitude_spectrum *= 255;
	
	// IDFT
	time.reset(); time.start();
	idft(fourier_series, FT.out_idft, DFT_REAL_OUTPUT);
	time.stop();
	cout << "IDFT execution time: " << time << endl;
	normalize(FT.out_idft, FT.out_idft, 0, 1, NORM_MINMAX);
	FT.out_idft *= 255;

	return FT;
}

uchar* DCT(uchar* img, int width, int height) {
	uchar* out = new uchar[width * height];
	double* dctx = new double[width * height];
	double* dctxy = new double[width * height];
	
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			double aw;
			if (w == 0)
				aw = sqrt(1.0 / width);
			else
				aw = sqrt(2.0 / width);

			double tmp = 0.0;
			for (int x = 0; x < width; x++) {
				tmp += img[x + h * width] * cos((2 * x + 1) * w * PI / (2.0 * width));
			}
			dctx[w + h * width] = aw * tmp;
		}
	}

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			double ah;
			if (h == 0)
				ah = sqrt(1.0 / height);
			else
				ah = sqrt(2.0 / height);

			double tmp = 0.0;
			for (int y = 0; y < height; y++) {
				tmp += dctx[w + y * width] * cos((2 * y + 1) * h * PI / (2.0 * height));
			}
			dctxy[w + h * width] = ah * tmp;
		}
	}

	double max = -1;
	for (int i = 0; i < width * height; i++) {
		double val = log(1 + abs(dctxy[i]));
		if (val > max)
			max = val;
	}

	for (int i = 0; i < width * height; i++) {
		double val = log(1 + abs(dctxy[i])) * 255.0 / max;
		if (val > 255)
			val = 255;
		out[i] = (uchar)val;
	}

	return out;
}

FT_MY BLPF(uchar* img, int width, int height, int D0, int n) {
	FT_MY FT;
	complex<double>* img_DFT = DFT(img, width, height);
	complex<double>* img_BLPF = new complex<double>[width * height];
	double D;
	double H;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			D = sqrt(pow(x - width / 2.0, 2) + pow(y - height / 2.0, 2));
			H = 1.0 / (1.0 + pow(D / D0, 2 * n));
			img_BLPF[x + y * width] = img_DFT[x + y * width] * H;
		}
	}

	FT.magnitude_spectrum = get_magnitude_spectrum(img_BLPF, width, height);
	FT.out_idft = IDFT(img_BLPF, width, height);

	return FT;
}

FT_MY BHPF(uchar* img, int width, int height, int D0, int n) {
	FT_MY FT;
	complex<double>* img_DFT = DFT(img, width, height);
	complex<double>* img_BHPF = new complex<double>[width * height];
	double D;
	double H;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			D = sqrt(pow(x - width / 2.0, 2) + pow(y - height / 2.0, 2));
			H = 1.0 / (1.0 + pow(D0 / D, 2 * n));
			img_BHPF[x + y * width] = img_DFT[x + y * width] * H;
		}
	}

	FT.magnitude_spectrum = get_magnitude_spectrum(img_BHPF, width, height);
	FT.out_idft = IDFT(img_BHPF, width, height);

	return FT;
}

FT_MY HFE(uchar* img, int width, int height, int D0, int n, double a, double b) {
	FT_MY FT;
	complex<double>* img_DFT = DFT(img, width, height);
	complex<double>* img_HFE = new complex<double>[width * height];
	double D;
	double H;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			D = sqrt(pow(x - width / 2.0, 2) + pow(y - height / 2.0, 2));
			H = 1.0 / (1.0 + pow(D / D0, 2 * n));
			img_HFE[x + y * width] = img_DFT[x + y * width] * (a + b * (1 - H));
		}
	}

	FT.magnitude_spectrum = get_magnitude_spectrum(img_HFE, width, height);
	FT.out_idft = IDFT(img_HFE, width, height);

	return FT;
}

FT_MY watermark_i(uchar* img, uchar* watermark, int width, int height, double w) {
	FT_MY FT;
	complex<double>* img_DFT = DFT(img, width, height);
	complex<double>* out = new complex<double>[width * height];

	for (int i = 0; i < width * height; i++) {
		out[i] = img_DFT[i] + w * (double)watermark[i];
	}

	FT.magnitude_spectrum = get_magnitude_spectrum(out, width, height);
	FT.out_idft = IDFT(out, width, height);

	return FT;
}

FT_MY watermark_ii(uchar* img, uchar* watermark, int width, int height, double w) {
	FT_MY FT;
	complex<double>* img_DFT = DFT(img, width, height);
	complex<double>* watermark_DFT = DFT(watermark, width, height);
	complex<double>* out = new complex<double>[width * height];

	for (int i = 0; i < width * height; i++) {
		out[i] = img_DFT[i] + w * watermark_DFT[i];
	}

	FT.magnitude_spectrum = get_magnitude_spectrum(out, width, height);
	FT.out_idft = IDFT(out, width, height);

	return FT;
}

uchar* homomorphic(uchar* img, int width, int height, double rH, double rL, double c, double D0) {
	// nature log
	double* img_ln = new double[width * height];;
	for (int i = 0; i < width * height; i++) {
		img_ln[i] = log((double)img[i] + 1.0);
	}

	// DFT
	double* fourier_series_real = new double[width * height];
	double* fourier_series_imag = new double[width * height];
	complex<double>* fourier_series = new complex<double>[width * height];
	double real, imag, theta, D, H;

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			real = 0;
			imag = 0;
			for (int x = 0; x < width; x++) {
				double I = img_ln[x + h * width];
				theta = 2.0 * PI * (double)w * (double)x / (double)width;
				real += I * cos(theta) * pow(-1, x);
				imag += I * -sin(theta) * pow(-1, x);
			}
			fourier_series_real[w + h * width] = real;
			fourier_series_imag[w + h * width] = imag;
		}
	}

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			real = 0;
			imag = 0;
			for (int y = 0; y < height; y++) {
				theta = 2.0 * PI * (double)h * (double)y / (double)height;
				real += (fourier_series_real[w + y * width] * cos(theta) + fourier_series_imag[w + y * width] * sin(theta)) * pow(-1, y);
				imag += (fourier_series_imag[w + y * width] * cos(theta) - fourier_series_real[w + y * width] * sin(theta)) * pow(-1, y);
			}
			// DFT * H(u, v)
			D = sqrt(pow(w - width / 2.0, 2) + pow(h - height / 2.0, 2));
			H = (rH - rL) * (1 - exp(-c * (pow(D, 2) / (2 * pow(D0, 2))))) + rL;
			fourier_series[w + h * width] = complex<double>(real, imag) * H;
		}
	}

	// IDFT
	complex<double>* fs_idft = new complex<double>[width * height];

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double real = 0;
			double imag = 0;
			for (int w = 0; w < width; w++) {
				complex<double> fs_dft = fourier_series[w + y * width];
				double theta = 2.0 * PI * (double)w * (double)x / (double)width;
				real += (fs_dft.real() * cos(theta) - fs_dft.imag() * sin(theta));
				imag += (fs_dft.imag() * cos(theta) + fs_dft.real() * sin(theta));
			}
			fourier_series_real[x + y * width] = real;
			fourier_series_imag[x + y * width] = imag;
		}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double real = 0;
			double imag = 0;
			for (int h = 0; h < height; h++) {
				double fs_real = fourier_series_real[x + h * width];
				double fs_imag = fourier_series_imag[x + h * width];
				double theta = 2.0 * PI * (double)h * (double)y / (double)height;
				real += (fs_real * cos(theta) - fs_imag * sin(theta));
				imag += (fs_imag * cos(theta) + fs_real * sin(theta));
			}
			fs_idft[x + y * width] = complex<double>(real, imag);
		}
	}

	// find max
	double max = -1;

	for (int i = 0; i < width * height; i++) {
		double val = sqrt(pow(fs_idft[i].real(), 2) + pow(fs_idft[i].imag(), 2));
		if (val > max)
			max = val;
	}

	// exp(IDFT / max)
	uchar* out = new uchar[width * height];
	double* fs_exp = new double[width * height];

	double k = 1;
	for (int i = 0; i < width * height; i++) {
		double val1 = sqrt(pow(fs_idft[i].real(), 2) + pow(fs_idft[i].imag(), 2));
		double val2 = exp(val1 / max * k);
		fs_exp[i] = val2;
	}

	max = -1;
	for (int i = 0; i < width * height; i++) {
		double val = fs_exp[i];
		if (val > max)
			max = val;
	}

	for (int i = 0; i < width * height; i++) {
		double val = fs_exp[i] / max * 255.0;
		if (val > 255) val = 255;
		out[i] = (uchar)val;
	}

	return out;
}

/*------------------------------------------------------------------------------hw6------------------------------------------------------------------------------*/
uchar* get_dilation(uchar* img, int width, int height, int kernel_type, int iterations) {
	uchar* out = new uchar[width * height];
	uchar* tmp = new uchar[width * height];

	// clone img
	for (int i = 0; i < width * height; i++) {
		out[i] = img[i];
	}

	// dilate
	for (int _ = 0; _ < iterations; _++) {
		// clone img
		for (int i = 0; i < width * height; i++) {
			tmp[i] = out[i];
		}
		
		// kernel_type == 1
		// 255  0  255
		//  0   0   0 
		// 255  0  255 
		if (kernel_type == 1) {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					// check left pixel
					if ((x > 0) && (tmp[x - 1 + y * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
					// check up pixel
					if ((y > 0) && (tmp[x + (y - 1) * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
					// check right pixel
					if ((x < width - 1) && (tmp[x + 1 + y * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
					// check botton pixel
					if ((y < height - 1) && (tmp[x + (y + 1) * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
				}
			}
		}
		// kernel_type == 2
		// 255 255 255
		//  0   0  255
		// 255 255 255 
		if (kernel_type == 2) {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					// check left pixel
					if ((x > 0) && (tmp[x - 1 + y * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
				}
			}
		}
		// kernel_type == 3
		// 255 255 255
		//  0   0   0 
		// 255  0  255
		if (kernel_type == 3) {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					// check left pixel
					if ((x > 0) && (tmp[x - 1 + y * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
					// check right pixel
					if ((x < width - 1) && (tmp[x + 1 + y * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
					// check botton pixel
					if ((y < height - 1) && (tmp[x + (y + 1) * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
				}
			}
		}
		// kernel_type == 4
		// 255 255  0 
		//  0   0   0 
		// 255  0  255
		if (kernel_type == 4) {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					// check top-right pixel
					if ((x < width - 1) && (y > 0) && (tmp[x + 1 + (y - 1) * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
					// check left pixel
					if ((x > 0) && (tmp[x - 1 + y * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
					// check right pixel
					if ((x < width - 1) && (tmp[x + 1 + y * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
					// check botton pixel
					if ((y < height - 1) && (tmp[x + (y + 1) * width] == 0)) {
						out[x + y * width] = 0;
						continue;
					}
				}
			}
		}
	}
	return out;
}

uchar* get_erosion(uchar* img, int width, int height, int kernel_type, int iterations) {
	uchar* out = new uchar[width * height];
	uchar* tmp = new uchar[width * height];

	// clone img
	for (int i = 0; i < width * height; i++)
		out[i] = img[i];

	// erode
	for (int _ = 0; _ < iterations; _++) {
		// clone img
		for (int i = 0; i < width * height; i++)
			tmp[i] = out[i];

		// kernel_type == 1
		// 255  0  255
		//  0   0   0 
		// 255  0  255 
		if (kernel_type == 1) {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					// check left pixel
					if ((x > 0) && (tmp[x - 1 + y * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
					// check up pixel
					if ((y > 0) && (tmp[x + (y - 1) * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
					// check right pixel
					if ((x < width - 1) && (tmp[x + 1 + y * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
					// check botton pixel
					if ((y < height - 1) && (tmp[x + (y + 1) * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
				}
			}
		}
		// kernel_type == 2
		// 255 255 255
		//  0   0  255
		// 255 255 255 
		if (kernel_type == 2) {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					// check left pixel
					if ((x > 0) && (tmp[x - 1 + y * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
				}
			}
		}
		// kernel_type == 3
		// 255 255 255
		//  0   0   0 
		// 255  0  255
		if (kernel_type == 3) {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					// check left pixel
					if ((x > 0) && (tmp[x - 1 + y * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
					// check right pixel
					if ((x < width - 1) && (tmp[x + 1 + y * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
					// check botton pixel
					if ((y < height - 1) && (tmp[x + (y + 1) * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
				}
			}
		}
		// kernel_type == 4
		// 255 255  0 
		//  0   0   0 
		// 255  0  255
		if (kernel_type == 4) {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					// check top-right pixel
					if ((x < width - 1) && (y > 0) && (tmp[x + 1 + (y - 1) * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
					// check left pixel
					if ((x > 0) && (tmp[x - 1 + y * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
					// check right pixel
					if ((x < width - 1) && (tmp[x + 1 + y * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
					// check botton pixel
					if ((y < height - 1) && (tmp[x + (y + 1) * width] == 255)) {
						out[x + y * width] = 255;
						continue;
					}
				}
			}
		}
	}
	return out;
}

uchar* get_open(uchar* img, int width, int height, int kernel_type) {
	return get_erosion(get_dilation(img, width, height, kernel_type, 1), width, height, kernel_type, 1);
}

uchar* get_close(uchar* img, int width, int height, int kernel_type) {
	return get_dilation(get_erosion(img, width, height, kernel_type, 1), width, height, kernel_type, 1);
}

uchar* erode_SE_5x5(uchar* img, int width, int height) {
	int kernel_size = 5;
	int pad = floor(kernel_size / 2);
	uchar* img_padding = replication_padding(img, width, height, pad);
	int NEW_WIDTH = width + 2 * pad;
	int NEW_HEIGHT = height + 2 * pad;
	uchar* out = new uchar[width * width];
	double kernel[5][5] = {
		{0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0}
	};
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			vector<uchar> vs{};
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					if (kernel[dy + pad][dx + pad] == 1) {
						vs.push_back(img_padding[x + dx + (y + dy) * NEW_WIDTH]);
					}
				}
			}

			sort(vs.begin(), vs.end());
			out[x - pad + (y - pad) * width] = vs[16];
		}
	}
	return out;
}

uchar* dilate_SE_5x5(uchar* img, int width, int height) {
	int kernel_size = 5;
	int pad = floor(kernel_size / 2);
	uchar* img_padding = replication_padding(img, width, height, pad);
	int NEW_WIDTH = width + 2 * pad;
	int NEW_HEIGHT = height + 2 * pad;
	uchar* out = new uchar[width * width];
	double kernel[5][5] = {
		{0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0}
	};
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			vector<uchar> vs{};
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					if (kernel[dy + pad][dx + pad] == 1) {
						vs.push_back(img_padding[x + dx + (y + dy) * NEW_WIDTH]);
					}
				}
			}

			sort(vs.begin(), vs.end());
			out[x - pad + (y - pad) * width] = vs[0];
		}
	}
	return out;
}

uchar* open_SE_5x5(uchar* img, int width, int height) {
	return erode_SE_5x5(dilate_SE_5x5(img, width, height), width, height);
}

uchar* close_SE_5x5(uchar* img, int width, int height) {
	return dilate_SE_5x5(erode_SE_5x5(img, width, height), width, height);
}

uchar* erode_SE_5x5_90(uchar* img, int width, int height) {
	int kernel_size = 5;
	int pad = floor(kernel_size / 2);
	uchar* img_padding = replication_padding(img, width, height, pad);
	int NEW_WIDTH = width + 2 * pad;
	int NEW_HEIGHT = height + 2 * pad;
	uchar* out = new uchar[width * width];
	double kernel[5][5] = {
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{1, 1, 1, 1, 1},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0}
	};
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			vector<uchar> vs{};
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					if (kernel[dy + pad][dx + pad] == 1) {
						vs.push_back(img_padding[x + dx + (y + dy) * NEW_WIDTH]);
					}
				}
			}

			sort(vs.begin(), vs.end());
			out[x - pad + (y - pad) * width] = vs[16];
		}
	}
	return out;
}

uchar* dilate_SE_5x5_90(uchar* img, int width, int height) {
	int kernel_size = 5;
	int pad = floor(kernel_size / 2);
	uchar* img_padding = replication_padding(img, width, height, pad);
	int NEW_WIDTH = width + 2 * pad;
	int NEW_HEIGHT = height + 2 * pad;
	uchar* out = new uchar[width * width];
	double kernel[5][5] = {
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{1, 1, 1, 1, 1},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0}
	};
	for (int y = pad; y < NEW_HEIGHT + pad; y++) {
		for (int x = pad; x < NEW_WIDTH + pad; x++) {
			vector<uchar> vs{};
			for (int dy = -pad; dy < pad + 1; dy++) {
				for (int dx = -pad; dx < pad + 1; dx++) {
					if (kernel[dy + pad][dx + pad] == 1) {
						vs.push_back(img_padding[x + dx + (y + dy) * NEW_WIDTH]);
					}
				}
			}

			sort(vs.begin(), vs.end());
			out[x - pad + (y - pad) * width] = vs[0];
		}
	}
	return out;
}

uchar* thin(uchar* img, int width, int height) {
	uchar* out = new uchar[width * width];

	for (int i = 0; i < width * height; i++)
		out[i] = img[i];

	int kernel0[3][3] = {
		{0, 0, 0},
		{-1, 255, -1},
		{255, 255, 255}
	};
	int kernel1[3][3] = {
		{-1, 0, 0},
		{255, 255, 0},
		{255, 255, -1}
	};
	int kernel2[3][3] = {
		{255, -1, 0},
		{255, 255, 0},
		{255, -1, 0}
	};
	int kernel3[3][3] = {
		{255, 255, -1},
		{255, 255, 0},
		{-1, 0, 0}
	};
	int kernel4[3][3] = {
		{255, 255, 255},
		{-1, 255, -1},
		{0, 0, 0}
	};
	int kernel5[3][3] = {
		{-1, 255, 255},
		{0, 255, 255},
		{0, 0, -1}
	};
	int kernel6[3][3] = {
		{0, -1, 255},
		{0, 255, 255},
		{0, -1, 255}
	};
	int kernel7[3][3] = {
		{0, 0, -1},
		{0, 255, 255},
		{-1, 255, 255}
	};

	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {
			int count = 0;
			for (int dy = -1; dy < 2; dy++) {
				for (int dx = -1; dx < 2; dx++) {
					if (img[x + dx + (y + dy) * width] == kernel0[dy + 1][dx + 1])
						count++;
				}
			}
			if (count == 7)
				out[x + y * width] = 0;
		}
	}

	for (int i = 1; i < 8; i++) {
		for (int y = 1; y < height - 1; y++) {
			for (int x = 1; x < width - 1; x++) {
				int count = 0;
				for (int dy = -1; dy < 2; dy++) {
					for (int dx = -1; dx < 2; dx++) {
						if (i == 1 && out[x + dx + (y + dy) * width] == kernel1[dy + 1][dx + 1])
							count++;
						else if (i == 2 && out[x + dx + (y + dy) * width] == kernel2[dy + 1][dx + 1])
							count++;
						else if (i == 3 && out[x + dx + (y + dy) * width] == kernel3[dy + 1][dx + 1])
							count++;
						else if (i == 4 && out[x + dx + (y + dy) * width] == kernel4[dy + 1][dx + 1])
							count++;
						else if (i == 5 && out[x + dx + (y + dy) * width] == kernel5[dy + 1][dx + 1])
							count++;
						else if (i == 6 && out[x + dx + (y + dy) * width] == kernel6[dy + 1][dx + 1])
							count++;
						else if (i == 7 && out[x + dx + (y + dy) * width] == kernel7[dy + 1][dx + 1])
							count++;
					}
				}
				if (count == 7)
					out[x + y * width] = 0;
			}
		}
	}
	return out;
}