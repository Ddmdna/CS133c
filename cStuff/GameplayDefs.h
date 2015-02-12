//This will define functions for the Gameplay
#include <stdio.h>

int printChangeSecretNumInstructions(char player[100], int min, int max){
	printf("\n========================================\n");
	printf("%s needs to set the secret number.\n", player);
	printf("Enter a number between %d and %d\n", min, max);
	printf("Input: ");
}
int getSecretNum_IO(int min, int max){
	int result;
	scanf("%d", &result);
	return result;
}
int determineHintRangeStart(int secretNum, int range, int min, int max, int randVal){
	int result = 0;
	if( (secretNum-range > min)&&(secretNum-range < max) ) min = secretNum-range;
	result = min + (randVal%range);
	if(result > secretNum) result = secretNum; //Quick fix just in case...
	if(result > max-range) result = max-range;
	
	//Secret Num - range :less than min?
	//SecretNum + range :more than max?
	return result;
}
int printGuessesRemaining(char name[100], int guessNum, int maxGuess){
	int remaining = maxGuess - guessNum;
	printf("\n========================================\n");
	printf("%s has %d guesses remaining.\n", name, remaining);
	return 0;
}
int printHintRange(int start, int end){
	printf("Possible solutions are as follows:\n");
	printf("(%d - %d)\n", start, end);
	return 0;
}
int getGuess_IO(){
	int result;
	scanf("%d", &result);
	return result;
}
int checkGuess(int guess, int start, int end){ // return 0 if guess is within range
	int flag = 1;
	if(guess>=start && guess <= end) flag = 0;
	return flag;
}
int printInvalidGuessMessage(){
	printf("Invalid guess...\n");
	return 0;
}
int printSecretNumFound(){
	printf("You guessed correctly!\n");
	printf("The secret number has been found!\n");
	return 0;
}
int printGuessTooLowMessage(){
	printf("Your guess was too low.\n");
	return 0;
}
int printGuessTooHighMessage(){
	printf("Your guess was too high.\n");
	return 0;
}
int printGuessAgain(){
	printf("Guess again.\n");
	return 0;
}
int printGameResults(char p1[100], int p1BadGuesses, int p1GoodGuesses, 
					 char p2[100], int p2BadGuesses, int p2GoodGuesses){
	int p1Result = p1GoodGuesses - p1BadGuesses;
	int p2Result = p2GoodGuesses - p2BadGuesses;
	printf("\n========================================\n");
	if(p1Result >= p2Result){
		printf("%s wins\n", p1);
	}
	else{
		printf("%s wins\n", p2);
	}
	return 0;	
}