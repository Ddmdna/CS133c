//pointerFun.c
#include <stdio.h>

int main()
{
	//Exercise Component 1:
	pointerFunction();
	return 0;
}

//1
int pointerFunction()
{
	//1.1
	char var_name = 'G';
	printf("var_name is a char with the value: %c, and has the address: %p\n", var_name, &var_name);
	
	//1.2
	char* pointer_var;
	pointer_var = &var_name;
	printf("pointer_var is a char* with the value: %p, at address: %p\n\n", pointer_var, &pointer_var);
	
	//1.3
	printf("Enter a char value for var_name\n");
	*pointer_var = getchar();
	
	//Extra to see result
	printf("var_name = %c\n", var_name);

	return 0;
}