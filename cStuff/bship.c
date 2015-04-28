#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct to hold a board worth of info, expecting two per battleship game
struct board
{
	int shipCount;
	int shipsSunk;
	
	//max health of each ship by "ship id"
	int *shipHealth;
	//hits so far of each ship by "ship id"
	int *shipHits;
	
	const int BOARD_SIZE;
	char *grid;
};

int loadBoard(char *p1File, struct board *p1Board, char *p2File, struct board *p2Board);
void printBoard(struct board *b);
int shoot(struct board* b, int col, int row);
int checkWin(struct board *b);
int quickTests();

//battleship!
int main(int argc, char *argv[])
{
	//do some quick tests on simple functionality
	quickTests();
	
	
	
	return 0;	
}

//read from file to fill in board for a player
int loadBoard(char *p1File, struct board *p1Board, char *p2File, struct board *p2Board)
{
//int readFile(char *fileName, char **str)
	int result = 0;
	
	const int MAX_FILE_SIZE = 109;
	FILE *fp = fopen(p1File, "r");
	
	if(fp == NULL)
	{
		printf("Oh no! File (%s) not found :'(", p1File);
		result = 1;
	}
	else
	{
		
			p1Board->grid = (char *) malloc(MAX_FILE_SIZE * sizeof(char));
			if(p1Board->grid == NULL)
			{
				printf("Oh no! The OS is mean and did not give me memory :'(");
				result = 2;
			}
			else
			{
				
				fread(p1Board->grid, MAX_FILE_SIZE, 1, fp);
			}
	}
	
	fclose(fp);
	
	return result;
}

//
void printBoard(struct board *b)
{
	for(int i = 0; i < (b->BOARD_SIZE + 1); i++)
	printf("%s\n", b->grid);
}

//see if shooting a position will hit something
int shoot(struct board* b, int col, int row)
{
	int result = 0;
	
	/*
		start at beginning of single dimension array,
		jump ahead by a number of rows,
		then jump ahead by number of columns
	*/
	char *point = ((b->grid) + ((b->BOARD_SIZE + 1) * row) + (col));
	
	if(*point != 0)
	{
		
		result = 1;
	}
	
	return result;
}

//check if some board has won against this board
int checkWin(struct board *b)
{
	return (b->shipsSunk >= b->shipCount);
}

int quickTests()
{
	int b1ShipHealth[] = {0, 2, 3, 3, 4, 5};
	int b2ShipHealth[] = {0, 2, 3, 3, 4, 5};
	int b1ShipHits[] = {0, 0, 0, 0, 0, 0};
	int b2ShipHits[] = {0, 0, 0, 0, 0, 0};
	int *b1ShipHealthPtr = b1ShipHealth;
	int *b2ShipHealthPtr = b2ShipHealth;
	int *b1ShipHitsPtr = b1ShipHits;
	int *b2ShipHitsPtr = b2ShipHits;
	
	//printf("b1ShipHealthPtr: %p, value: %d", b1ShipHealthPtr, *(b1ShipHealthPtr + 2));
	
	struct board b1 = {5, 5, b1ShipHealthPtr, b1ShipHitsPtr, 10, NULL};
	struct board b2 = {5, 0, b2ShipHealthPtr, b2ShipHitsPtr, 10, NULL};
	
	//test that ships have correct amount of max health
	for(int i = 0; i < 6; ++i)
	{
		printf("max health for ship %d: %d\n", i, (b1.shipHealth)[i]);
	}
	
	//test that board is properly created
	printf("BOARD_SIZE: %d\n", b1.BOARD_SIZE);
	
	//test that grid is loaded with file contents
	char fName1[] = "board1.txt";
	char fName2[] = "board2.txt";
	loadBoard(fName1, &b1, fName2, &b2);
	printf("Board printed manually:\n%s\n", b1.grid);
	
	//test that printBoard is working
	printf("Board printed with printBoard:\n");
	printBoard(&b1);
	
	//test that shoot function returns whether a shot was successful
	printf("shot at 4, 3: %d\n", shoot(&b1, 3, 2)); //should be a hit in board 1?

	//test if win works
	
	int b1Lose = checkWin(&b1);
	int b2Lose = checkWin(&b2);
	printf("Player1 loss status: %d\n", b1Lose);
	printf("Player2 loss status: %d\n", b2Lose);
	
	//test if loadBoard works
	
	//test if shoot works
	
	return 0;
}