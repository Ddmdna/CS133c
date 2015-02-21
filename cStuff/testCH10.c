#include <stdio.h>

int main(){

	char arr2[6] = {'A'};
	char arr3[6] = {[5] = 'A'};

	
	int i;
	for(i = 0; i< (sizeof arr2 / sizeof arr2[0]); i++){

		printf("arr2[%d] = %c\n", i, arr2[i]);
		printf("arr3[%d] = %c\n", i, arr3[i]);

	}
}