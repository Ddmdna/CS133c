//dynamicFun.c
#include <stdio.h>
#include <stdlib.h>
int dynamicFunction(int **dynamicIntArray);

int main()
{
	//Pointer to an int: for dynamic int array
	int *dynamicIntArray_ptr;
	
	//Exercise Component 2:
	int length = dynamicFunction(&dynamicIntArray_ptr);
	
	//Print the newly created array
	int i;
	printf("\nThe newly created array..\n");
	for(i = 0; i < length; i++)
	{
		printf("%d: %d\n", i, dynamicIntArray_ptr[i]);
	}
	
	//Free the memory dynamically allocated
	free(dynamicIntArray_ptr);
	
	return 0;
}

//Accept a pointer to an int
int dynamicFunction(int **dynamicIntArray)
{
	//Curently set such that the user won't get stuck inputting 100s of elements into an array
	//This could be changed later to the maximum space available in memory, or the highest int value.(whichever caps first)
	int sizeMin = 1;
	int sizeMax = 20;
	
	//A guessed number such that the input works with getIntegerInRange.
	//This could be the min and max integer values enabled by my system.
	int inputMin = -1000000000;
	int inputMax =  1000000000;
	
	//Determine the maximum size of the dynamic array
	int size;
	int sizeFlag = 1;
	while(sizeFlag)
	{
		//Ask the user to decide on a size for the dynamic array
		printf("Enter the maximum size for the dynamic array\n(%d to %d): ", sizeMin, sizeMax);
		//Get verified user integer input for size
		size = getIntegerInRange(sizeMin, sizeMax, 15, &sizeFlag);
		//Output error message if necessary
		if(sizeFlag)
			printf("Invalid Input\n");
	}
	
	//Create an array of int values dynamically
	*dynamicIntArray = (int*)malloc(size * sizeof(int));
	
	//Ask the user to input values to fill the newly created array
	//Get verified user integer input for each element allocated for the array
	int i, fillFlag;
	for(i = 0; i < size; i++)
	{
		fillFlag = 1;
		while(fillFlag)
		{
			printf("Enter an integer within range(%d to %d)\n(%d out of %d): ", inputMin, inputMax, i, size);
			(*dynamicIntArray)[i] = getIntegerInRange(inputMin, inputMax, 15, &fillFlag);
			if(fillFlag)
				printf("Invalid Input\n");
		}
	}
	return size;
}
	
	
//From tictactoe2.c
int getIntegerInRange(int min, int max, int inputSize, int *flag)
{
	int result = 0;
	
	char input[inputSize];
	int index;
	
	//Get input
	fgets(input, inputSize, stdin);

	//Check input
	//Account for negative numbers
	int validMinus = 0;
	if(input[0] == '-')
		validMinus = 1;

	int isValidInput = 1;
	for(index = (0+validMinus); index < (inputSize + validMinus); index++)
	{
		//Input <= inputSize
		if(input[index] == '\n')
		{
			input[index] = 0;
			break;
		}
		
		//Input > inputSize
		if(input[index] == 0) 
		{
			isValidInput = 0;
			//Clear buffer
			while(getchar() != '\n');
			break;
		}
		
		//Check to see that each char is a digit
		if(!isdigit(input[index]))
		{
			isValidInput = 0;
		}
	}
	//Ensure that at least one digit was input	
	if(!isdigit(input[0 + validMinus]))
	{
		isValidInput = 0;
	} 
	
	if(isValidInput)
	{
		//Convert input into an int value
		int baseTenPower = 1;
		while(index>(0 + validMinus)) //My use of index between tests might be confusing
		{
			index--;
			result+= (baseTenPower * (input[index] - '0'));
			baseTenPower *= 10;
		}
			
		if(validMinus)
			result*=(-1);
		//Check input for being in range of MIN and MAX
		if(result >= min && result <= max)
		{
			*flag = 0;
		}
	}
	return result;
}// Input value is within correct range