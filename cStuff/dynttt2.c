//dynttt2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Global Attributes
#define MAX_LOCATIONS 9
#define LOCATION_SUBSET 3

#define WINNING_X_GAME 1
#define WINNING_O_GAME 2
#define CAT_GAME 3
#define MORE_MOVES_LEFT 4

#define EMPTY 0
#define X 1
#define O 2

#define EASY 1
#define MEDIUM 2
#define HARD 3

//AI struct
struct AI
{
	int currentDifficulty;
	int numGamesWon;
	int numGamesLost;
	int numGamesTied;
};

//Game struct
struct Game
{
	int numDimensions;
	int numColumns;
	int numRows;
	int **board;

	int numXWins;
	int numOWins;
	int numCatGames;
};

//struct AI functions
int construct_AI(struct AI *thisAI, int difficulty);
int evaluate_AI(struct AI *thisAI);
int setDifficulty_AI(struct AI *thisAI, int difficulty);
int settings_AI(struct AI *thisAI);

//struct Game functions
int construct_Game(struct Game *thisGame, char *dimensions);
int isXTurn_Game(struct Game *thisGame);
int determineGameState_Game(struct Game *thisGame);
int resetBoard_Game(struct Game *thisGame);
int outPutResults_Game(struct Game *thisGame); //Contains console output
int printBoard_Game(struct Game *thisGame);	//Contains console output
int xTurn_Game(struct Game *thisGame); //Contains console output and keyboard input

//struct AI and struct Game combined functions
int mainMenu(struct AI *thisAI, struct Game *thisGame);	//Contains console output and keyboard input(getIntegerInRange)
int gamePlay(struct AI *thisAI, struct Game *thisGame);	//Contains console output and keyboard input

int oTurn_Game(struct Game *thisGame, struct AI *thisAI);

int xWon(struct Game *thisGame, struct AI *thisAI);
int oWon(struct Game *thisGame, struct AI *thisAI);
int catGame(struct Game *thisGame, struct AI *thisAI);

//User input functions
int getIntegerInRange(int min, int max, int inputSize, int *flag); //Contains console output and keyboard input

//Main functions
char getDecision(char yes, char no); //Contains console output and keyboard input

int main(int argc, char* argv[])
{
	//Test arguments
	if(argc == 2 && ((strcmp(argv[1],"1") == 0) || (strcmp(argv[1],"2") == 0)))
	{
		//Intro Message
		printf("\nLets Play a game of Tic-tac-toe!\n");
		printf("This program calculates the board using a %s D array", argv[1]);
	}
	else
	{
		printf("Error in argument\nUsage: %s <dimension(s)>\n", argv[0]);
		exit(2);
	}
	
	//Attributes
	struct AI playerO_AI;
	struct Game tictactoe_Game;
	
	//Random Attributes
	time_t t;
	srand((unsigned) time(&t));

	//Loop while user agrees
	char repeat = 'y';
	while(repeat == 'y' || repeat == 'Y')
	{
		//Initialize AI
		construct_AI(&playerO_AI, EASY);
		
		//Initialize Game with the number of dimensions command line argument. ie: 1 or 2 only
		construct_Game(&tictactoe_Game, argv[1]);

		//Main Menu
		mainMenu(&playerO_AI, &tictactoe_Game); //Might need to pass the structs
		
		//Output Results
		outPutResults_Game(&tictactoe_Game);
		
		//Get decision to repeat program
		repeat = getDecision('y', 'n');
	}

	//Exit Message
	printf("\n\nThanks for playing!\n");
	
	//Free memory
	int i;
	for(i = 0; i < LOCATION_SUBSET; i++)
	{
		free(tictactoe_Game.board[i]);
	}
	free(tictactoe_Game.board);
	
	return 0;
}

int construct_AI(struct AI *thisAI, int difficulty)
{
	//Sets the AI to use
	thisAI ->  currentDifficulty = difficulty;

	//Sets initial stats
	thisAI ->  numGamesWon = 0;
	thisAI ->  numGamesLost = 0;
	thisAI ->  numGamesTied = 0;
	return 0;
}

