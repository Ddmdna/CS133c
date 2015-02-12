//This will define functions for the Main Menu
#include <stdio.h>

int printMainMenu(){
	printf("\n========================================\n");
	printf("Main Menu\n");
	printf("Select one of the following options:\n");
	printf("(0) Exit Program\n");
	printf("(1) Change Game Settings\n");
	printf("(2) Play Guessing Game\n");
	printf("Input: ");
}
int getMainMenuOption_IO(){
	int result;
	scanf("%d", &result);
	return result;
}