// recFun.c
#include <stdio.h>
int fibbo(int n);

int main()
{
	int i = 0;
	while(i < 25){
		printf("%2d: %5d\n", i, fibbo(i));
		i++;
	}
	
	getchar();
	return 0;
}

//Here's the function, tested above
int fibbo(int n){
	if(n == 0 || n == 1) return 1;
	else return (fibbo(n-1) + fibbo(n-2));
}