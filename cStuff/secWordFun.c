//secWordFun.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int MAX_WORD_SIZE = 20;
const int MAX = 26;
const int MAX_ROUNDS = 5;
const char ALPHABET[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
						 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
						 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};

int setSecretWord(char secretWord[], int *endOfWord);
void initializeGameAtributes(int alphabetStatus[], int *roundsRemaining);
void printGameResults(int result, char secretWord[], int endOfWord, int alphabetStatus[]);
void printHangman(int numPartsHidden);
char getGuess();
int gamePlay(char secretWord[], int endOfWord, int alphabetStatus[], int *roundsRemaining);
char playAgain(char yes, char no);

int main()
{
	char secretWord[MAX_WORD_SIZE];
	int endOfWord;
	int alphabetStatus[MAX];
	int roundsRemaining = MAX_ROUNDS;
	int gameResult;
	int i;

	//Intro message
	printf("\nLets Play Some Hangman!\n");
	
	//Loop while user agrees
	char repeat = 'y';
	while(repeat == 'y' || repeat == 'Y'){
		
		//Get secret word loop
		while(setSecretWord(secretWord, &endOfWord) == 0);
	
		//Initialize attributes
		initializeGameAtributes(alphabetStatus, &roundsRemaining);
		
		//Try to hide secret word input
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n=============================================================\n");
		printf("THE GAME HAS STARTED");
		
		//Game play loop
		while( (gameResult = gamePlay(secretWord, endOfWord, alphabetStatus, &roundsRemaining)) > 0);
		
		//Output game results
		printGameResults(gameResult, secretWord, endOfWord, alphabetStatus);
		
		//Get decision to play again
		repeat = playAgain('y', 'n');
	}
	
	//Exit message
	printf("\n\nExit\n");
	
	return 0;
}


int setSecretWord(char secretWord[], int *endOfWord){
	int validWord = 1;
	char charCatch = '0';
	int i;
	
	//Reset secret word
	for(i=0; i<MAX_WORD_SIZE; i++){
		secretWord[i] = '\0';
	}
	
	//Ask for input
	printf("\nEnter the secret word.\n");
	
	//Get input
	fgets(secretWord, MAX_WORD_SIZE, stdin );
	
	//Find end of input
	for(i=0; i<MAX_WORD_SIZE; i++){
		if(secretWord[i] == '\n') break;
	}
	
	//Clear buffer stream
	if( (secretWord[i]!= EOF) && (secretWord[i]!= '\n') ){
		do{
			charCatch = getchar();
		}while(charCatch != EOF && charCatch != '\n');
	}
	
	*endOfWord = i;
	
	//Check and format input
	for(i=0; i<*endOfWord; i++){
		if( isalpha(secretWord[i]) == 0 ){
			validWord = 0;
			break;
		}
		else
			secretWord[i] = toupper(secretWord[i]);	
	}
	
	//Word must be at least one letter in length
	if(*endOfWord == 0)
		validWord = 0;
	//Error message
	if(validWord == 0)
		printf("\nOnly alphabet letters allowed. Please try again.\n");
	
	return validWord;
}


void initializeGameAtributes(int alphabetStatus[], int *roundsRemaining){
	int i;
	for(i=0; i<MAX; i++){
		alphabetStatus[i] = 0;	
	}
	*roundsRemaining = MAX_ROUNDS;
}


int gamePlay(char secretWord[], int endOfWord, int alphabetStatus[], int *roundsRemaining){
	int wordIndex;
	int alphIndex;
	char guessedLetter;
	int secretWordFound;
	int guessCount;
	
	//Output Hangman Image
	printHangman(*roundsRemaining);
	
	//Output currently revealed secret word
	printf("Secret Word: ");
	for(wordIndex=0; wordIndex<endOfWord; wordIndex++){
		//Find mapped index for testing
		for(alphIndex=0; alphIndex<MAX; alphIndex++){
			if(secretWord[wordIndex] == ALPHABET[alphIndex])
				break;
		}
		//Test for being correctly guessed
		if(alphabetStatus[alphIndex] == 1)
			printf("%c ", ALPHABET[alphIndex]);
		else
			printf("_ ");
		//if(wordIndex<(endOfWord-1))
		//	printf(" ");
	}
	
	//Output revealed incorrect characters
	printf("\nIncorrect:");
	for(alphIndex=0; alphIndex<MAX; alphIndex++){
		if(alphabetStatus[alphIndex] == -1)
			printf(" %c", ALPHABET[alphIndex]);
	}

	
	//Output remaining characters
	printf("\nRemaining:");
	for(alphIndex=0; alphIndex<MAX; alphIndex++){
		if(alphabetStatus[alphIndex] == 0)
			printf(" %c", ALPHABET[alphIndex]);
	}
	
	//Get Guess Loop
	while( (guessedLetter = getGuess()) == '0');

	//Side effects of correct or incorrect guess
	for(alphIndex=0; alphIndex<MAX; alphIndex++){
		if(ALPHABET[alphIndex] == guessedLetter)
			break;
	}
	guessCount = 0;
	for(wordIndex=0; wordIndex<endOfWord; wordIndex++){
		if(secretWord[wordIndex] == guessedLetter)
			guessCount++;
	}
	
	//Update alphabetStatus and roundsRemaining
	if(guessCount == 0){
		alphabetStatus[alphIndex] = -1;
		*roundsRemaining = *roundsRemaining - 1;
	}
	else{
		alphabetStatus[alphIndex] = 1;
		if(guessCount == 1)
			printf("%c was found 1 time in the secret word.", guessedLetter);
		else
			printf("%c was found %d times in the secret word.", guessedLetter, guessCount);
	}
	
	//Check to see if the secretWord has been found
	secretWordFound = 1;
	for(wordIndex=0; wordIndex<endOfWord; wordIndex++){
		//Find mapped index for testing
		for(alphIndex=0; alphIndex<MAX; alphIndex++){
			if(secretWord[wordIndex] == ALPHABET[alphIndex])
				break;
		}
		//Test for being correctly guessed
		if(alphabetStatus[alphIndex] != 1){
			secretWordFound = 0;
			break;
		}
	}
	
	//Set flag if the secret word has been found
	if(secretWordFound == 1)
		*roundsRemaining = -1;
	
	return *roundsRemaining;	
}