int construct_Game(struct Game *thisGame, char *dimensions)
{
	//Determine which board to create and set the necessary attributes
	if(strcmp(dimensions,"1") == 0) // 1D array board
	{
		//Set board attributes
		thisGame -> numDimensions = 1;
		thisGame -> numColumns = 9;
		thisGame -> numRows = 1;
	}
	else
	{
		//Set board attributes
		thisGame -> numDimensions = 2;
		thisGame -> numColumns = 3;
		thisGame -> numRows = 3;
	}
	
	int i, j;
	int columns = (thisGame -> numColumns);
	int rows = (thisGame -> numRows);
	//Provide memory for the board and initialize each board element
	thisGame -> board = (int**)malloc(columns * sizeof(int));
	for(i = 0; i < columns; i++)
	{
		thisGame -> board[i] = (int*)malloc(rows * sizeof(int));
		for(j = 0; j < rows; j++)
		{
			thisGame -> board[i][j] = EMPTY;
		}
	}
	
	//Set game stats
	thisGame -> numXWins = 0;
	thisGame -> numOWins = 0;
	thisGame -> numCatGames = 0;
	return 0;
}

int resetBoard_Game(struct Game *thisGame)
{
	int i, j;
	int columns = (thisGame -> numColumns);
	int rows = (thisGame -> numRows);
	for(i = 0; i < columns; i++)
	{
		for(j = 0; j < rows; j++)
		{
			thisGame -> board[i][j] = EMPTY;
		}
	}
	return 0;
}

int outPutResults_Game(struct Game *thisGame)
{
	printf("\n%2d games won by X.", thisGame -> numXWins);
	printf("\n%2d games won by O.", thisGame -> numOWins);
	printf("\n%2d games were tied.", thisGame -> numCatGames);
	return 0;
}

//From grades.c
char getDecision(char yes, char no)
{
	char result;
	printf("\nWould you like to repeat the program? (%c/%c)\n", yes, no);
	result = getchar();
	while (getchar() != '\n');
	return result;
}

int mainMenu(struct AI *thisAI, struct Game *thisGame)
{
	int numberOfOptions = 3;
	int input;
	int flag;
	int loopAgain = 1;
	while(loopAgain)
	{
		flag = 1;
		while(flag)
		{
			//Output Menu Options
			printf("\n\nMain Menu\nSelect one of the following options...\n");
			printf("(1): Game Play\n");
			printf("(2): AI Settings\n");
			printf("(3): AI Game Stats\n");
			printf("(0): Exit Main Menu\n");

			//Ask for Input
			printf("\nEnter an integer between 0 and %d\n", numberOfOptions);
		
			//Get input
			input = getIntegerInRange(0, numberOfOptions, 10, &flag);
			if(flag) printf("Invalid input. Please try again.\n");
		}

		//Switch (input)
		switch(input)
		{
			case 1:
				while(gamePlay(thisAI, thisGame));
				resetBoard_Game(thisGame);
				break;
			case 2:
				settings_AI(thisAI);
				break;
			case 3:
				evaluate_AI(thisAI);
				break;
			case 0:
				loopAgain = 0;
				break;
		}
	}
	return 0;
} //mainMenu()

//Modified from savings.c
int getIntegerInRange(int min, int max, int inputSize, int *flag)
{
	int result = 0;
	
	char input[inputSize];
	int index;
	
	//Get input
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

int gamePlay(struct AI *thisAI, struct Game *thisGame)
{
	//Returns true to the containing while loop if more moves are left to play
	int loopFlag = 0;

	//Print the tic-tac-toe board
	printf("\n");
	printBoard_Game(thisGame);
	printf("\n");
	
	//Determine Current Game State
	int gameState;
	gameState = determineGameState_Game(thisGame);
	
	//Switch (gameState)
	switch(gameState)
	{
		case WINNING_X_GAME:
			xWon(thisGame, thisAI);
			printf("\nPlayer X has won!\n");
			break;
		case WINNING_O_GAME:
			oWon(thisGame, thisAI);
			printf("\nPlayer O has won!\n");
			break;
		case CAT_GAME:
			catGame(thisGame, thisAI);
			printf("\nCat Game!\n");
			break;
		case MORE_MOVES_LEFT:
			if(isXTurn_Game(thisGame))
			{
				printf("\nPlayer's turn!");
				xTurn_Game(thisGame);
			}
			else
			{
				printf("\nAI's turn!\n");
				oTurn_Game(thisGame, thisAI);
			}
			loopFlag = 1;
			break;
	}
	return loopFlag;
} //gamePlay()

int printBoard_Game(struct Game *thisGame)
{
	//Blank board
	char boardSTR[61] = 
	{
		' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '\n',
		'-', '-', '-', '|', '-', '-', '-', '|', '-', '-', '-', '\n',
		' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '\n',
		'-', '-', '-', '|', '-', '-', '-', '|', '-', '-', '-', '\n',
		' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '\n',
		'\0'
	};

	//Specific array locations for the board
	//These were simply counted from the board string.
	//If I wanted to be more generic I could have included special characters
	//I could have searched for each special character and added it to this array
	int editableLocations[] = {1, 5, 9, 25, 29, 33, 49, 53, 57};
	int editableIndex = 0;
	
	int i, j;
	int columns = (thisGame -> numColumns);
	int rows = (thisGame -> numRows);
	//Edit locations where either an X or O have been places
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			if( (thisGame -> board[j][i]) == X )
				boardSTR[editableLocations[editableIndex]] = 'X';
			else if( (thisGame -> board[j][i]) == O )
				boardSTR[editableLocations[editableIndex]] = 'O';
			
			editableIndex++;
		}
	}

	//Print board
	printf("%s", boardSTR);
	
	return 1;
} // printBoard_Game()

