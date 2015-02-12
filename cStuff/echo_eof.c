/* echo_eof.c -- repeats input to end of file */
#include <stdio.h>
int main(void)
{
	int ch;
	int i = 0;
	
	while(i < 1000000){
		i++;
		printf("I: %d", i);
	}
	
	while ((ch = getchar()) != EOF)
	putchar(ch);
	return 0;
}