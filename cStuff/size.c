// size.c
#include <stdio.h>

int getInt();
int getHeight();
int getWeight();
int getAge();
double solveHatSize(int weight, int height);
double solveJacketSize(int weight, int height, int age);
double solveWaistSize(int weight, int age);

int main()
{
	int height;
	int weight;
	int age;
	double hatSize;
	double jacketSize;
	double waistSize;
	
	//Loop while user agrees
	char repeat = 'y';
	while(repeat == 'y' || repeat == 'Y'){
		
		//Set base attributes
		height = getHeight();
		weight = getWeight();
		age = getAge();
		
		//Set complex attributes
		hatSize = solveHatSize(weight, height);
		jacketSize = solveJacketSize(weight, height, age);
		waistSize = solveWaistSize(weight, age);
		
		//Print results
		printf("\n\nYour results are as follows:\n");
		printf("Height: %d\n", height);
		printf("Weight: %d\n", weight);
		printf("Age: %d\n", age);
		printf("Hat Size: %.2f\n", hatSize);
		printf("Jacket Size: %.2f\n", jacketSize);
		printf("Waist Size: %.2f\n", waistSize);
		
		//Ask user if they would like to repeat the program
		printf("\nWould you like to try again?(y/n)\n");
		
		//Get user input
		repeat = getchar();	
		
		//Clear buffer stream
		while (getchar() != '\n');	
	}
	
	return 0;
}


int getHeight(){
	printf("Enter your height in inches.\n");
	int result = getInt();
	while(result < 1){
		printf("Height must be greater than 0.\n");
		printf("Enter your height in inches.\n");
		result = getInt();
	}
	return result;
}

int getWeight(){
	printf("Enter your weight in pounds.\n");
	int result = getInt();
	while(result < 1){
		printf("Weight must be greater than 0.\n");
		printf("Enter your weight in pounds.\n");
		result = getInt();
	}
	return result;
}

int getAge(){
	printf("Enter your age in years.\n");
	int result = getInt();
	while(result < 1){
		printf("Age must be greater than 0.\n");
		printf("Enter your age in years.\n");
		result = getInt();
	}
	return result;
}

//Taken from randNum2.c but with alterations.
//I could go without negative numbers but I've left it intact for now.
int getInt(){
	int result = 0;
	//Prevent integers from reaching +- one billion
	const int MAX = 10;
	
	//Used to clean up the buffer
	char charCatch;
	
	//Gets unchecked input
	char buffer[MAX+1];
	
	//Gets checked input
	char intStr[MAX];
	
	
	int index;
	int indexLimit;
	int baseTenPower;
	int hasMinus;
	int validIntStr;
	
	
	int invalidInput = 1;
	while(invalidInput){
		//Get input
		fgets(buffer, sizeof buffer, stdin );
		
		//Check for '-' and make corrections for testing
		if(buffer[0] == '-')
			hasMinus = index = 1;	//Index starts past '-'
		
		else
			hasMinus = index = 0;
		
		//Change indexLimit to add and extra digit for negative values (MAX + 1)
		//or remove one one digit for positive values (MAX - 1)
		indexLimit = MAX - 1 + hasMinus + index;
			
		//Check for valid characters up to indexLimit
		validIntStr = 1;
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
			
		//Handle invalid data input
		if(validIntStr == 0){
			printf("\nInvalid input, please try again...\n");
			continue; // Start over...
		}
		
		//Set the appropriate initial base ten power
		//Set indexLimit to the end of the valid int string ie: '\n', '\0', or previous indexLimit
		indexLimit = index;
		
		//Change index to not count '-' as an additional power of ten
		index = hasMinus + 1;
		
		// Set the appropriate initial base ten power
		baseTenPower = 1;
		while(index<indexLimit){
			baseTenPower*= 10;
			index++;
		}
		
		//Pass along valid input to intString
		//Don't pull '-' from buffer
		for(index = 0; index<indexLimit; index++){
			intStr[index] = buffer[index+hasMinus];
		}
		
		//Convert intStr to an integer value
		int convertedInt;
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
			if(baseTenPower)
				result += convertedInt*baseTenPower;
			else
				result += convertedInt;
			
			//reduce baseTenPower by 1
			baseTenPower/=10;
		} // end string to integer conversion loop
		
		//flip the sign of the bound if it has a '-'
		if(hasMinus) result*=(-1);
		
		//Make sure the buffer is clear
		charCatch = '0';
		if( (buffer[index]!= EOF) && (buffer[index]!= '\n') ){
			do{
				charCatch = getchar();
			}while(charCatch != EOF && charCatch != '\n');
		}
		invalidInput = 0; // end loop assignment
	}// Get a valid integer loop
	
	return result;
}


//Hat size =weight in pounds divided by height in inches and all that multiplied by 2.9.
double solveHatSize(int weight, int height){
	double hatSize = 0;
	if(height != 0){
		hatSize = (double)weight / (double)height;
		hatSize *= 2.9;
	}
	return hatSize;
}

/*
	Jacket size (chest in inches) = height times weight divided by 288 and then adjusted by
	adding one-eighth of an inch for each 10 years over age 30. (Note that the adjustment only
	takes place after a full 10 years. So, there is no adjustment for ages 30 through 39, but
	one-eighth of an inch is added for age 40.)
*/
double solveJacketSize(int weight, int height, int age){
	double jacketSize = (double)height * (double) weight;
	jacketSize /= 288.0;
	if(age>30)
		age -= 30;
	else
		age = 0;
	int adjustment = age / 10;
	jacketSize += (double)adjustment * (1.0 / 8.0);
	return jacketSize;
}
/*
	Waist in inches =weight divided by 5.7 and then adjusted by adding one-tenth of an inch
	for each 2 years over age 28. (Note that the adjustment only takes place after a full 2
	years. So, there is no adjustment for age 29, but one-tenth of an inch is added for age 30.)
*/
double solveWaistSize(int weight, int age){
	double waistSize = (double) weight / 5.7;
	if(age>28)
		age -= 28;
	else
		age = 0;
	int adjustment = age / 2;
	waistSize += (double)adjustment * (1.0/10.0);
	return waistSize;
}