int isXTurn_Game(struct Game *thisGame)
{
	int result = 0;

	int xTotal, oTotal;
	xTotal = oTotal = 0;
	int i, j;
	int columns = (thisGame -> numColumns);
	int rows = (thisGame -> numRows);
	//If there are an equal number of x to o then its x's turn
	for(i = 0; i < columns; i++)
	{
		for(j = 0; j < rows; j++)
		{
			if(thisGame -> board[i][j] == X)
				xTotal++;
			else if(thisGame -> board[i][j] == O)
				oTotal++;
		}
	}

	if(xTotal <= oTotal) //They should only be found as being equal
		result = 1;

	return result;
} // isXTurn_Game()

int determineGameState_Game(struct Game *thisGame)
{
	int columns = (thisGame -> numColumns);
	int rows = (thisGame -> numRows);
	int numHZChecks = 3;
	int column = ((columns / rows) / numHZChecks);
	int row = (rows / columns);

	//Check if X just Won then if O won
	//This needs to be simplified...
	int test, outcome, state;
	for(test = X, outcome = WINNING_X_GAME, state = 0;;test = O, outcome = WINNING_O_GAME)
	{
		//Horizontal and vertical checks
		int n;
		for(n = 0, numHZChecks = 3; n < numHZChecks; n++)
		{
			if( (thisGame -> board[column*n][row*n] == test && thisGame -> board[column*n+1][row*n] == test && thisGame -> board[column*n+2][row*n] == test) ||
				(thisGame -> board[n][0] == test && thisGame -> board[column+n][row] == test && thisGame -> board[column*2+n][row*2] == test))
				state = outcome;
		}
		//Diagonal checks
		if( (thisGame -> board[0][0] == test && thisGame -> board[(column*1)+1][row*1] == test && thisGame -> board[column*2+2][row*2] == test) ||
			(thisGame -> board[column*2][row*2] == test && thisGame -> board[(column*1)+1][row*1] == test && thisGame -> board[2][0] == test))
			state = outcome;

		//Exit if X wins or after we test for O
		if(state == WINNING_X_GAME) break;
		else if(test == O) break;
	}
	//If neither player has won
	if(state == 0)
	{
		//Check if a cat game just happened or if their are still moves left
		int i, j;
		int spaceCount = 0;
		for(i = 0; i < columns; i++)
		{
			for(j = 0; j < rows; j++)
			{
				if( (thisGame -> board[i][j]) == EMPTY )
					spaceCount++;
			}
		}

		if(spaceCount == 0)
			state = CAT_GAME;
		else
			state = MORE_MOVES_LEFT;
	}
	return state;
} // determineGameState_Game()


int xWon(struct Game *thisGame, struct AI *thisAI)
{
	thisGame -> numXWins++;
	thisAI -> numGamesLost++;
	return 0;
}

int oWon(struct Game *thisGame, struct AI *thisAI)
{
	thisGame -> numOWins++;
	thisAI -> numGamesWon++;
	return 0;
}

int catGame(struct Game *thisGame, struct AI *thisAI)
{
	thisAI -> numGamesTied++;
	thisGame -> numCatGames++;
	return 0;
}

