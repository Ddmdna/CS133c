// randNum.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//If you run this program more then once within a second, time(NULL) will produce the same output
//If you want to run this program more than once within a second, I suggest wrapping it within a
//a separate program that performs srand(time(NULL))
// I could always copy the source code from the Mersenne Twister random number generator
int main()
{
	srand(time(NULL));
	int randVal;
	int i = 0;
	while(i<11){
		randVal = rand() % 100;
		printf("%d\n", randVal);
		i++;
	}
	
	return 0;
}