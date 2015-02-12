/*

	(5) Create a program for the following (originally from Absolute C++)

	File must be called: finalist.c

	“You have four identical prizes to give away and a pool of 25 finalists. The finalists are
	assigned numbers from 1 to 25. Write a program to randomly select the numbers of 4
	finalists to receive a prize. Make sure not to pick the same number twice. For example,
	picking finalists 3, 15, 22, and 14 would be valid but picking 3, 3, 31, and 17 would be
	invalid, because finalist number 3 is listed twice and 31 is not a valid finalist number.”

	Discussion idea: How can we make sure that in the end no person gets picked multiple
	times as a winner?

	5. Be sure to test that each of your sections of code work correctly in a variety of cases.

	After you think your code is good, trade it with another person and try to break their code
	(share with the other person what you find works well and what does not).

	Note: Later we will have points based on this, so be sure to at least try to work with the
	proposed programs of others!

*/
// finalist.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_FINALISTS = 25;
const int MAX_WINNERS = 4;

void initializeFinalists(char finalists[]);
void initializeWinners(char winners[]);
void setWinners(char winners[], char finalists[]);
void printWinners(char winners[]);

int rand_int(int min, int max);
char getFinalist(int index, char finalists[]);

int main()
{
	//Random Attributes
	time_t t;
	srand((unsigned) time(&t));
	int randVal;

	//Array attributes
	char finalists[MAX_FINALISTS+1];
	char winners[MAX_WINNERS+1];
	
	//Loop while user agrees
	char repeat = 'y';
	while(repeat == 'y' || repeat == 'Y'){
			
		//Initialize finalist and winner arrays
		initializeFinalists(finalists);
		initializeWinners(winners);
		
		//Set Winners
		setWinners(winners, finalists);
		
		//print Winners
		printWinners(winners);	
	
		//Ask user if they would like to repeat the program
		printf("\nWould you like to try again?(y/n)\n");
		
		//Get user input
		repeat = getchar();
		
		//Clear buffer stream
		while (getchar() != '\n');
	}
	
	return 0;
}


void initializeFinalists(char finalists[]){
	//Initialize finalist array
	char i = 0;
	while(i<MAX_FINALISTS){
		finalists[i] = (i+1);
		i++;
	}
	//Cap finalists array
	finalists[MAX_FINALISTS] = '\0';
}

void initializeWinners(char winners[]){
	//Initialize winners array
	char i = 0;
	while(i<MAX_WINNERS){
		winners[i] = (i+1);
		i++;
	}
	//Cap winners array
	winners[MAX_WINNERS] = '\0';
}

void setWinners(char winners[], char finalists[]){
	char i = 0;
	while(i<MAX_WINNERS){
		winners[i] = getFinalist( rand_int(0, strlen(finalists)-1), finalists );
		i++;
	}
}

void printWinners(char winners[]){
	printf("\nThe winners are as follows:\n");
	int i = 0;
	while(i<MAX_WINNERS){
		printf("%2d  ", winners[i]);
		i++;
	}
	printf("\n");
}

int rand_int(int min, int max){
	int range = (max - min + 1); //number of possible values
	int randInt = rand();
	randInt = min + (randInt%range);
	return randInt;
}

char getFinalist(int index, char finalists[]){
	char finalist = finalists[index];
	int numFinalists = strlen(finalists);
	memmove(finalists+index, finalists+index+1, numFinalists - index-1);
	finalists[numFinalists-1] = '\0';
	return finalist;
}

