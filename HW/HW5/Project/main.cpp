#include "Header.h"

int main() {
	while (1) {
		printf("0: Exit\n");
		printf("1:  1.(1) & 1.(3) answer\n");
		printf("2:  1.(2) & 1.(4) answer\n");
		printf("3:  1.(5)         answer\n");
		printf("4:  2.(1)         answer\n");
		printf("5:  2.(2)         answer\n");
		printf("6:  3.(1)         answer\n");
		printf("7:  3.(2)         answer\n");
		printf("8:  4.            answer\n");
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
			hw5_1_1and3();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 2:
			hw5_1_2and4();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 3:
			hw5_1_5();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 4:
			hw5_2_1();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 5:
			hw5_2_2();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 6:
			hw5_3_1();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 7:
			hw5_3_2();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 8:
			hw5_4();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		default:
			printf("<<Please enter number 0~8!!>>\n");
			printf("-----------------------------------------------------------------------\n\n");
			break;
		}
		if (stop == 1)break;
	}
}