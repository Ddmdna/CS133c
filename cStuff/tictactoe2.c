// tictactoe2.c
#include <stdio.h>

//Global Attributes
#define MAX_LOCATIONS 9
#define LOCATION_SUBSET 3

#define WINNING_X_GAME 1
#define WINNING_O_GAME 2
#define CAT_GAME 3
#define MORE_MOVES_LEFT 4

#define X 1
#define O 2

#define EASY 1
#define MEDIUM 2
#define HARD 3

#define DIMENSIONAL 2

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
	int board1D[MAX_LOCATIONS];
	int board2D[LOCATION_SUBSET][LOCATION_SUBSET];

	int numXWins;
	int numOWins;
	int numCatGames;
};

int construct_AI(struct AI *thisAI, int difficulty);
int construct_Game(struct Game *thisGame, int dimensions);
int outPutResults_Game(struct Game *thisGame);
char getDecision(char yes, char no);
int getIntegerInRange(int min, int max, int inputSize, int *flag);
int gamePlay(struct AI *thisAI, struct Game *thisGame);
int printBoard_Game(struct Game *thisGame);
int isXTurn_Game(struct Game *thisGame);
int determineGameState_Game(struct Game *thisGame);
int xWon(struct Game *thisGame, struct AI *thisAI);
int oWon(struct Game *thisGame, struct AI *thisAI);
int catGame(struct Game *thisGame, struct AI *thisAI);
int xTurn_Game(struct Game *thisGame);
int oTurn_Game(struct Game *thisGame, struct AI *thisAI);
int evaluate_AI(struct AI *thisAI);
int settings_AI(struct AI *thisAI);
int setDifficulty_AI(struct AI *thisAI, int difficulty);
int mainMenu(struct AI *thisAI, struct Game *thisGame);
int resetBoard_Game(struct Game *thisGame, int dimensions);