char getGuess(){
	char guess;
	//Ask for input
	printf("\nEnter a one letter guess.\n");
	
	//Get user input
	guess = getchar();
	
	//Check and format input
	if( isalpha(guess) == 0 )
		guess = '0';
	else
		guess = toupper(guess);	
	
	//Error message
	if(guess == '0')
		printf("Only an alphabet letter is allowed. Please try again.");
	
	//Clear buffer stream
	while (getchar() != '\n');
		
	return guess;
}


void printGameResults(int result, char secretWord[], int endOfWord, int alphabetStatus[]){
	int wordIndex;
	int alphIndex;
	
	if(result == 0){
		printHangman(0);
		printf("HANGMAN!\n");
	}
	else{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n=============================================================\n");
		printf("CONGRATS! You guessed the secret word!\n");
	}
	
	printf("The secret word was: %s\n", secretWord);
		if(result == 0){
			printf("You missed: ");
			for(wordIndex=0; wordIndex<endOfWord; wordIndex++){
				//Find mapped index for testing
				for(alphIndex=0; alphIndex<MAX; alphIndex++){
					if(secretWord[wordIndex] == ALPHABET[alphIndex]){
						if(alphabetStatus[alphIndex] == 0)
							printf("%c ", secretWord[wordIndex]);
					}
				}
			}
		}
		
}


char playAgain(char yes, char no){
	char result = '\n';
	printf("\nWould you like to play again?(%c/%c)\n", yes, no);
	result = getchar();
	while (getchar() != '\n');
	return result;
}

void printHangman(int numPartsHidden){
	int column = 100;
	int row = 17;
	char hangman[row][column];
	int i, j;
	
	//initialize a blank hangman
	//From http://ascii.co.uk/art/hangman
	strcpy(hangman[0], " ___________.._________ ");
	strcpy(hangman[1], "| .__________))________|");
	strcpy(hangman[2], "| | / /      ||         ");
	strcpy(hangman[3], "| |/ /       ||         ");
	strcpy(hangman[4], "| | /        ||         ");
	strcpy(hangman[5], "| |/         ()         ");
	for(i=6; i<row; i++){
		strcpy(hangman[i], "| |");
	}

	if(numPartsHidden<5){
		strcpy(hangman[2], "| | / /      ||.-''.       ");
		strcpy(hangman[3], "| |/ /       |/  _  \\     ");
		strcpy(hangman[4], "| | /        ||  `/,|      ");
		strcpy(hangman[5], "| |          (\\\\`_.'     ");
	}
	if(numPartsHidden==3){
		strcpy(hangman[6],  "| |         .-`--'.       ");
		strcpy(hangman[7],  "| |        \\\\ . . //    ");
		strcpy(hangman[8],  "| |          |   |        ");
		strcpy(hangman[9],  "| |          | . |        ");
		strcpy(hangman[10], "| |          |   |        ");
	}
	else if(numPartsHidden<3){
		strcpy(hangman[6],  "| |         .-`--'.       ");
		strcpy(hangman[7],  "| |        /Y . . Y\\     ");
		strcpy(hangman[8],  "| |       // |   | \\\\   ");
		strcpy(hangman[9],  "| |      //  | . |  \\\\  ");
		strcpy(hangman[10], "| |     .)   |   |   (.   ");
	}
	if(numPartsHidden==1){
		strcpy(hangman[11], "| |          ||           ");
		strcpy(hangman[12], "| |          ||           ");
		strcpy(hangman[13], "| |          ||           ");
		strcpy(hangman[14], "| |          ||           ");
		strcpy(hangman[15], "| |         / |           ");	
	}
	else if(numPartsHidden<1){
		strcpy(hangman[11], "| |          || ||        ");
		strcpy(hangman[12], "| |          || ||        ");
		strcpy(hangman[13], "| |          || ||        ");
		strcpy(hangman[14], "| |          || ||        ");
		strcpy(hangman[15], "| |         / | | \\      ");
	}

	printf("\n");
	for(i=0; i<row; i++){
		printf("%s\n", hangman[i]);
	}
}