#include "Header.h"

int main() {
	while (1) {
		printf("0: Exit\n");
		printf("1: 1 answer\n");
		printf("2: 2_1 answer\n");
		printf("3: 2_2 answer\n");
		printf("4: 2_3 answer\n");
		printf("5: 3 answer\n");
		printf("6: 4 answer\n");
		printf("Enter the question number to select output result: ");

		int num;
		int stop = 0;
		scanf("%d", &num);
		printf("-------------------------------result----------------------------------\n");

		switch (num) {
		case 0:
			stop = 1;
			printf("<<Exit>>\n");
			printf("-----------------------------------------------------------------------\n");
			break;
		case 1:
			hw2_1();
			printf("-----------------------------------------------------------------------\n");
			break;
		case 2:
			hw2_2_1();
			printf("-----------------------------------------------------------------------\n");
			break;
		case 3:
			hw2_2_2();
			printf("-----------------------------------------------------------------------\n");
			break;
		case 4:
			hw2_2_3();
			printf("-----------------------------------------------------------------------\n");
			break;
		case 5:
			hw2_3();
			printf("-----------------------------------------------------------------------\n");
			break;
		case 6:
			hw2_4();
			printf("-----------------------------------------------------------------------\n");
			break;
		default:
			printf("<<Please enter number 0~6!!>>\n");
			printf("-----------------------------------------------------------------------\n");
			break;
		}
		if (stop == 1)break;
	}
}