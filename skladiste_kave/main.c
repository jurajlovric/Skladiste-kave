#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
	int opcija = 1;

	while (opcija != 101) {
		opcija = izbornik();
	}
	return 0;
}