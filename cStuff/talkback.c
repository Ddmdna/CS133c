// talkback.c -- nosy, informative program
#include <stdio.h>
#include <string.h> // for strlen() prototype
#define DENSITY 62.4 // human density in lbs per cu ft
int main()
{
	//char name[5]; // name is an array of 5 chars
	//printf("Hi! What's your first name?\n");
	//scanf("%s", name);
	//Show the address for each spot
	//Show the char stored in each spot
	printf("\nWe will analyse the string!\n");
	int i = 0;
	char *ptr = 2665479;
	for(i = 0; i<=100; i++){
		printf("\n%#3d: is: %c, at %d", i, *ptr, ptr);
		ptr++;
	}
	return 0;
}