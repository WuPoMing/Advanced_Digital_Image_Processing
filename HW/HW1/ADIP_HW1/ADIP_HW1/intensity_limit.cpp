#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include "Header.h"

unsigned char intensity_limit(unsigned char intensity, int fix) {
	int x = intensity + fix;
	if (x > 255) {
		x = 255;
	}
	if (x < 0) {
		x = 0;
	}
	return x;
}