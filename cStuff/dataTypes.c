/*
 * dataTypes.c
 *
 *  Created on: Jan 9, 2015
 *      Author: Ddmdna
 */
#include <stdio.h>

char myChar = 255;
int myInt = 2147483647;
short myShort = 32767;
long myLong = 1000;
unsigned myUnsigned = 10;
signed mySigned = -10;
float myFloat = 0.000001;
double myDouble = 100000.000001;

int main(int argc, char *argv[])
{
	printf("The value of myChar is: %c\n", myChar);
	printf("The value of myInt is: %d\n", myInt);
	printf("The value of myShort is: %d\n", myShort);
	printf("The value of myLong is: %ld\n", myLong);
	printf("The value of myUnsigned is: %u\n", myUnsigned);
	printf("The value of mySigned is: %d\n", mySigned);
	printf("The value of myFloat is: %f\n", myFloat);
	printf("The value of myDouble is: %f", myDouble);

	return 0;
}
