// recFun2.c
#include <stdio.h>
#include <ctype.h>
int pinCount(int rows);
const int MIN = 0;
const int MAX = 99;
const int MAX_INPUT_SIZE = 4;

int main()
{
	char input[MAX_INPUT_SIZE];
	int index;
	
	int numberOfRows;
	int numberOfPins;
	
	//Determine number of rows through user input
	int validIntInRange = 0;
	while(validIntInRange == 0)
	{
		int validInt = 0;
		while(validInt == 0)
		{
			//Ask for input
			printf("\nEnter number of rows between %d and %d.\n", MIN, MAX);
		
			//Get input
			fgets(input, MAX_INPUT_SIZE, stdin);
		
			//Check input
			int isValidInput = 1;
			for(index = 0; index < MAX_INPUT_SIZE; index++)
			{
				//Must have entered less than three characters
				if(input[index] == '\n')
				{
					input[index] = 0;
					break;
				}
				
				//Entered more than two characters
				if(input[index] == 0) 
				{
					isValidInput = 0;
					//Clear the buffer
					while(getchar() != '\n');
					break;
				}
				
				//Each character must be a digit through (0-9)
				if(!isdigit(input[index])) isValidInput = 0;
			}
			
			//Check input for at least 1 number
			if(!isdigit(input[0])) isValidInput = 0;
			
			//Correct input escape
			if(isValidInput)
				validInt = 1;
			else
			//Incorrect input message
			printf("Invalid input. Please enter an integer.\n");
			
		}// Input successfully converted into an integer value
		
		
		//Convert input into an int value
		numberOfRows = 0;
		int baseTenPower = 1;
		while(index>0) //My use of index between tests might be confusing
		{
			index--;
			numberOfRows+= (baseTenPower * (input[index] - '0'));
			baseTenPower *= 10;
		}
		
		//Check input for being in range of MIN and MAX
		if(numberOfRows < MIN || numberOfRows > MAX){
			printf("Invalid input. Must be within %d and %d\n", MIN, MAX);
		}
		else{
			validIntInRange = 1;
		}
		
	}// Input value is within correct range
	
	//numberOfRows goes into function
	printf("numberOfRows: %d\n", numberOfRows);
	numberOfPins = pinCount(numberOfRows);
	
	//Output results
	printf("numberOfPins: %d\n", numberOfPins);
	
	return 0;
}

int pinCount(int rows){
	if(rows == 1) return 1;
	else return (rows + pinCount(rows-1));
}
