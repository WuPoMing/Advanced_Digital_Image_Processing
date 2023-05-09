#include "Header.h"

int main() {
	while (1) {
		printf("0: Exit\n");
		printf("1:  1.		answer\n");
		printf("2:  2.(1)	answer\n");
		printf("3:  2.(2)	answer\n");
		printf("4:  3.		answer\n");
		printf("5:  4.		answer\n");
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
			hw6_1();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 2:
			hw6_2_1();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 3:
			hw6_2_2();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 4:
			hw6_3();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 5:
			hw6_4();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		default:
			printf("<<Please enter number 0~5!!>>\n");
			printf("-----------------------------------------------------------------------\n\n");
			break;
		}
		if (stop == 1)break;
	}
}