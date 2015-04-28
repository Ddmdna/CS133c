// dynGrades.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void string_gets(char *str, int max);
int findNextDigit(char *input, int index);
int findNextNonDigit(char *input, int index);
int digit_string_to_int(char *input, int digit_start, int digitLength);
char getDecision(char yes, char no);

int main()
{
	const int MAX_HISTOGRAM_SIZE = 11;
	int *histogram = (int*)malloc(MAX_HISTOGRAM_SIZE * sizeof(int));
	
	const int MAX_INPUT_SIZE = 100;
	char *input = (char*)malloc(MAX_INPUT_SIZE * sizeof(char));
	
	int i;
	
	//Loop while user agrees
	char repeat = 'y';
	while(repeat == 'y' || repeat == 'Y')
	{
		//Initialize input as an empty string
		memset(input, '\0', MAX_INPUT_SIZE);
		
		//Initialize histogram to zero for each value
		for(i = 0; i < MAX_HISTOGRAM_SIZE; i++) histogram[i] = 0;
		
		//Ask for a string of digits between 0 and 10, separated by non digits
		printf("\nEnter a string of integers between 0 and 10, separated by non digits.\n");
		
		//Get input
		string_gets(input, MAX_INPUT_SIZE);
		
		//Output formatted input with info
		printf("\nInput: (%s) length: %d\n\n", input, strlen(input));
		
		//Convert input string to integer histogram array
		int digit_start, digit_end, digitsInSeries, value;
		for(i = 0; i < strlen(input); i = digit_end)
		{
			//Find next digit
			digit_start = findNextDigit(input, i);
			if(digit_start == -1) break; //No more digits in string
			
			//Find next non-digit
			digit_end = findNextNonDigit(input, digit_start);
			
			//Calculate digit
			digitsInSeries = (digit_end - digit_start);
			value = digit_string_to_int(input, digit_start, digitsInSeries);
			
			//Add valid digit
			if(-1 < value && value < 11) histogram[value]++;
		}
		
		//Output histogram
		for(i = 0; i < MAX_HISTOGRAM_SIZE; i++) printf("%2d grade(s) of %2d\n", histogram[i], i);
		
		//Get decision to repeat program
		repeat = getDecision('y', 'n');
	}
	
	//free memory
	free(input);
	free(histogram);
	
	return 0;
}

void string_gets(char *str, int max)
{
	//Get input
	fgets(str, max, stdin);
	
	//Format input
	if(strlen(str) < max && str[strlen(str)-1] == '\n')	//Remove '\n' from short inputs.
		str[strlen(str)-1] = '\0';
	else
		while(getchar() != '\n');						//Clear buffer on long inputs.
}

int findNextDigit(char *input, int index)
{
	while(input[index] != '\0' && isdigit(input[index]) == 0){
		index++;
	}
	if(input[index] == '\0')
		return -1;
	else
		return index;
}

int findNextNonDigit(char *input, int index)
{
	while(input[index] != '\0' && isdigit(input[index]) != 0){
		index++;
	}
	return index;
}

int digit_string_to_int(char *input, int digit_start, int digitLength)
{
	int result = 0;
	int baseTenPower = 1;
	while(digitLength>0) //My use of index between tests might be confusing
	{
		digitLength--;
		result+= (baseTenPower * (input[digit_start + digitLength] - '0'));
		baseTenPower *= 10;
	}
	return result;
}

char getDecision(char yes, char no){
	char result;
	printf("\nWould you like to repeat the program? (%c/%c)\n", yes, no);
	result = getchar();
	while (getchar() != '\n');
	return result;
}