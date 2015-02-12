// equals.c
#include <stdio.h>
int main()
{
	int isEqual = 1;
	int const MAX = 100;
	char myStrA[MAX];
	char myStrB[MAX];
	
	printf("Enter a string.\n");
	fgets(myStrA, MAX, stdin);
	
	printf("\nEnter another string.\n");
	fgets(myStrB, MAX, stdin);
	
	int i = 0;
	while(isEqual && (myStrA[i] != '\0' && myStrB[i] != '\0') ){
		if(myStrA[i] != myStrB[i]) isEqual = 0;
		i++;
	}
	if(isEqual) printf("\n\nThe strings are equal.");
	else printf("\n\nThe strings are unequal.");
	
	return 0;
}