int xTurn_Game(struct Game *thisGame)
{
	int columns = (thisGame -> numColumns);
	int rows = (thisGame -> numRows);
	int invalidInput = 1;

	int min = 0;
	int max = 2;
	int maxStringLength = 10; //This can probably be reduced later
	int row, column, flag;
	
	do{
		printf("\nWhere would you like to place your next X?\n");
		//Get Row
		flag = 1;
		while(flag)
		{	
			//Ask for input
			printf("\nInput Row coordinate between %d and %d: ", min, max);
			//Get input
			row = getIntegerInRange(min, max, maxStringLength, &flag);
			//Error message
			if(flag) printf("Invalid input. Please try again.\n");
		}

		//Get Column
		flag = 1;
		while(flag)
		{	
			//Ask for input
			printf("\nInput Column coordinate between %d and %d: ", min, max);
			//Get input
			column = getIntegerInRange(min, max, maxStringLength, &flag);
			//Error message
			if(flag) printf("Invalid input. Please try again.\n");
		}
		
		//Correct coordinates based on current dimensions of tictactoe board
		column = ((columns / rows) / 3)*row + column;
		row = (rows / columns)*row;
		if(thisGame -> board[column][row] == EMPTY)
		{
			thisGame -> board[column][row] = X;
			invalidInput = 0;
		}
		
		if(invalidInput)
			printf("Invalid input. Please select an empty location.\n");
		
	}while(invalidInput);
	
	return 0;
} //xTurn()

int oTurn_Game(struct Game *thisGame, struct AI *thisAI)
{
	int columns = (thisGame -> numColumns);
	int rows = (thisGame -> numRows);
	int i, j;
	int *spots[9]; //There should be up to 9 spots on a tictactoe board
	int numSpotsAvailable = 0;
	int randVal;
	//Find all available spots
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			if( (thisGame -> board[j][i]) == EMPTY )
			{
				spots[numSpotsAvailable] = &(thisGame -> board[j][i]);
				numSpotsAvailable++;
			}
		}
	}
	//Choose spot based on AI difficultly
	switch(thisAI -> currentDifficulty)
	{
		case EASY:
			*spots[0] = O;
			break;
		case MEDIUM:
			randVal = (rand())%numSpotsAvailable;
			*spots[randVal] = O;
			break;
		case HARD:
			randVal = (rand())%numSpotsAvailable;
			*spots[randVal] = O;
			break;
	}
	return 0;
} // oTurn_Game()

int evaluate_AI(struct AI *thisAI)
{
	//Output AI difficulty
	printf("Current difficulty set to ");
	if( (thisAI -> currentDifficulty) == EASY)
		printf("easy.\n");
	if( (thisAI -> currentDifficulty) == MEDIUM)
		printf("medium.\n");
	if( (thisAI -> currentDifficulty) == HARD)
		printf("hard.\n");

	//Output AI Wins, losses, and ties
	printf("\n%2d games won by AI.", thisAI -> numGamesWon);
	printf("\n%2d games lost by AI.", thisAI -> numGamesLost);
	printf("\n%2d games were tied with user.\n", thisAI -> numGamesTied);
	return 0;
}

int settings_AI(struct AI *thisAI)
{
	int numberOfOptions = 3;
	int input;
	int flag = 1;
	while(flag)
	{
		//Output AI Settings Options
		printf("\nAI Settings\nSelect one of following options...\n");
		printf("(1): Set AI to Easy\n");
		printf("(2): Set AI to Medium\n");
		printf("(3): Set AI to Hard\n");
		printf("(0): Exit AI Settings\n");

		//Ask for Input
		printf("\nEnter an integer between 0 and %d\n", numberOfOptions);
		
		//Get input
		input = getIntegerInRange(0, numberOfOptions, 10, &flag);
		if(flag) printf("Invalid input. Please try again.\n");
	}

	//Switch (input)
	switch(input)
	{
		case 1:
			setDifficulty_AI(thisAI, EASY);
			printf("\nAI set to Easy.\n");
			break;
		case 2:
			setDifficulty_AI(thisAI, MEDIUM);
			printf("\nAI set to Medium.\n");
			break;
		case 3:
			setDifficulty_AI(thisAI, HARD);
			printf("\nAI set to Hard.\n");
			break;
		case 0:
			break;
	}
	
	return 0;
} //settings_AI()

int setDifficulty_AI(struct AI *thisAI, int difficulty)
{
	thisAI ->  currentDifficulty = difficulty;
	thisAI -> numGamesWon = 0;
	thisAI -> numGamesLost = 0;
	thisAI -> numGamesTied = 0;
	return 0;
}