#include <stdio.h>
#include <math.h>

#define MY_PI 3.1415

int main () {
	int x;
	printf ("uint16_t angleLookup[5000] = {\n");
	for (x=-2500; x<2500; x++) {
		if (x%10 == 0)
			printf ("\n");
		printf ("%d, ", (int)(32768*sin(2*MY_PI*x/10000)));
	}
	x=2500;
	printf ("\n%d};", (int)(32768*sin(2*MY_PI*x/10000)));
return 0;
}
