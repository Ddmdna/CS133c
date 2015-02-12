#include <stdio.h>
#include <stdlib.h>
#include "MainMenuDefs.h"
#include "SettingsMenuDefs.h"
#include "GameplayDefs.h"

int printAppInfo(){
	printf("\n\n");
	printf("========================================\n");
	printf("This is a guessing game for two players.\n");
	printf("========================================\n");
	printf("\n\n");
	return 0;
}
int printExitMessage(){
	printf("\n\n");
	printf("========================================\n");
	printf("Thanks for playing.\n");
	printf("========================================\n");
	printf("\n\n");
	return 0;
}

int main(int argc, char const *argv[])
{
	//Random Attributes
	time_t t;
	srand((unsigned) time(&t));
	int randVal = 0;
	
	
	//Player attributes
	char playerName[2][100] = {"Player 1\0", "Player 2\0"};
	int playerBadGuesses[2] = {0, 0};
	int playerGoodGuesses[2] = {0, 0};
	int currentNumberSetter = 0;
	int currentNumberGuesser = 1;
	int NUM_PLAYERS = 2;
	
	//Round attributes
	int maxRound = 1;
	int roundNum = 0;
	
	//Guess attributes
	int maxGuess = 5;
	int guessNum = 0;
	int guess = 0;
	int invalidGuess = 0;
	
	//Hint range attributes
	int maxHintRange = 10;
	int hintRangeStart = 0;
	int hintRangeEnd = 10;
	
	//Secret number attributes
	int secretNum = 0;
	int MAX_NUM = 1000;
	int MIN_NUM = 0;
	
	//While loop control attributes
	int inSettingsMenu = 0;
	int running = 1;
	int iterator = 0;
	
	printAppInfo(); // Where to define this?
	while(running){
		printMainMenu();
		switch (getMainMenuOption_IO()){
			case 0: // User selected to end the program
				running = 0;
				break;
					
			case 1: // User selected Settings Menu
				inSettingsMenu = 1;
				while(inSettingsMenu){
					printSettingsMenu();
					switch (getSettingsMenuOption_IO()){
						case 0: // User selected to go back to Main Menu
							inSettingsMenu = 0;
							break;
						
						case 1: // User selected to change the number of rounds to play
							printChangeMaxRoundInstructions(maxRound);
							maxRound = getMaxRound_IO();
							break;
							
						case 2: // User selected to change the number of guesses per round
							printChangeMaxGuessInstructions(maxGuess);
							maxGuess = getMaxGuess_IO();
							break;
							
						case 3: // User selected to change the hint range
							printChangeMaxHintRangeInstructions(maxHintRange);
							maxHintRange = getMaxHintRange_IO();
							break;
					} // end of getSettingsMenuOption switch statement
				} // End of Settings Menu while loop
				break;
				
			case 2: // User selected to play the game
				roundNum = 0;
				while(roundNum<maxRound){
					currentNumberSetter = 0; //Player 1 starts setting the secret number
					currentNumberGuesser = 1; //Player 2 starts guessing at the secret number set by Player 1
					while(currentNumberSetter<NUM_PLAYERS){
						secretNum = MIN_NUM - 1; //This is a problem when (MIN_NUM - 1) leads to overflow
						while(secretNum>MAX_NUM || secretNum<MIN_NUM){ //I might want to change this to secretNumFlag
							printChangeSecretNumInstructions(playerName[currentNumberSetter], MIN_NUM, MAX_NUM);
							secretNum = getSecretNum_IO(MIN_NUM, MAX_NUM);
						}
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // A quick method to hide the secret number
						randVal = rand();
						hintRangeStart = determineHintRangeStart(secretNum, maxHintRange, MIN_NUM, MAX_NUM, randVal);
						hintRangeEnd = hintRangeStart + maxHintRange;
						guessNum = 0;
						while(guessNum<maxGuess){
							invalidGuess = 1;
							while(invalidGuess){ //Ensures a guess is within the correct range
								printGuessesRemaining(playerName[currentNumberGuesser],guessNum, maxGuess);
								printHintRange(hintRangeStart, hintRangeEnd);
								guess = getGuess_IO(); //I might want to change this to guessFlag
								invalidGuess = checkGuess(guess, hintRangeStart, hintRangeEnd);
								if(invalidGuess) printInvalidGuessMessage();
							} // guess should now be valid
							if(guess == secretNum){ //correct guess
								playerGoodGuesses[currentNumberGuesser] = playerGoodGuesses[currentNumberGuesser] + 1;
								printSecretNumFound();
								break;
							}
							else { //incorrect guess
								playerBadGuesses[currentNumberGuesser] = playerBadGuesses[currentNumberGuesser] + 1;
								if(guess<secretNum) {
									printGuessTooLowMessage();
									hintRangeStart = guess;
								}
								else {
									printGuessTooHighMessage();
									hintRangeEnd = guess;
								}
								printGuessAgain();
							}
							guessNum = guessNum + 1;
						} // The currentNumberGuesser finished guessing
						// Switch rolls
						currentNumberGuesser = currentNumberSetter;
						currentNumberSetter = currentNumberSetter + 1;
					} // while loop for each player being the secret number setter
					roundNum = roundNum + 1;
				} // while loop for rounds
				printGameResults(playerName[0], playerBadGuesses[0], playerGoodGuesses[0], 
								 playerName[1], playerBadGuesses[1], playerGoodGuesses[1]);
				//Reset all player stats
				for(iterator = 0; iterator<NUM_PLAYERS; iterator = iterator + 1){
					playerBadGuesses[iterator] = 0;
					playerGoodGuesses[iterator] = 0;
				}
				break;
			
		} // End of getMainMenuOption switch statement
		
		
	} // End of running while loop
	printExitMessage();
	
	return 0;
}