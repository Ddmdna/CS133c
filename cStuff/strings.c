// strings.c
#include <stdio.h>
int main()
{
	int const MAX = 100;
	char myStr[MAX];
	int letterCount = 0;
	
	printf("Enter a string.\n");
	fgets(myStr, MAX, stdin);
	
	int i = 0;
	printf("\nPrinting your string forwards.\n");
	while(i < MAX && myStr[i+1] != '\0')
	{
		if( (myStr[i] >= 'a' && myStr[i] <= 'z') || (myStr[i] >= 'A' && myStr[i] <= 'Z') ) letterCount++;
		printf("%c\n", myStr[i]);
		i++;
	}
	
	printf("\nPrinting your string backwards.");
	while(i >= 0)
	{
		printf("%c\n", myStr[i]);
		i--;
	}
	printf("\n%d letters in your string.", letterCount);

	return 0;
}