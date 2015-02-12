// savings.c
#include <stdio.h>
#include <ctype.h>
int getIntegerInRange(int min, int max, int inputSize, int *flag);
double futureSavingsTotal(double savings, int interest, int years);

const int MIN_SAVINGS = 0;
const int MAX_SAVINGS = 100000;
const int MIN_INTEREST = 0;
const int MAX_INTEREST = 100;
const int MIN_YEARS = 0;
const int MAX_YEARS = 100;
const int MAX_INPUT_SIZE = 10;

int main()
{	
	double calculatedSavings;
	int savings, interest, years;
	int flag;
	
	printf("\n");
	flag = 1;
	while(flag!=0){
		printf("\nInput the initial amount to be placed into savings.\n");
		savings = getIntegerInRange(MIN_SAVINGS, MAX_SAVINGS, MAX_INPUT_SIZE, &flag);
		if(flag) printf("Invalid input. Please try again.\n");
	}
	
	printf("\n");
	flag = 1;
	while(flag!=0){
		printf("\nInput the yearly interest rate.\n");
		interest = getIntegerInRange(MIN_INTEREST, MAX_INTEREST, MAX_INPUT_SIZE, &flag);
		if(flag) printf("Invalid input. Please try again.\n");
	}
	
	printf("\n");
	flag = 1;
	while(flag!=0){
		printf("\nInput the number of years the money will accrue compounding interest.\n");
		years = getIntegerInRange(MIN_YEARS, MAX_YEARS, MAX_INPUT_SIZE, &flag);
		if(flag) printf("Invalid input. Please try again.\n");
	}
	
	//INPUTS
	printf("\n\nSavings: %d\n", savings);
	printf("Interest: %d\n", interest);
	printf("Years: %d\n", years);
	
	//Output function results
	calculatedSavings = futureSavingsTotal((double)savings, interest, years);
	printf("\nCalculated Savings: %.2f\n", calculatedSavings);
	return 0;
}

int getIntegerInRange(int min, int max, int inputSize, int *flag)
{
	int result = 0;
	
	char input[inputSize];
	int index;
	
	//Get input
	printf("Integer between %d and %d.\n", min, max);
	fgets(input, inputSize, stdin);

	//Check input
	int isValidInput = 1;
	for(index = 0; index < inputSize; index++)
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
	if(!isdigit(input[0]))
	{
		isValidInput = 0;
	} 
	
	if(isValidInput)
	{
		//Convert input into an int value
		int baseTenPower = 1;
		while(index>0) //My use of index between tests might be confusing
		{
			index--;
			result+= (baseTenPower * (input[index] - '0'));
			baseTenPower *= 10;
		}
			
		//Check input for being in range of MIN and MAX
		if(result >= min && result <= max)
		{
			*flag = 0;
		}
	}
	
	return result;
}// Input value is within correct range

double futureSavingsTotal(double savings, int interest, int years)
{
	if(years == 0) return savings;
	else
	{
		savings += savings * (double)interest / 100;
		years--;
		return(futureSavingsTotal(savings, interest, years));
	} 
}