#include "Header.h"
#define WIDTH 100
#define HEIGHT 100

const int INF = 1000000;
typedef pair<int, int > P;

Mat draw_D4_search_path(Mat img, int x, int y, int s, int t) {
	int width = img.cols;
	int height = img.rows;
	int d[WIDTH][HEIGHT];
	int dx[4] = { 1,0,-1,0 };	// �k �U �� �W
	int dy[4] = { 0,1,0,-1 };
	queue<P> que;

	// ��l�ƩҦ��I���Z����INF 
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			d[x][y] = INF;
		}
	}

	// ��_�I�[�J��C�A�ó]�Z���� 0 
	que.push(P(x, y));
	d[x][y] = 0;

	while (que.size()) {
		P p = que.front();
		que.pop();
		if (p.first == s && p.second == t) break;	// �p�G���X�����A�O���I�A�h�j�M����
		
		for (int i = 0; i < 4; i++) {
			int nx = p.first + dx[i];
			int ny = p.second + dy[i];

			if (0 <= nx && nx < width && 0 <= ny && ny < height && img.at<uchar>(Point(nx, ny)) == 0 && d[nx][ny] == INF) {
				que.push(P(nx, ny));
				d[nx][ny] = d[p.first][p.second] + 1;
			}
		}
	}
	printf("The shortest distance using D4: %d\n", d[s][t]);	// ��ܱq��l�I������I���̵u�B��

	Mat out(height, width, CV_8UC1);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			out.at<uchar>(Point(x, y)) = img.at<uchar>(Point(x, y));
			if (d[x][y] != INF) out.at<uchar>(Point(x, y)) = d[x][y];
		}
	}
	return out;
}

Mat draw_D8_search_path(Mat img, int x, int y, int s, int t) {
	int width = img.cols;
	int height = img.rows;
	int d[WIDTH][HEIGHT];
	int dx[8] = { -1, 1, 1, -1, 1, 0, -1, 0 };	// ���W �k�W �k�U ���U �k �U �� �W
	int dy[8] = { -1, -1, 1, 1, 0 , 1, 0, -1 };
	queue<P> que;

	// ��l�ƩҦ��I���Z����INF 
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			d[x][y] = INF;
		}
	}

	// ��_�I�[�J��C�A�ó]�Z���� 0 
	que.push(P(x, y));
	d[x][y] = 0;

	while (que.size()) {
		P p = que.front();
		que.pop();
		if (p.first == s && p.second == t) break;	// �p�G���X�����A�O���I�A�h�j�M����

		for (int i = 0; i < 8; i++) {
			int nx = p.first + dx[i];
			int ny = p.second + dy[i];

			if (0 <= nx && nx < width && 0 <= ny && ny < height && img.at<uchar>(Point(nx, ny)) == 0 && d[nx][ny] == INF) {
				que.push(P(nx, ny));
				d[nx][ny] = d[p.first][p.second] + 1;
			}
		}
	}
	printf("The shortest distance using D8: %d\n", d[s][t]);	// ��ܱq��l�I������I���̵u�B��

	Mat out(height, width, CV_8UC1);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			out.at<uchar>(Point(x, y)) = img.at<uchar>(Point(x, y));
			if (d[x][y] != INF) out.at<uchar>(Point(x, y)) = d[x][y];
		}
	}
	return out;
}

Mat draw_Dm_search_path(Mat img, int x, int y, int s, int t) {
	int width = img.cols;
	int height = img.rows;
	int d[WIDTH][HEIGHT];
	int dx[8] = { 1, 0, -1, 0, -1, 1, 1, -1 };	// �k �U �� �W ���W �k�W �k�U ���U
	int dy[8] = { 0, 1, 0, -1, -1, -1, 1, 1 };
	queue<P> que;

	// ��l�ƩҦ��I���Z����INF 
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			d[x][y] = INF;
		}
	}

	// ��_�I�[�J��C�A�ó]�Z���� 0 
	que.push(P(x, y));
	d[x][y] = 0;

	while (que.size()) {
		P p = que.front();
		que.pop();
		if (p.first == s && p.second == t) break;	// �p�G���X�����A�O���I�A�h�j�M����

		bool a = false;
		for (int i = 0; i < 4; i++) {
			int nx = p.first + dx[i];
			int ny = p.second + dy[i];

			if (0 <= nx && nx < width && 0 <= ny && ny < height && img.at<uchar>(Point(nx, ny)) == 0 && d[nx][ny] == INF) {
				que.push(P(nx, ny));
				d[nx][ny] = d[p.first][p.second] + 1;
				a = true;
			}
		}
		if (!a) {
			for (int i = 4; i < 8; i++) {
				int nx = p.first + dx[i];
				int ny = p.second + dy[i];

				if (0 <= nx && nx < width && 0 <= ny && ny < height && img.at<uchar>(Point(nx, ny)) == 0 && d[nx][ny] == INF) {
					que.push(P(nx, ny));
					d[nx][ny] = d[p.first][p.second] + 1;
				}
			}
		}
	}
	printf("The shortest distance using Dm: %d\n", d[s][t]);	// ��ܱq��l�I������I���̵u�B��

	Mat out(height, width, CV_8UC1);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			out.at<uchar>(Point(x, y)) = img.at<uchar>(Point(x, y));
			if (d[x][y] != INF) out.at<uchar>(Point(x, y)) = d[x][y];
		}
	}
	return out;
}

Mat draw_shortest_path(Mat img1, Mat img2, int s, int t) {
	int dx[8] = { 1, 0, -1, 0, -1, 1, 1, -1 };	// �k �U �� �W ���W �k�W �k�U ���U
	int dy[8] = { 0, 1, 0, -1, -1, -1, 1, 1 };

	Mat out(img1.rows, img1.cols, CV_8UC1);
	for (int y = 0; y < img1.rows; y++) {
		for (int x = 0; x < img1.cols; x++) {
			out.at<uchar>(Point(x, y)) = img1.at<uchar>(Point(x, y));
		}
	}

	out.at<uchar>(Point(s, t)) = 200;
	while (1) {
		if (img2.at<uchar>(Point(s, t)) == 0) break;

		for (int i = 0; i < 8; i++) {
			if (img2.at<uchar>(Point(s + dx[i], t + dy[i])) == img2.at<uchar>(Point(s, t)) - 1) {
				out.at<uchar>(Point(s + dx[i], t + dy[i])) = 200;
				s = s + dx[i];
				t = t + dy[i];
				break;
			}
		}
	}
	return out;
}