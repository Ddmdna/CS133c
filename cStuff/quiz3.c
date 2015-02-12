//quiz3.c
#include <stdio.h>
int main(void)
{
	char ch;
	int lc = 0; // lowercase char count 
	int uc = 0; // uppercase char count
	int oc = 0; // other char count
 
	printf("\nEnter a character or string:\n(Enter '#' to end)\n");
	while ((ch = getchar()) != '#')
	{
    	if ( ('a' <= ch) && (ch <= 'z') )  lc++;
    	else{ if (!(ch < 'A') && !(ch > 'Z')) uc++;
				else oc++;
		}
		if(ch == '\n') oc--;
	}

	printf("%d lowercase, %d uppercase, %d other", lc, uc, oc);
	return 0;
}
