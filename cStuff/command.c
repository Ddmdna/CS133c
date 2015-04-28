// command.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int findNextDigit(char *input, int index);
int findNextNonDigit(char *input, int index);
int digit_string_to_int(char *input, int digit_start, int digitLength);

int main(int argc, char* argv[])
{
	//Test arguments
	if(argc == 1){
		printf("Error in argument count\nUsage: %s <grade_1> <grad_2> ... <grade_n>", argv[0]);
		exit(2);
	}
	
	//Create the histogram array and give it memory
	char space[2] = {' ', '\0'};
	const int MAX_HISTOGRAM_SIZE = 11;
	int *histogram = (int*)malloc(MAX_HISTOGRAM_SIZE * sizeof(int));
	
	//How many total characters in our command line arguments
	int count = 0;
	int i;
	for(i = 1; i < argc; i++ ){
		count += strlen(argv[i]);
	}
	
	//Give input enough memory for all arguments with separating spaces
	char *input = (char*)malloc( (count + argc - 1) * sizeof(char));
	
	//Initialize input as an empty string
	memset(input, '\0', (count + argc - 1));
	
	//Add arguments with separating spaces to input
	for(i = 1; i < argc; i++ ){
		strcat(input, argv[i]);
		strcat(input, space);
	}
	
	//Initialize histogram to zero for each value
	for(i = 0; i < MAX_HISTOGRAM_SIZE; i++) histogram[i] = 0;
		
		
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
	
	//free memory
	free(input); // This gives me an empty stack trace...
	free(histogram);
	
	return 0;
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