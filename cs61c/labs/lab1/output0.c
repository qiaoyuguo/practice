#include <stdio.h>

int main(void) {
	int n;
	n = 48; // fix 1: only change this line
	printf("fix 1: %c\n",n);

	n = 0; 
	printf("fix 2: %c\n", '0'+n); // fix 2: only change this line

	return 0;
}
