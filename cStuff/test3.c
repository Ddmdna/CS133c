// test3.c
#include <stdio.h>

int get_int(void);

int main()
{
	int num;

	num = get_int();
	printf("Input: %d\n", num);
	
	
	return 0;
}


int get_int(void)
{
	int input;
	char ch;
	while (scanf("%d", &input) != 1)
	{
		while ((ch = getchar()) != '\n')
		{
			putchar(ch); // dispose of bad input
		}
		printf(" is not an integer.\nPlease enter an ");
		printf("integer value, such as 25, -178, or 3: ");
	}
	return input;
}