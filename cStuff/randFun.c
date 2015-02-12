/*

	(5) Write a function that acts like a random number generator with the following behaviour:
	File must be called: randFun.c
	
	Note: you can use the rand function in your function, you do not have to make your own
	random number generator code from scratch!
	
	hint: reusing code you have written may be a good idea again...
	
	Discussion idea: Are there different ways you could setup a function to do this? Are there
	benefits of accepting arguments over asking for user input (and the other way around)?
		a. Your function signature should look like: int rand_int(int min, int max),
		b. The function should accept two int values (one for the minimum value for some random
		    number in a range and one for the maximum number in the range), generate a number
			within that range, and then return that number, though the exact details on how it generates
			the number are up to you,
			
	Discussion idea: I am guessing that some of you may have found ways to generate
	random numbers with a one line expression, why might it be a good idea (or a bad idea) to
	have this in a function instead of as a one line expression in our code? Why might I say
	that your final answer should accept arguments and return a value and not mention the
	user input or possibility of output to the screen?
	
*/
// randFun.c
#include <stdio.h>
#include <stdlib.h>

int rand_int(int min, int max){
	int range = (max - min + 1); //number of possible values
	int randInt = rand();
	randInt = min + (randInt%range);
	return randInt;
}

int main()
{
	//Max int 2,147,483,647
	//Could use an unsigned int to find the range!
	//so... Lets look at 9 characters to be safe or 10 if a '-' is first
	//Our range possible: (-1,000,000,000 to 1,000,000,000)
	int const MAX = 10;
	int bounds[2];
	
	char intStr[MAX];
	char buffer[MAX+1];
	char charCatch;
	
	int indexLimit = MAX;
	
	int baseTenPower;
	int convertedInt;
	
	int hasMinus;
	int validIntStr;
	
	int lowerBoundComplete;
	int upperBoundComplete;
	
	int index;
	int boundIndex;
	
	
	//Random Attributes
	time_t t;
	srand((unsigned) time(&t));
	int randVal = 0;
	
	//Loop as long as user agrees
	char repeat = 'y';
	while(repeat == 'y' || repeat == 'Y'){
		lowerBoundComplete = 0;
		upperBoundComplete = 0;
		bounds[0] = 0;
		bounds[1] = 0;
		
		boundIndex = 0;
		
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
		randVal = rand_int(bounds[boundIndex-1], bounds[boundIndex]);
		
		
		//==================================================
		//14.	Output random number
		//==================================================
		printf("\nA random value within the given range is as follows:\n");
		printf("%d\n", randVal);
	
		//Ask user if they would like to repeat the program
		printf("\nWould you like to try again?(y/n)\n");
		
		//Get user input
		repeat = getchar();
		
		//Clear buffer stream
		while (getchar() != '\n');
		
	}
	
	return 0;
}