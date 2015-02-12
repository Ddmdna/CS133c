//This will define functions for the Settings Menu
#include <stdio.h>

int printSettingsMenu(){
	printf("\n========================================\n");
	printf("Settings Menu\n");
	printf("Select one of the following options:\n");
	printf("(0) Exit Settings Menu\n");
	printf("(1) Change the number of playable rounds\n");
	printf("(2) Change the number of allowable guesses\n");
	printf("(3) Change the hint range\n");
	printf("Input: ");
}
int getSettingsMenuOption_IO(){
	int result;
	scanf("%d", &result);
	return result;
}

int printChangeMaxRoundInstructions(maxRound){
	printf("\n========================================\n");
	printf("Current round limit: %d\n", maxRound);
	printf("What will you change the round limit to?\n");
	printf("Input: ");
	return 0;
}
int getMaxRound_IO(){
	int result;
	scanf("%d", &result);
	return result;
}
int printChangeMaxGuessInstructions(maxGuess){
	printf("\n========================================\n");
	printf("Current guess limit per round: %d\n", maxGuess);
	printf("What will you change the guess limit to?\n");
	printf("Input: ");
	return 0;
}
int getMaxGuess_IO(){
	int result;
	scanf("%d", &result);
	return result;
}
int printChangeMaxHintRangeInstructions(maxHintRange){
	printf("\n========================================\n");
	printf("Current hint range: %d\n", maxHintRange);
	printf("What will you change the hint range to?\n");
	printf("Input: ");
	return 0;
}
int getMaxHintRange_IO(){
	int result;
	scanf("%d", &result);
	return result;
}