int main()
{
	//Attributes
	struct AI playerO_AI;
	struct Game tictactoe_Game;

	//Intro Message
	printf("\nLets Play a game of Tic-tac-toe!\n");
	printf("This program calculates the board using a %d D array", DIMENSIONAL);
	

	//Loop while user agrees
	char repeat = 'y';
	while(repeat == 'y' || repeat == 'Y')
	{
		//Initialize AI
		construct_AI(&playerO_AI, EASY);
		
		//Initialize Game
		construct_Game(&tictactoe_Game, DIMENSIONAL);

		//Main Menu
		mainMenu(&playerO_AI, &tictactoe_Game); //Might need to pass the structs
		
		//Output Results
		outPutResults_Game(&tictactoe_Game);
		
		//Get decision to repeat program
		repeat = getDecision('y', 'n');
	}
	

	//Exit Message
	

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


int construct_Game(struct Game *thisGame, int dimensions)
{
	//Initialize both arrays
	int i, j;
	for(i = 0; i < MAX_LOCATIONS; i++)
	{
		thisGame -> board1D[i] = 0;
	}
	for(i = 0; i < LOCATION_SUBSET; i++)
	{
		for(j = 0; j < LOCATION_SUBSET; j++)
		{
			thisGame -> board2D[i][j] = 0;
		}
	}
	//Set the dimension so we know what array to use for each Project Component
	thisGame -> numDimensions = dimensions;

	//Set game stats
	thisGame -> numXWins = 0;
	thisGame -> numOWins = 0;
	thisGame -> numCatGames = 0;
	return 0;
}

int resetBoard_Game(struct Game *thisGame, int dimensions)
{
	int i, j;
	if(dimensions = 1)
	{
		for(i = 0; i < MAX_LOCATIONS; i++)
		{
			thisGame -> board1D[i] = 0;
		}
	}
	else{
		for(i = 0; i < LOCATION_SUBSET; i++)
		{
			for(j = 0; j < LOCATION_SUBSET; j++)
			{
				thisGame -> board2D[i][j] = 0;
			}
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
			printf("\nMain Menu\nSelect one of the following options...\n");
			printf("(1): Game Play\n");
			printf("(2): AI Settings\n");
			printf("(3): AI Game Stats\n");
			printf("(0): Exit Main Menu\n");

			//Ask for Input
			printf("Enter an integer between 0 and %d\n", numberOfOptions);
		
			//Get input
			input = getIntegerInRange(0, numberOfOptions, 10, &flag);
			if(flag) printf("Invalid input. Please try again.\n");
		}


		//Switch (input)
		switch(input)
		{
			case 1:
				while(gamePlay(thisAI, thisGame));
				resetBoard_Game(thisGame, DIMENSIONAL);
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
			break;
		case WINNING_O_GAME:
			oWon(thisGame, thisAI);
			break;
		case CAT_GAME:
			catGame(thisGame, thisAI);
			break;
		case MORE_MOVES_LEFT:
			if(isXTurn_Game(thisGame))
				xTurn_Game(thisGame);
			else
				oTurn_Game(thisGame, thisAI);

			loopFlag = 1;
			break;
	}
	return loopFlag;
} //gamePlay()


int printBoard_Game(struct Game *thisGame)
{
	//Blank board
	char board[61] = 
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
	//If i wanted to be more generic I could have included special characters
	//I could have searched for each special character and added it to this array
	int editableLocations[] = {1, 5, 9, 25, 29, 33, 49, 53, 57};
	int editableIndex = 0;

	//Change blank spaces in board to X or O where neccesarry
	if(thisGame -> numDimensions = 1)
	{
		int i;
		for(i = 0; i < MAX_LOCATIONS; i++)
		{
			if( (thisGame -> board1D[i]) == X )
				board[editableLocations[editableIndex]] = 'X';
			else if( (thisGame -> board1D[i]) == O )
				board[editableLocations[editableIndex]] = 'O';

			editableIndex++;
		}
	}
	else
	{
		int i, j;
		for(i = 0; i < LOCATION_SUBSET; i++)
		{
			for(j = 0; j < LOCATION_SUBSET; j++)
			{
				if( (thisGame -> board2D[i][j]) == X )
					board[editableLocations[editableIndex]] = 'X';
				else if( (thisGame -> board2D[i][j]) == O )
					board[editableLocations[editableIndex]] = 'O';

				editableIndex++;
			}
		}
	}

	//Print board
	printf("%s", board);
	return 1;
} // printBoard_Game()


int isXTurn_Game(struct Game *thisGame)
{
	int result = 0;

	int xTotal, oTotal;
	int i, j;
	//If there are an equal number of x to o then its x's turn
	if(thisGame -> numDimensions = 1)
	{
		for(i = 0; i < MAX_LOCATIONS; i++)
		{
			if(thisGame -> board1D[i] == X)
				xTotal++;
			else if(thisGame -> board1D[i] == O)
				oTotal++;
		}
	}
	else
	{
		for(i = 0; i < LOCATION_SUBSET; i++)
		{
			for(j = 0; j < LOCATION_SUBSET; j++)
			{
				if(thisGame -> board2D[i][j] == X)
					xTotal++;
				else if(thisGame -> board2D[i][j] == O)
					oTotal++;
			}
		}
	}

	if(xTotal <= oTotal) //They should only be found as being equal
		result = 1;

	return result;
} // isXTurn_Game()


int determineGameState_Game(struct Game *thisGame)
{
	int state = 0;
	if(thisGame -> numDimensions = 1)
	{
		//Check if X just Won then if O won
		int test, outcome;
		for(test = X, outcome = WINNING_X_GAME;;test = O, outcome = WINNING_O_GAME)
		{
			if(thisGame -> board1D[0] == test && thisGame -> board1D[1] == test && thisGame -> board1D[2] == test)
				state = outcome;
			else if(thisGame -> board1D[3] == test && thisGame -> board1D[4] == test && thisGame -> board1D[5] == test)
				state = outcome;
			else if(thisGame -> board1D[6] == test && thisGame -> board1D[7] == test && thisGame -> board1D[8] == test)
				state = outcome;
			else if(thisGame -> board1D[0] == test && thisGame -> board1D[3] == test && thisGame -> board1D[6] == test)
				state = outcome;
			else if(thisGame -> board1D[1] == test && thisGame -> board1D[4] == test && thisGame -> board1D[7] == test)
				state = outcome;
			else if(thisGame -> board1D[2] == test && thisGame -> board1D[5] == test && thisGame -> board1D[8] == test)
				state = outcome;
			else if(thisGame -> board1D[0] == test && thisGame -> board1D[4] == test && thisGame -> board1D[8] == test)
				state = outcome;
			else if(thisGame -> board1D[2] == test && thisGame -> board1D[4] == test && thisGame -> board1D[6] == test)
				state = outcome;

			//Exit if X wins or after we test for O
			if(state == WINNING_X_GAME) break;
			else if(test == O) break;
		}

		//Continue if no state has been found so far
		if(state == 0)
		{
			//Check if a cat game just happened or if their are still moves left
			int i, spaceCount;
			for(i = 0, spaceCount = 0; i < MAX_LOCATIONS; i++)
			{
				if( (thisGame -> board1D[i]) == 0 )
					spaceCount++;
			}

			if(spaceCount == 0)
				state = CAT_GAME;
			else
				state = MORE_MOVES_LEFT;
		}
	} // end 1D testing....
	else
	{
		//Check if X just Won then if O won
		int test, outcome;
		for(test = X, outcome = WINNING_X_GAME;;test = O, outcome = WINNING_O_GAME)
		{
			if(thisGame -> board2D[0][0] == test && thisGame -> board2D[1][0] == test && thisGame -> board2D[2][0] == test)
				state = outcome;
			else if(thisGame -> board2D[0][1] == test && thisGame -> board2D[1][1] == test && thisGame -> board2D[2][1] == test)
				state = outcome;
			else if(thisGame -> board2D[0][2] == test && thisGame -> board2D[1][2] == test && thisGame -> board2D[2][2] == test)
				state = outcome;
			else if(thisGame -> board2D[0][0] == test && thisGame -> board2D[0][1] == test && thisGame -> board2D[0][2] == test)
				state = outcome;
			else if(thisGame -> board2D[1][0] == test && thisGame -> board2D[1][1] == test && thisGame -> board2D[1][2] == test)
				state = outcome;
			else if(thisGame -> board2D[2][0] == test && thisGame -> board2D[2][1] == test && thisGame -> board2D[2][2] == test)
				state = outcome;
			else if(thisGame -> board2D[0][0] == test && thisGame -> board2D[1][1] == test && thisGame -> board2D[2][2] == test)
				state = outcome;
			else if(thisGame -> board2D[0][2] == test && thisGame -> board2D[1][1] == test && thisGame -> board2D[2][0] == test)
				state = outcome;

			//Exit if X wins or after we test for O
			if(state == WINNING_X_GAME) break;
			else if(test == O) break;
		}

		//Continue if no state has been found so far
		if(state == 0)
		{
			//Check if a cat game just happened or if their are still moves left
			int i, j;
			int spaceCount = 0;
			for(i = 0; i < LOCATION_SUBSET; i++)
			{
				for(j = 0; j < LOCATION_SUBSET; j++)
				{
					if( (thisGame -> board2D[i][j]) == 0 )
						spaceCount++;
				}
			}

			if(spaceCount == 0)
				state = CAT_GAME;
			else
				state = MORE_MOVES_LEFT;
		}
	} // end 2d testing....
	return state;
} // determineGameState_Game()


int xWon(struct Game *thisGame, struct AI *thisAI)
{
	thisGame -> numXWins++;
	thisAI -> numGamesLost++;
	printf("\nPlayer X has won!\n");
	return 0;
}


int oWon(struct Game *thisGame, struct AI *thisAI)
{
	thisGame -> numOWins++;
	thisAI -> numGamesWon++;
	printf("\nPlayer O has won!\n");
	return 0;
}


int catGame(struct Game *thisGame, struct AI *thisAI)
{
	
	thisAI -> numGamesTied++;
	thisGame -> numCatGames++;
	printf("\nCat Game!\n");
	return 0;
}


int xTurn_Game(struct Game *thisGame)
{
	int invalidInput = 1;

	int min = 0;
	int max = 2;
	int maxStringLength = 10; //This can probably be reduced later
	int row, column, flag;
	
	printf("\nPlayer's turn!");
	do{
		//Get Row
		flag = 1;
		while(flag)
		{	
			//Ask for input
			printf("\nWhere would you like to place your next X?\nRow(%d-%d): ", min, max);

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
			printf("\nWhere would you like to place your next X?\ncolumn(%d-%d): ", min, max);

			//Get input
			column = getIntegerInRange(min, max, maxStringLength, &flag);

			//Error message
			if(flag) printf("Invalid input. Please try again.\n");
		}

		//Check if the input matches an empty space in the 1D or 2D board(Depending on thisGame)
		if(thisGame -> numDimensions = 1)
		{
			if(thisGame -> board1D[row*3 + column] == 0)
			{
				thisGame -> board1D[row*3 + column] = X;
				invalidInput = 0;
			}
		}
		else
		{
			if(&thisGame -> board2D[row][column] == 0)
			{
				thisGame -> board2D[row][column] = X;
				invalidInput = 0;
			}
		}

		if(invalidInput)
			printf("\nInvalid input. Please select an empty location.\n");
	}while(invalidInput);
	
	return 0;
} //xTurn()


int oTurn_Game(struct Game *thisGame, struct AI *thisAI)
{
	printf("\nAI's turn!\n");
	int i, j;
	if(thisGame -> numDimensions = 1)
	{
		for(i = 0; i < MAX_LOCATIONS; i++)
		{
			if( (thisGame -> board1D[i]) == 0 )
			{
				thisGame -> board1D[i] = O;
				break;
			}
		}
	}
	else
	{
		for(i = 0; i < LOCATION_SUBSET; i++)
		{
			for(j = 0; j < LOCATION_SUBSET; j++)
			{
				if( (thisGame -> board2D[i][j]) == 0 )
				{
					thisGame -> board2D[i][j] = O;
					break;
				}
			}
		}
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
	return 0;
}