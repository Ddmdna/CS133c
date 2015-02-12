#include <stdio.h>

int main(int argc, char const *argv[])
{
	int x = 0;
	int y = 0;
	printf("%d\n", (x = (2 + 3) * 6));

	printf("%d\n", (x = (12 + 6)/2*3));

	printf("%d\n", (y = x = (2 + 3)/4));

	printf("%d\n", y = 3 + 2*(x = 7/2));

	printf("%d\n", x = (int) 3.8 + 3.3);

	printf("%d\n", x = (2 + 3) * 10.5);

	printf("%d\n", x = 3 / 5 * 22.0);

	printf("%d\n", x = 22.0 * 3 / 5);


	return 0;
}