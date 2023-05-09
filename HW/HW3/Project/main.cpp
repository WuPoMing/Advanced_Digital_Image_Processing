#include "Header.h"

int main() {
	while (1) {
		printf("0: Exit\n");
		printf("1: 1. answer\n");
		printf("2: 2.(1) answer\n");
		printf("3: 2.(2) answer\n");
		printf("4: 3.(1) answer\n");
		printf("5: 3.(2) answer\n");
		printf("6: 3.(3) answer\n");
		printf("Enter the question number to select output result: ");

		int num;
		int stop = 0;
		scanf("%d", &num);
		printf("-------------------------------result----------------------------------\n\n");

		switch (num) {
		case 0:
			stop = 1;
			printf("<<Exit>>\n");
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 1:
			hw3_1();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 2:
			hw3_2_1();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 3:
			hw3_2_2();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 4:
			hw3_3_1();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 5:
			hw3_3_2();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 6:
			hw3_3_3();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		default:
			printf("<<Please enter number 0~6!!>>\n");
			printf("-----------------------------------------------------------------------\n\n");
			break;
		}
		if (stop == 1)break;
	}
}