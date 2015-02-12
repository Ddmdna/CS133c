/*

	(5) Write a function that accepts two strings and returns an int (0 for false, 1 for true) showing
	whether they have the same contents with the use of a loop to check each character
	individually. 
	
	Your function signature will likely look like this: 
		int equals(char *str1, int len1, char *str2, int len2)

	File must be called: retFun.c

	(hint: you can compare individual characters with the <, ==, and > operators)

	hint: reusing code you have written may be a good idea... 
	
	Discussion Idea: Are there any challenges or easy mistakes you could make through code reuse?

*/
// retFun.c
#include <stdio.h>

int getLength(char *str);
int equals(char *str1, int len1, char *str2, int len2);
void clearBuffer();


const int MAX = 100;

int main()
{
	//Create attributes to be used in equals()
	char input1[MAX];
	int size1;
	char input2[MAX];
	int size2;
	
	int isEqual;
	
	//Get input and compare strings
	char repeat = 'y';
	while(repeat == 'y' || repeat == 'Y'){
		//Into
		printf("\nEnter two strings and test for equality.\n\n");
		
		//Assume the strings are going to be equal.
		isEqual = 1;
		
		//Get user input
		printf("Enter the first string.\n");
		fgets(input1, MAX, stdin );
		printf("\n\nEnter the second string.\n");
		fgets(input2, MAX, stdin );
		
		//Determine length of each input
		size1 = getLength(input1);
		size2 = getLength(input2);
		
		//Test to see if they are equal
		isEqual = equals(input1, size1, input2, size2);
		
		//Output results of equals
		if(isEqual) printf("\nThe strings are equal.\n");
		else  printf("\nThe strings are not equal.\n");
		
		//Show the contents of each string
		int i = 0;
		printf("Index	Str1[]	Str2[]\n");
		while( (i<size1) || (i<size2) ){
			printf("%3d     ", i);
			
			if(i<size1) 
				printf("  %c  ", input1[i]);
			else 
				printf("     ");
			
			if(i<size2) 
				printf("     %c  ", input2[i]);
			
			printf("\n");
			i++;
		}
		
		//Ask user if they would like to repeat the program
		printf("\nWould you like to try again?(y/n)\n");
		
		//Get user input
		repeat = getchar();
		
		//Clear buffer stream
		while (getchar() != '\n');

		
	}
	
	return 0;
}

//This function requires pre handled strings
//basically strings that end with '\n'
//returns 1 for equal and 0 for unequal
int equals(char *str1, int len1, char *str2, int len2){
	int result = 1;
	if(len1 != len2) 
		result = 0;
	
	int i = 0;
	while( result && (i < len1) ){
		if(str1[i] == str2[i]) 
			i++;
		else
			result = 0;
	}
	return result;
}

//This function determine how many characters are in a 
//char array before a '\n' is found
int getLength(char *str){
	int length = 0;
	char ch;
	while(str[length] != '\n') length++;
	return length;
}
