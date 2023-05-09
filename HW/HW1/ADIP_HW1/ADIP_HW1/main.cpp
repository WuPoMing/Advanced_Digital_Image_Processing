#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "Header.h"

int main() {
	while (1) {
		printf("0:Exit\n");
		printf("1:1.2_a answer\n");
		printf("2:1.2_b answer\n");
		printf("3:1.2_c answer\n");
		printf("4:1.2_d answer\n");
		printf("5:1.2_e answer\n");
		printf("6:1.3_a answer\n");
		printf("7:1.3_b answer\n");
		printf("8:2_b answer\n");
		printf("Enter the question number to select output result¡G");

		int num;
		int stop = 0;
		scanf("%d", &num);

		switch (num) {
			case 0:
				stop = 1;
				printf("Exit!\n");
				break;
			case 1:
				hw1_1_2a();
				break;
			case 2:
				hw1_1_2b();
				break;
			case 3:
				hw1_1_2c();
				break;
			case 4:
				hw1_1_2d_horizontal();
				hw1_1_2d_vertical();
				break;
			case 5:
				hw1_1_2e();
				break;
			case 6:
				hw1_1_3a();
				break;
			case 7:
				hw1_1_3b();
				break;
			case 8:
				hw1_2b();
				break;
			default:
				printf("Please enter number 0~8!!\n");
				break;
		}
		if (stop == 1)break;
	}
}