// randNum2.c
#include <stdio.h>
#include <stdlib.h>
int main()
{
	//Max int 2,147,483,647
	//Could use an unsigned int to find the range!
	//so... Lets look at 9 characters to be safe or 10 if a '-' is first
	//Our range possible: (-1,000,000,000 to 1,000,000,000)
	int const MAX = 10;
	int bounds[] = {0, 0};
	
	char intStr[MAX];
	char buffer[MAX+1];
	char charCatch = '0';
	
	int indexLimit = MAX;
	
	int baseTenPower = 1;
	int convertedInt = 0;
	
	int hasMinus = 0;
	int validIntStr = 1; // Innocent until proven guilty
	
	int lowerBoundComplete = 0;
	int upperBoundComplete = 0;
	
	int maxGreaterCheck = 1;
	
	int index = 0;
	int boundIndex = 0;
	
	
	//Random Attributes
	time_t t;
	srand((unsigned) time(&t));
	int randVal = 0;
	int range = 0;
	
	//Tell the user the goal of the program
	printf("Please specify the range for a random number to be generated within.\n");
	
	while(lowerBoundComplete == 0 || upperBoundComplete == 0){
		//==================================================
		//0.	Reset attributes
		//==================================================
		indexLimit = MAX;
		baseTenPower = 1;
		hasMinus = 0;
		validIntStr = 1;
		index = 0;
		
		
		//==================================================
		//1.	Ask user to input lower and upper bounds
		//==================================================
		if(lowerBoundComplete) 	printf("Enter the upper bound value:\n");
		else					printf("Enter the lower bound value:\n");
								
		
		//==================================================
		//2.	Get input from user
		//==================================================
		fgets(buffer, sizeof buffer, stdin );
		
		//==================================================
		//3. 	Check for '-' and make corrections for testing
		//==================================================
		if(buffer[0] == '-') hasMinus = 1;
		
		//Change index to start past the '-' char if it was at buffer[0]
		if(hasMinus) index++;
		
		//Change indexLimit to add and extra digit for negative values 
		//or remove one for positive values
		if(hasMinus) indexLimit++;
		else indexLimit--;
		
		//==================================================
		//4.	Check for valid characters up to indexLimit
		//		At least 1 char must be valid past '-'
		//==================================================
		do{
			switch(buffer[index]){
				case '0': break; case '1': break;
				case '2': break; case '3': break;
				case '4': break; case '5': break;
				case '6': break; case '7': break;
				case '8': break; case '9': break;
				default: validIntStr = 0;
			}
			index++;
		}while( (index < indexLimit) && (buffer[index] != '\0') && (buffer[index] != '\n') );
		
		//==================================================
		//5.	Handle invalid data input
		//==================================================
		if(validIntStr == 0){
			printf("\nInvalid input, please try again...\n");
			continue;
		}
		
		
		//==================================================
		//6.	Set the appropriate initial base ten power
		//==================================================
		//Set to the first instance of '\0', '\n', or the previously designated indexLimit
		indexLimit = index;
		
		//Change index to not count '-' as an additional power of ten
		index = hasMinus + 1;
		
		// Set the appropriate initial base ten power
		while(index<indexLimit){
			baseTenPower*= 10;
			index++;
		}

		
		//==================================================
		//8.	Pass along valid input to intString
		//		Dont pull '-' from buffer
		//==================================================
		for(index = 0; index<indexLimit; index++){
			intStr[index] = buffer[index+hasMinus];
		}

		
		//==================================================
		//9.	Convert intStr to an int value for bounds[boundIndex]
		//==================================================
		for(index = 0; index<indexLimit; index++){
			convertedInt = 0;
			switch(intStr[index]){
				case '9': convertedInt++;
				case '8': convertedInt++;
				case '7': convertedInt++;
				case '6': convertedInt++;
				case '5': convertedInt++;
				case '4': convertedInt++;
				case '3': convertedInt++;
				case '2': convertedInt++;
				case '1': convertedInt++;
			}
			//Add the appropriate amount
			if(baseTenPower) bounds[boundIndex] += convertedInt*baseTenPower;
			else bounds[boundIndex] += convertedInt;
			
			//reduce baseTenPower by 1
			baseTenPower/=10;
		}
		
		//flip the sign of the bound if it has a '-'
		if(hasMinus) bounds[boundIndex]*=(-1);
		
		//==============================================================
		//10.	Make sure the buffer is clear
		//==============================================================
		
		if( (buffer[index]!= EOF) && (buffer[index]!= '\n') ){
			do{
				charCatch = getchar();
			}while(charCatch != EOF && charCatch != '\n');
		}
		
		//==================================================
		//11.	Set the status of of the current bound and the boundIndex
		//==================================================
		//update lowerBoundComplete if necessary
		if(lowerBoundComplete == 0) {
			lowerBoundComplete = 1;
			boundIndex = 1;
			continue;
		}
		
		//update upperBoundComplete if(upperBound >= lowerBound) else handle with an output
		if(bounds[boundIndex] >= bounds[boundIndex-1]) upperBoundComplete = 1;
		else {
			printf("\nUpper bound must be greater than or equal to lower bound.\n");
			bounds[boundIndex] = 0;
		}
	}
	
	//==================================================
	//12.	Output bounds
	//==================================================
	printf("\n\nYou have choosen the following:\n");
	printf("Lower bound: %10d\nUpper bound: %10d\n", bounds[boundIndex-1], bounds[boundIndex]);
	
	
	//==================================================
	//13.	Generate a number within that range
	//		I believe low order bits will not be very random with this approach...
	//==================================================
	range = (bounds[boundIndex] - bounds[boundIndex-1] + 1); //number of possible values
	randVal = rand();
	randVal = bounds[boundIndex-1] + (randVal%range);
	
	//==================================================
	//14.	Output random number
	//==================================================
	printf("\nA random value within the given range is as follows:\n");
	printf("%d\n", randVal);
	
	return 0;
}