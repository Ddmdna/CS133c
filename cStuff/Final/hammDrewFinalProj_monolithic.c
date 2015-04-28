// hammDrewFinalProj_monolithic.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
time_t t;


//==================================================================================================================
//From MyIO.c
const int TEST_LINE_MAX = 76;
const char START_CHAR = '_';
const char END_CHAR = '^';

const int INVALID_INPUT = -1;
const int VALID_INPUT = 1;
const int UNCHANGED = 0;
const int CHANGED = 1;
//==================================================================================================================


//==================================================================================================================
//From ConwaysGameOfLife.c
const int MIN_BOARD_WIDTH = 10;
const int MIN_BOARD_HEIGHT = 10;
const int MIN_STEP = 1;

const int MAX_BOARD_WIDTH = 999;
const int MAX_BOARD_HEIGHT = 999;
const int MAX_STEP = 9999;

const int NONLIVING = 0;
const int DEAD_NEXT_TURN = -1;
const int LIVING = 1;
const int BORN_NEXT_TURN = 2;

struct CGoL{
	int currentStep;
	int maxStep;
	int boardWidth;
	int boardHeight;
	int **board;
};

int** cgol_initializeBoard(int boardWidth, int boardHeight);
void cgol_freeBoard(int **board, int boardHeight);
int changeBoardWidth(int *attribute);
int changeBoardHeight(int *attribute);
int changeMaxStep(int *attribute);
void printBoard(struct CGoL *cgol, int visabilityModifier);
void test_CGoLBoardInitialized(struct CGoL *cgol);
void test_PrintCGoLSimpleAttributes(struct CGoL *cgol);
void resetBoard(int **board, int boardWidth, int boardHeight);
int loadSeed(int **seed, int solutionWidth, int solutionHeight, int **board, int boardWidth, int boardHeight);
int getFutureState(int currentState, int sumLive);
int getFutureCenterState(int **board, int startH, int startW);
void setFutureBoardState(int **board, int boardWidth, int boardHeight);
void updateBoardState(int **board, int boardWidth, int boardHeight);
int getFitness(int **board, int boardWidth, int boardHeight, int fitnessSpecifier);
//==================================================================================================================


//==================================================================================================================
//From GeneticAlgorithm.c
const int MAX_POPULATION = 999;
const int MAX_SOLUTION_SIZE = 99;
const int MAX_GENERATION = 999;
const int MAX_MUTATION_RATE = 100;
const int MAX_FITNESS_SPECIFIER = 3;
const int MAX_SELECTION_SPECIFIER = 3;
const int MAX_CROSSOVER_SPECIFIER = 3;

const int MIN_POPULATION = 1;
const int MIN_SOLUTION_SIZE = 1;
const int MIN_GENERATION = 1;
const int MIN_MUTATION_RATE = 0;
const int MIN_FITNESS_SPECIFIER = 1;
const int MIN_SELECTION_SPECIFIER = 1;
const int MIN_CROSSOVER_SPECIFIER = 1;


struct Solution{
	int fitness;
	int **seed;
};


struct GA{
	int currentSolution;
	int maxSolution;
	int solutionWidth;
	int solutionHeight;
	int currentGeneration;
	int maxGeneration;
	int mutationRate;
	int fitnessSpecifier;
	int selectionSpecifier;
	int crossoverSpecifier;
	struct Solution bestSolution;
	struct Solution *population;
};


int** ga_initializeBestSolution(int solutionWidth, int solutionHeight, char *seedFileName);
struct Solution* ga_initializePopulation(int maxSolution, int solutionWidth, int solutionHeight);
void ga_freePopulation(struct Solution *population, int maxSolution, int solutionHeight);
struct Solution* ga_initializeSolution(int solutionWidth, int solutionHeight);
void ga_freeSolution(struct Solution *solution, int solutionHeight);
struct Solution* copySolution(struct Solution *solution, int solutionWidth, int solutionHeight);
int changePopSize(int *attribute);
int changeSolutionWidth(int *attribute);
int changeSolutionHeight(int *attribute);
int changeMaxGeneration(int *attribute);
int changeMutationRate(int *attribute);
int changeFitnessSpecifier(int *attribute);
int changeSelectionSpecifier(int *attribute);
int changeCrossoverSpecifier(int *attribute);
void test_GASolutionsInitiallized(struct GA *ga);
void test_PrintGASimpleAttributes(struct GA *ga);
void printSolution(struct Solution *solution, int solutionHeight, int solutionWidth, int lineModifier);
int selection_Roulette(struct Solution *population, int maxSolution);
struct Solution* crossover(struct Solution *parentA, struct Solution *parentB, int solutionWidth, int solutionHeight);
//==================================================================================================================


//==================================================================================================================
//From Control.c
struct Settings{
	int viewWidth;
	int viewHeight;
	char settingsFileName[100];
	char seedFileName[100];
};
//==================================================================================================================


//==================================================================================================================
//From GenericMenu.c
struct Menu{
	int numberOfFunctions;
	char *menuName;
	char **functionDescriptions;
};

void outputMenu(struct Menu *menu);
//==================================================================================================================


//==================================================================================================================
//From Optimization.c
void mutatePopulation(struct Solution *population, int maxSolution, int solutionWidth, int solutionHeight, int mutationRate);
int bitMutationCheck(int mutationRate);
void sortPopulationByFitness(struct Solution *population, int maxSolution);

int runCGoL(struct Solution *solution, int solutionWidth, int solutionHeight, int fitnessSpecifier, struct CGoL *cgol, int visabilityModifier);

const int INITIAL_MUTATION_RATE = 20;
//==================================================================================================================


//==================================================================================================================
//From Run.c
const int EXIT_CONDITION = -1;
const int SKIP_CONDITION = -2;
const int debugRun = 0;


int mainMenu(struct Menu *menu);
int settingsMenu_GA(struct Menu *menu, struct GA *ga);
int settingsMenu_CGoL(struct Menu *menu, struct CGoL *cgol);
//==================================================================================================================


//==================================================================================================================
//From RunCGoL.c
int runCGoL(struct Solution *solution, int solutionWidth, int solutionHeight, int fitnessSpecifier, struct CGoL *cgol, int visabilityModifier);
//==================================================================================================================


//==================================================================================================================
//From hammDrewFinalProj.c
int debugMode = 0;

void test_FileCharacterOutput(FILE *fp);
void test_FileNamesFromBaseFile(char *settingsFileName, char *seedFileName);
void test_StructValuesInitialized(struct Settings *settings, struct CGoL *cgol, struct GA *ga);

const int MAX_FILE_NAME = 100;
const int MAX_VIEW_WIDTH = 100;
const int MAX_VIEW_HEIGHT = 50;

const char defaultFileName[] = "Saved_Default.txt";
//==================================================================================================================


int main(int argc, char* argv[])
{
	//Random attribute
	srand((unsigned) time(&t));
	
	//File attributes
	FILE *fp;
	char *settingsFileName;
	char *seedFileName;
	
	
	//================================================================
	//Evaluate command line arguments and open the relevant file
	switch(argc){
		case 1:
			fp = fopen(defaultFileName, "r");
			break;
		case 2:
			fp = fopen(argv[1], "r");
			break;
		default:
			printf("Error in argument count\nUsage: %s <Saved_File>", argv[0]);
			printf("\nargc = %d", argc);
			exit(2);
	}
	//================================================================
	//Test the file for containing characters
	if(debugMode) test_FileCharacterOutput(fp);
	
	
	//================================================================
	//Read from the base file to get the names of the secondary files
	settingsFileName = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	seedFileName = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	fscanf(fp, "%s %s", settingsFileName, seedFileName);
	fclose(fp);
	//================================================================
	
	
	//================================================================
	//Ensure that the file names have valid lengths
	if((sizeof(settingsFileName) == 0 || sizeof(seedFileName) == 0)){
		printf("Invalid file input.");
        exit(2);
    } else if(sizeof(settingsFileName) == 50 || sizeof(seedFileName) == 50){
		printf("File names too large.");
        exit(2);
	}
	//================================================================
	//Test that the file names were read correctly
	if(debugMode) test_FileNamesFromBaseFile(settingsFileName, seedFileName);
	
	
	//================================================================
	//Intro Message
	printf("\nFile: \t%s\nTitle: \t%s\nBy: \t%s\nDate: \t%s\nClass: \t%s\n\n", argv[0], "Final Project", "Drew Hamm", "03/18/2015", "CS 133c");
	printf("This program is designed from Conway's Game of Life.(CGoL)\n");
	printf("In addition, a Genetic Algorithm(GA) is used to find optimal seeds.\n");
	printf("Options are provided to change the game environment as well as the behaviour of the GA.\n\n");
	
	printf("Hit enter to begin...\n");
	while(getchar() != '\n');
	//================================================================
	
	
	//================================================================
	//Create structs
	struct Settings settings;
	struct CGoL cgol;
	struct GA ga;
	
	//Open settings file
	fp = fopen(settingsFileName, "r");
	rewind(fp);
	
	//Initialize structs values
	//Settings
	strcpy(settings.settingsFileName, settingsFileName);
	strcpy(settings.seedFileName, seedFileName);
	fscanf (fp, "%d", &settings.viewWidth);
	fscanf (fp, "%d", &settings.viewHeight);
	//CGoL
	cgol.currentStep = 0;
	fscanf (fp, "%d", &cgol.maxStep);
	fscanf (fp, "%d", &cgol.boardWidth);
	fscanf (fp, "%d", &cgol.boardHeight);
	//GA
	ga.currentSolution = 0;
	fscanf (fp, "%d", &ga.maxSolution);
	fscanf (fp, "%d", &ga.solutionWidth);
	fscanf (fp, "%d", &ga.solutionHeight);
	ga.currentGeneration = 0;
	fscanf (fp, "%d", &ga.maxGeneration);
	fscanf (fp, "%d", &ga.mutationRate);
	fscanf (fp, "%d", &ga.fitnessSpecifier);
	fscanf (fp, "%d", &ga.selectionSpecifier);
	fscanf (fp, "%d", &ga.crossoverSpecifier);
	fclose(fp);
	
	//Initialize cgol.board
	cgol.board = cgol_initializeBoard(cgol.boardWidth, cgol.boardHeight);
	
	//Initialize ga.bestSolution
	ga.bestSolution.seed = ga_initializeBestSolution(ga.solutionWidth, ga.solutionHeight, settings.seedFileName);

	//Initialize ga.population
	ga.population = ga_initializePopulation(ga.maxSolution, ga.solutionWidth, ga.solutionHeight);
	
	//================================================================
	//Check if each struct was initialized correctly
	if(debugMode) {
		test_StructValuesInitialized(&settings, &cgol, &ga);
		test_CGoLBoardInitialized(&cgol);
		test_GASolutionsInitiallized(&ga);
	}
	
	
	//================================================================
	//For readability I moved this to Run.c
	//I have a new debugMode this function which is currently included in run.c
	run(&settings, &cgol, &ga);
	//================================================================
	
	
	
	//================================================================
	//Exit Message
	printf("\n\nThis concludes the program.\n");
	//================================================================
	
	
	//================================================================
	//File output
	//Not sure if I need this at this point...
	//================================================================
}

void test_FileCharacterOutput(FILE *fp){
	int c;
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_FileCharacterOutput\n\n");
	while(1){
		c = fgetc(fp);
		if(feof(fp)){
			break;
		}
		if(c != '\r') printf("[%c]", c);
   }
   printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
   rewind(fp);
}

void test_FileNamesFromBaseFile(char *settingsFileName, char *seedFileName){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_FileNamesFromBaseFile\n\n");
	printf("Settings File Name: \"%s\"\nSeed File Name: \"%s\"\n", settingsFileName, seedFileName);
	printf("strlen(settingsFileName): %d\nstrlen(seedFileName): %d", strlen(settingsFileName), strlen(seedFileName));
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}

void test_StructValuesInitialized(struct Settings *settings, struct CGoL *cgol, struct GA *ga){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_settingStructInit\n\n");
	printf("settingsFileName: %s", settings -> settingsFileName);
	printf("\nseedFileName: %s", settings -> seedFileName);
	printf("\nviewWidth: %d", settings -> viewWidth);
	printf("\nviewHeight: %d", settings -> viewHeight);
	
	printf("\n\ncurrentStep: %d", cgol -> currentStep);
	printf("\nmaxStep: %d", cgol -> maxStep);
	printf("\nboardWidth: %d", cgol -> boardWidth);
	printf("\nboardHeight: %d", cgol -> boardHeight);
	
	printf("\n\ncurrentSolution: %d", ga -> currentSolution);
	printf("\nmaxSolution: %d", ga -> maxSolution);
	printf("\nsolutionWidth: %d", ga -> solutionWidth);
	printf("\nsolutionHeight: %d", ga -> solutionHeight);
	printf("\ncurrentGeneration: %d", ga -> currentGeneration);
	printf("\nmaxGeneration: %d", ga -> maxGeneration);
	printf("\nmutationRate: %d", ga -> mutationRate);
	printf("\nfitnessSpecifier: %d", ga -> fitnessSpecifier);
	printf("\nselectionSpecifier: %d", ga -> selectionSpecifier);
	printf("\ncrossoverSpecifier: %d", ga -> crossoverSpecifier);
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}
//==================================================================================================================


//==================================================================================================================
//From MyIO.c
void printSpacedCharLine(char character, int numberOfTimes){
	printf("\n");
	int i;
	for(i = 0; i < numberOfTimes; i++){
		printf("%c", character);
	}
	printf("\n");
}

int getPositiveIntInRange(int bufferSize, int min, int max){
	int result = -1;
	char *buffer = (char*)calloc(bufferSize, sizeof(char));

	fgets(buffer, bufferSize, stdin);
	int check = sscanf(buffer, "%d", &result);

	if(strlen(buffer) == (bufferSize-1) && buffer[bufferSize-2] != '\n'){
		result = INVALID_INPUT;
		while(getchar() != '\n');
	}
	
	//Checks for lack of integers
	if(check != VALID_INPUT)
		result = INVALID_INPUT;
	
	//Checks for a result out of range
	if(result < min || result > max)
		result = INVALID_INPUT;

	free(buffer);
	return result;
}

int getPositiveChangedIntInRange(int *currentValue, int bufferSize, int min, int max){
	int check;
	int result = getPositiveIntInRange(bufferSize, min, max);
	
	if(result == INVALID_INPUT || result == *currentValue){
		check = UNCHANGED;
	} else{
		*currentValue = result;
		check = CHANGED;
	}
	return check;
}

void requestNewValueForAttribute(char* attributeName, int currentValue, int min, int max){
	printf("\n%s is currently set to (%d)\n", attributeName, currentValue);
	printf("Enter a value in the range (%d-%d): ", min, max);
}
//==================================================================================================================


//==================================================================================================================
//From ConwaysGameOfLife.c
//Initialize and return a two dimensional array to be used as the board for the CGoL struct
int** cgol_initializeBoard(int boardWidth, int boardHeight){
	int **board = (int**)calloc(boardHeight, sizeof(int));
	int h;
	for(h = 0; h < boardHeight; h++){
		board[h] = (int*)calloc(boardWidth, sizeof(int));
	}
	return board;
}


void cgol_freeBoard(int **board, int boardHeight){
	int h;
	for(h = 0; h < boardHeight; h++){
		free(board[h]);
	}
	free(board);
}

void resetBoard(int **board, int boardWidth, int boardHeight){
	int h, w;
	for(h = 0; h < boardHeight; h++){
		for(w = 0; w < boardWidth; w++){
			board[h][w] = 0;
		}
	}
}

int loadSeed(int **seed, int solutionWidth, int solutionHeight, int **board, int boardWidth, int boardHeight){
	//Check to see if the seed can fit
	if(solutionWidth >= boardWidth || solutionHeight >= boardHeight) return 0;
	
	//Determine initial coordinates
	int startH = ((boardHeight-solutionHeight)/2);
	int startW = ((boardWidth-solutionWidth)/2);
	int h, w;
	for(h = 0; h < solutionHeight; h++ ){
		for(w = 0; w < solutionWidth; w++){
			board[startH+h][startW+w] = seed[h][w];
		}
	}
	return 1;
}

int changeBoardWidth(int *attribute){
	requestNewValueForAttribute("Board width", *attribute, MIN_BOARD_WIDTH, MAX_BOARD_WIDTH);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_BOARD_WIDTH, MAX_BOARD_WIDTH);
	return changed;
}

int changeBoardHeight(int *attribute){
	requestNewValueForAttribute("Board height", *attribute, MIN_BOARD_HEIGHT, MAX_BOARD_HEIGHT);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_BOARD_HEIGHT, MAX_BOARD_HEIGHT);
	return changed;
}

int changeMaxStep(int *attribute){
	requestNewValueForAttribute("Max step", *attribute, MIN_STEP, MAX_STEP);
	int changed = getPositiveChangedIntInRange(attribute, 6, MIN_STEP, MAX_STEP);
	return changed;
}

void printBoard(struct CGoL *cgol, int visabilityModifier){
	int h, w;
	if(visabilityModifier == 1) printSpacedCharLine('=', (cgol -> boardWidth));
	else printf("\n");
	for(h = 0; h < (cgol -> boardHeight); h++){
		for(w = 0; w < (cgol -> boardWidth); w++){
			if(visabilityModifier == 1){
				if((cgol -> board[h][w]) == 0) printf(" ");
				else printf("%d", (cgol -> board[h][w]));
			}else{
				printf("%d", (cgol -> board[h][w]));
			}
		}
		printf("\n");
	}
	if(visabilityModifier == 1) printSpacedCharLine('=', (cgol -> boardWidth));
	else printf("\n");
}

int getFutureState(int currentState, int sumLive){
	int futureState = 0;
	if(currentState == LIVING){
		if(sumLive < 2 || sumLive > 3){
			futureState = DEAD_NEXT_TURN;
		}else{
			futureState = LIVING;
		}
	}
	else if(currentState == NONLIVING){
		if(sumLive == 3) {
			futureState = BORN_NEXT_TURN;
		}
	}

	return futureState;
}

int getFutureCenterState(int **board, int startH, int startW){
	int sumLive = 0;
	int h, w;
	for(h = (startH-1); h < (startH+2); h++){
		for(w = (startW-1); w < (startW+2); w++){
			if( (board[h][w] == (LIVING)) || (board[h][w] == (DEAD_NEXT_TURN)) ){
				sumLive++;
			}
		}
	}
	if(board[startH][startW] == LIVING) sumLive--;

	int futureState = getFutureState((board[startH][startW]), sumLive);
	return futureState;
}

void setFutureBoardState(int **board, int boardWidth, int boardHeight){
	int h, w;
	//Check the center with a two space gap, will add edge and corner cases later
	//Problem if my board is too small
	for(h = 2; h < (boardHeight - 2); h++){
		for(w = 2; w < (boardWidth - 2); w++){
			(board[h][w]) = getFutureCenterState(board, h, w);
		}
	}
}

void updateBoardState(int **board, int boardWidth, int boardHeight){
	int h, w;
	for(h = 0; h < boardHeight; h++){
		for(w = 0; w < boardWidth; w++){
			if(board[h][w] == DEAD_NEXT_TURN){
				(board[h][w]) = NONLIVING;
			}
			else if(board[h][w] == BORN_NEXT_TURN){
				(board[h][w]) = LIVING;
			}
		}
	}
}

int getFitness(int **board, int boardWidth, int boardHeight, int fitnessSpecifier){
	int sumFitness = 0;
	int h, w;
	for(h = 0; h < boardHeight; h++){
		for(w = 0; w < boardWidth; w++){
			if(board[h][w] == LIVING) sumFitness++;
		}
	}
	return sumFitness;
}

void test_CGoLBoardInitialized(struct CGoL *cgol){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_CGoLBoardInitialized\n\n");
	printBoard(cgol, 0);
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}

void test_PrintCGoLSimpleAttributes(struct CGoL *cgol){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_PrintCGoLSimpleAttributes\n\n");
	printf("currentStep: %d\n", (cgol -> currentStep));
	printf("maxStep: %d\n", (cgol -> maxStep));
	printf("boardWidth: %d\n", (cgol -> boardWidth));
	printf("boardHeight: %d\n", (cgol -> boardHeight));
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}
//==================================================================================================================


//==================================================================================================================
//From GeneticAlgorithm.c
int** ga_initializeBestSolution(int solutionWidth, int solutionHeight, char *seedFileName){
	int **bestSeed = (int**)calloc(solutionHeight, sizeof(int));
	int h, w;
	for(h = 0; h < solutionHeight; h++){
		bestSeed[h] = (int*)calloc(solutionWidth, sizeof(int));
	}
	
	FILE *fp;
	int c;
  
    fp = fopen(seedFileName, "r");
    if(fp == NULL){
		printf("\nError in opening file\n");
		return bestSeed;
	}
	
	h = w = 0;
	while(1)
	{
		c = fgetc(fp);
		if( feof(fp) )
		{ 
			break ;
		}
		
		switch(c){
			case '0':
				w++;
				break;
			case '1':
				bestSeed[h][w] = 1;
				w++;
				break;
			case '\n':
				h++;
				w = 0;
				break;
		}
	}
	fclose(fp);
   return bestSeed;	
}

struct Solution* ga_initializePopulation(int maxSolution, int solutionWidth, int solutionHeight){
	struct Solution *population = (struct Solution*)calloc(maxSolution, sizeof(struct Solution));
	int p;
	
	for(p = 0; p < maxSolution; p++){
		population[p] = *ga_initializeSolution(solutionWidth, solutionHeight);
	}
	
	
	return population;
	
}

void ga_freePopulation(struct Solution *population, int maxSolution, int solutionHeight){
	int p, h;
	for(p = 0; p < maxSolution; p++){
		for(h = 0; h < solutionHeight; h++){
			free(population[p].seed[h]);
		}
		free(population[p].seed);
	}
	free(population);
}

struct Solution* ga_initializeSolution(int solutionWidth, int solutionHeight){
	struct Solution *solution = (struct Solution*)malloc(sizeof(struct Solution));
	solution -> seed = (int**)calloc(solutionHeight, sizeof(int));
	
	int h;
	for(h = 0; h < solutionHeight; h++){
		solution -> seed[h] = (int*)calloc(solutionWidth, sizeof(int));
	}
	solution -> fitness = 0;
	
	return solution;
}

void ga_freeSolution(struct Solution *solution, int solutionHeight){
	int  h;
	for(h = 0; h < solutionHeight; h++){
		free((solution -> seed)[h]);
	}
	free(solution -> seed);
}

struct Solution* copySolution(struct Solution *solution, int solutionWidth, int solutionHeight){
	struct Solution *newSolution = ga_initializeSolution(solutionWidth, solutionHeight);
	int h, w;
	for(h = 0; h < solutionHeight; h++){
		for(w = 0; w < solutionWidth; w++){
			//This needs to return the value not a pointer
			(newSolution -> seed)[h][w] = (solution -> seed)[h][w];
		}
	}
	(newSolution -> fitness) = (solution -> fitness);
	return newSolution;
}

int changePopSize(int *attribute){
	requestNewValueForAttribute("Population size", *attribute, MIN_POPULATION, MAX_POPULATION);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_POPULATION, MAX_POPULATION);
	return changed;
}

int changeSolutionWidth(int *attribute){
	requestNewValueForAttribute("Solution width", *attribute, MIN_SOLUTION_SIZE, MAX_SOLUTION_SIZE);
	int changed = getPositiveChangedIntInRange(attribute, 4, MIN_SOLUTION_SIZE, MAX_SOLUTION_SIZE);
	return changed;
}

int changeSolutionHeight(int *attribute){
	requestNewValueForAttribute("Solution height", *attribute, MIN_SOLUTION_SIZE, MAX_SOLUTION_SIZE);
	int changed = getPositiveChangedIntInRange(attribute, 4, MIN_SOLUTION_SIZE, MAX_SOLUTION_SIZE);
	return changed;
}

int changeMaxGeneration(int *attribute){
	requestNewValueForAttribute("Max generation", *attribute, MIN_GENERATION, MAX_GENERATION);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_GENERATION, MAX_GENERATION);
	return changed;
}

int changeMutationRate(int *attribute){
	requestNewValueForAttribute("Mutation rate", *attribute, MIN_MUTATION_RATE, MAX_MUTATION_RATE);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_MUTATION_RATE, MAX_MUTATION_RATE);
	return changed;
}

int changeFitnessSpecifier(int *attribute){
	requestNewValueForAttribute("Fitness specifier", *attribute, MIN_FITNESS_SPECIFIER, MAX_FITNESS_SPECIFIER);
	int changed = getPositiveChangedIntInRange(attribute, 3, MIN_FITNESS_SPECIFIER, MAX_FITNESS_SPECIFIER);
	return changed;
}

int changeSelectionSpecifier(int *attribute){
	requestNewValueForAttribute("Selection specifier", *attribute, MIN_SELECTION_SPECIFIER, MAX_SELECTION_SPECIFIER);
	int changed = getPositiveChangedIntInRange(attribute, 3, MIN_SELECTION_SPECIFIER, MAX_SELECTION_SPECIFIER);
	return changed;
}

int changeCrossoverSpecifier(int *attribute){
	requestNewValueForAttribute("Crossover specifier", *attribute, MIN_CROSSOVER_SPECIFIER, MAX_CROSSOVER_SPECIFIER);
	int changed = getPositiveChangedIntInRange(attribute, 3, MIN_CROSSOVER_SPECIFIER, MAX_CROSSOVER_SPECIFIER);
	return changed;
}


void test_GASolutionsInitiallized(struct GA *ga){
	int p, h, w;
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_GASolutionsInitiallized\n\n");
	printf("ga.bestSolution:\n");
	for(h = 0; h < ga -> solutionHeight; h++){
		for(w = 0; w < ga -> solutionWidth; w++){
			printf("%d", ga -> bestSolution.seed[h][w]);
		}
		printf("\n");
	}
	printf("\n");
	
	int randVal = rand();
	randVal %= ( (ga -> maxSolution) - 1);
	randVal++;
	int testing[3] = {0, randVal, (ga -> maxSolution) - 1};
	for(p = 0; p < 3; p++){
		printf("ga.population[%d]:\n", testing[p]);
		for(h = 0; h < ga -> solutionHeight; h++){
			for(w = 0; w < ga -> solutionWidth; w++){
				printf("%d", ga -> population[testing[p]].seed[h][w]);
			}
			printf("\n");
		}
		printf("\n");
	}
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}

void test_PrintGASimpleAttributes(struct GA *ga){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_PrintGASimpleAttributes\n\n");
	printf("currentSolution: %d\n", (ga -> currentSolution));
	printf("maxSolution: %d\n", (ga -> maxSolution));
	printf("solutionWidth: %d\n", (ga -> solutionWidth));
	printf("solutionHeight: %d\n", (ga -> solutionHeight));
	printf("currentGeneration: %d\n", (ga -> currentGeneration));
	printf("maxGeneration: %d\n", (ga -> maxGeneration));
	printf("mutationRate: %d\n", (ga -> mutationRate));
	printf("fitnessSpecifier: %d\n", (ga -> fitnessSpecifier));
	printf("selectionSpecifier: %d\n", (ga -> selectionSpecifier));
	printf("crossoverSpecifier: %d\n", (ga -> crossoverSpecifier));
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}

void printSolution(struct Solution *solution, int solutionHeight, int solutionWidth, int lineModifier){
	if(lineModifier) printSpacedCharLine('=', TEST_LINE_MAX);
	int h, w;
	for(h = 0; h < solutionHeight; h++){
		for(w = 0; w < solutionWidth; w++){
			printf("%d", solution -> seed[h][w]);
		}
		printf("\n");
	}
	if(lineModifier) printSpacedCharLine('=', TEST_LINE_MAX);
}

int selection_Roulette(struct Solution *population, int maxSolution){
	int fitnessSum = 0;
	int p;
	for(p = 0; p < maxSolution; p++){
		fitnessSum += population[p].fitness;
	}
	int randNum = rand() % (fitnessSum + 1);
	
	p = 0;
	while(p<(maxSolution-1)){
		randNum -= population[p].fitness;
		if(randNum <= 0) break;
		p++;
	}
	return p;
}

struct Solution* crossover(struct Solution *parentA, struct Solution *parentB, int solutionWidth, int solutionHeight){
	struct Solution *child = ga_initializeSolution(solutionWidth, solutionHeight);
	int h, w;
	//For each row
	for(h = 0; h < solutionHeight; h++){
		//Select a point to swap at
		int swapPoint = rand() % (solutionWidth + 1);
		for(w = 0; w < solutionWidth; w++){
			if(w < swapPoint){
				(child -> seed)[h][w] = (parentA -> seed)[h][w];
			}else{
				(child -> seed)[h][w] = (parentB -> seed)[h][w];
			}
		}
	}
	
	return child;
}
//==================================================================================================================


//==================================================================================================================
//From GenericMenu.c
void outputMenu(struct Menu *menu){
	int i;
	printf("\n%s", menu -> menuName);
	for(i = 0; i < menu -> numberOfFunctions; i++){
		printf("\n(%d): %s", i, menu -> functionDescriptions[i]);
	}
	printf("\nSelection a function between (0-%d): ", menu -> numberOfFunctions -1);
}
//==================================================================================================================


//==================================================================================================================
//From Optimization.c
int optimization(struct GA *ga, struct CGoL *cgol){
	printf("\nIn optimization\n");
	printf("\ncurrentGeneration: %d\n", (ga -> currentGeneration) + 1);
	printf("\nmaxGeneration: %d\n", ga -> maxGeneration);
	
	int again = 0;
	
	//Mutate initial population
	if((ga -> currentGeneration) == 0){
		printf("\nBest Solution at start\n");
		printSolution(&(ga -> bestSolution), (ga -> solutionHeight), (ga -> solutionWidth), 0);
		printf("\nWith a fitness of: (%d)\n",(ga -> bestSolution.fitness));
		sleep(1);
		mutatePopulation((ga -> population), (ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight), INITIAL_MUTATION_RATE);
	}
	int p;
	
	//Run each solution through CGoL to determine their fitness
	//Don't show the board...
	int seedTooLarge;
	int i;
	for(i = 0; i < (ga -> maxSolution); i++){
		seedTooLarge = runCGoL(&(ga -> population[i]), (ga -> solutionWidth), (ga -> solutionHeight), (ga -> fitnessSpecifier), cgol, 0);
		if(seedTooLarge == 0) return seedTooLarge; //Temp fix
	}
	
	//Sort population by fitness
	sortPopulationByFitness((ga -> population), (ga -> maxSolution));
	
	//Allocate memory for a new blank population for the next generation
	struct Solution *newPopulation = ga_initializePopulation((ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight));
	
	//For each new solution perform the following by working with the last population
	//Selection and Crossover
	for(i = 0; i < (ga -> maxSolution); i++){
		int parentA, parentB;
		//Selection to find each parent
		parentA = selection_Roulette((ga -> population), (ga -> maxSolution));
		parentB = selection_Roulette((ga -> population), (ga -> maxSolution));
		//perform crossover at different parts for each line
		(newPopulation)[i] = *crossover(&(ga -> population[parentA]), &(ga -> population[parentB]), (ga -> solutionWidth), (ga -> solutionHeight));
	}
	
	//For each solution in the new population
	//Mutation
	mutatePopulation(newPopulation, (ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight), (ga -> mutationRate));
	
	//Determine to continue or set the bestSeed and finish
	if((ga -> currentGeneration) < ((ga -> maxGeneration)-1)){
		again = 1;
	}else{
		//Testing past bestSolution vs current leading solution
		if(ga -> bestSolution.fitness < ga -> population[(ga -> maxSolution) - 1].fitness){
			printf("\nga -> bestSolution.fitness < ga -> population[0].fitness\n");
			//free the old bestSolution
			ga_freeSolution(&(ga -> bestSolution), (ga -> solutionHeight));
			//Copy values and return a new solution
			(ga -> bestSolution) = *copySolution(&((ga -> population)[(ga -> maxSolution) - 1]), (ga -> solutionWidth), (ga -> solutionHeight));
		}
		
		printf("\nBest Solution at finish\n");
		printSolution(&(ga -> bestSolution), (ga -> solutionHeight), (ga -> solutionWidth), 0);
		printf("\nWith a fitness of: (%d)\n",(ga -> bestSolution.fitness));
		sleep(1);
	}
	
	//Free memory from the old population
	ga_freePopulation((ga -> population), (ga -> maxSolution), (ga -> solutionHeight));
	
	//Set ga.population to point to the new population
	(ga -> population) = newPopulation;
	
	//Advance currentGeneration
	(ga -> currentGeneration)++; 
	
	return again;
}

void mutatePopulation(struct Solution *population, int maxSolution, int solutionWidth, int solutionHeight, int mutationRate){
	int h, w, p;
	for(p = 0; p < maxSolution; p++){
		for(h = 0; h < solutionHeight; h++){
			for(w = 0; w < solutionWidth; w++){
				if(bitMutationCheck(mutationRate)){
					if(population[p].seed[h][w]){
						population[p].seed[h][w] = 0;
					} else{
						population[p].seed[h][w] = 1;
					}
				}
			}
		}
	}
}

//Larger seeds will have higher mutation rates...
//Might want to adjust this later
int bitMutationCheck(int mutationRate){
	int result = 0;
	//prepare for random values by multiplying mutationRate by 10 in hopes of a better dispersal of values
	mutationRate*=10;
	int randValue = rand();
	if((randValue % (MAX_MUTATION_RATE*10)) <= mutationRate) result = 1;
	return result;
}

//Grabbed a selection sort from:
//http://www.codebeach.com/2008/09/sorting-algorithms-in-c.html
void sortPopulationByFitness(struct Solution *population, int maxSolution){
	struct Solution temp;
	int i;
    for (i = 0; i < (maxSolution - 1); ++i)
    {
        int j, min;
        min = i;
        for (j = i+1; j < maxSolution; ++j)
        {
			if(population[j].fitness < population[min].fitness)
				min = j;
        }

        temp = population[i];
        population[i] = population[min];
        population[min] = temp;
	}
}
//==================================================================================================================


//==================================================================================================================
//From Run.c
void run(struct Settings *settings, struct CGoL *cgol, struct GA *ga){
	//Create GenericMenu structs
	struct Menu main_Menu;
	struct Menu menu_GA;
	struct Menu menu_CGoL;
	
	//Initialize mainMenu
	main_Menu.numberOfFunctions = 6;
	main_Menu.menuName = "Main Menu";
	main_Menu.functionDescriptions = (char *[]){ "GA Settings Menu", "CGoL Settings Menu", 
	"Run Optimization", "Observe CGoL with Best Seed", "Save Best Seed", "Exit"
	};
	//if(debugRun) test_InitializeMain_Menu();
	
	
	//Initialize menu_GA
	menu_GA.numberOfFunctions = 9;
	menu_GA.menuName = "GA Settings Menu";
	menu_GA.functionDescriptions = (char *[]){ "Set Population Size", "Set Solution Width", 
	"Set Solution Height", "Set Max Generation", "Set Mutation Rate", "Set Fitness Specifier", 
	"Set Selection Specifier", "Set Crossover Specifier", "Exit"
	};
	//if(debugRun) test_InitializeMenu_GA);
	
	
	//Initialize menu_CGoL
	menu_CGoL.numberOfFunctions = 4;
	menu_CGoL.menuName = "CGoL Settings Menu";
	menu_CGoL.functionDescriptions = (char *[]){ "Set Board Width", "Set Board Height", 
	"Set Max Step", "Exit"
	};
	//if(debugRun) test_InitializeMenu_CGoL();
	
	
	//Loop through mainMenu until exitCondition is returned
	int index;
	do{
		index = mainMenu(&main_Menu);
		switch(index){
			case 0:
				//Loop through menu_GA until exitCondition is returned
				//This functions includes IO which enables the user to access
				//and change the values of "ga" attributes
				while(settingsMenu_GA(&menu_GA, ga) != EXIT_CONDITION);
				if(debugRun) test_PrintGASimpleAttributes(ga);
				break;
			case 1:
				//Loop through menu_CGoL until exitCondition is returned
				//This functions includes IO which enables the user to access
				//and change the values of "cgol" attributes
				while(settingsMenu_CGoL(&menu_CGoL, cgol) != EXIT_CONDITION);
				if(debugRun) test_PrintCGoLSimpleAttributes(cgol);
				break;
			case 2:
				//Loop through each solution in population through each generation
				//This functions includes simple output as it progresses
				//Returns true if currentGeneration < maxGeneration
				printf("\nStarting optimization\n");
				ga -> currentGeneration = 0;
				while(optimization(ga, cgol));
				printf("\nFinished optimization\n");
				break;
			case 3:
				//observeBestSeed(ga, cgol)
				printf("\nStarting To watch the bestSolution\n");
				runCGoL(&(ga -> bestSolution), (ga -> solutionWidth), (ga -> solutionHeight), (ga -> fitnessSpecifier), cgol, 1);
				printf("\nFinished bestSolution\n");
				break;
			case 4:
				//saveBestSeed(ga)
				break;
			case 5:
				//exit
				index = EXIT_CONDITION;
				break;
			default:
				index = SKIP_CONDITION;
				printf("\nInvalid input\n");
				break;
		}
	}
	while(index != EXIT_CONDITION);
}

int mainMenu(struct Menu *menu){
	int index = -2;
	outputMenu(menu);
	index = getPositiveIntInRange(3, 0, menu -> numberOfFunctions);
	return index;
}

int settingsMenu_GA(struct Menu *menu, struct GA *ga){
	int index = -1;
	int oldMaxSolution;
	int oldSolutionHeight;
	outputMenu(menu);
	index = getPositiveIntInRange(3, 0, menu -> numberOfFunctions);
	switch(index){
		case 0:
			//Update maxSolution
			//If successful, free population and allocate a new population in its place
			//using the updated attributes
			oldMaxSolution = (ga -> maxSolution);
			if(changePopSize(&(ga -> maxSolution))){
				ga_freePopulation((ga -> population), oldMaxSolution, (ga -> solutionHeight));
				(ga -> population) = ga_initializePopulation((ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight));
				printf("\nPopulation max changed to (%d)\n", (ga -> maxSolution));
				//Also Change bestSolution...
				ga_freeSolution(&(ga -> bestSolution), (ga -> solutionHeight));
				(ga -> bestSolution) = *ga_initializeSolution((ga -> solutionWidth), (ga -> solutionHeight));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 1:
			//Update solutionWidth
			//If successful, free population and allocate a new population in its place
			//using the updated attributes
			if(changeSolutionWidth(&(ga -> solutionWidth))){
				ga_freePopulation((ga -> population), (ga -> maxSolution), (ga -> solutionHeight));
				(ga -> population) = ga_initializePopulation((ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight));
				printf("\nSolution width changed to (%d)\n", (ga -> solutionWidth));
				//Also Change bestSolution...
				ga_freeSolution(&(ga -> bestSolution), (ga -> solutionHeight));
				(ga -> bestSolution) = *ga_initializeSolution((ga -> solutionWidth), (ga -> solutionHeight));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 2:
			//Update solutionHeight
			//If successful, free population and allocate a new population in its place
			//using the updated attributes
			oldSolutionHeight = (ga -> solutionHeight);
			if(changeSolutionHeight(&(ga -> solutionHeight))){
				ga_freePopulation((ga -> population), (ga -> maxSolution), oldSolutionHeight);
				(ga -> population) = ga_initializePopulation((ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight));
				printf("\nSolution height changed to (%d)\n", (ga -> solutionHeight));
				//Also Change bestSolution...
				ga_freeSolution(&(ga -> bestSolution), oldSolutionHeight);
				(ga -> bestSolution) = *ga_initializeSolution((ga -> solutionWidth), (ga -> solutionHeight));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 3:
			//Update maxGeneration
			if(changeMaxGeneration(&(ga -> maxGeneration))){
				printf("\nMax generation changed to (%d)\n", (ga -> maxGeneration));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 4:
			//Update mutationRate
			if(changeMutationRate(&(ga -> mutationRate))){
				printf("\nMutation rate changed to (%d)\n", (ga -> mutationRate));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 5:
			if(changeFitnessSpecifier(&(ga -> fitnessSpecifier))){
				printf("\nFitness specifier changed to (%d)\n", (ga -> fitnessSpecifier));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 6:
			if(changeSelectionSpecifier(&(ga -> selectionSpecifier))){
				printf("\nSelection specifier changed to (%d)\n", (ga -> selectionSpecifier));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 7:
			if(changeCrossoverSpecifier(&(ga -> crossoverSpecifier))){
				printf("\nCrossover specifier changed to (%d)\n", (ga -> crossoverSpecifier));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 8:
			index = EXIT_CONDITION;
			break;
		default:
			index = SKIP_CONDITION;
			printf("\nInvalid input\n");
			break;
	}
	return index;
}

int settingsMenu_CGoL(struct Menu *menu, struct CGoL *cgol){
	int index = -1;
	int oldBoardHeight;
	outputMenu(menu);
	index = getPositiveIntInRange(3, 0, menu -> numberOfFunctions);
	switch(index){
		case 0:
			//Update boardWidth
			//If successful, free board and allocate a new board in its place
			//using the updated attributes
			if(changeBoardWidth(&(cgol -> boardWidth))){
				cgol_freeBoard((cgol -> board), (cgol -> boardHeight));
				(cgol -> board) = cgol_initializeBoard((cgol -> boardWidth), (cgol -> boardHeight));
				printf("\nBoard width changed to (%d)\n", (cgol -> boardWidth));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 1:
			//Update boardHeight
			//If successful, free board and allocate a new board in its place
			//using the updated attributes
			oldBoardHeight = (cgol -> boardHeight);
			if(changeBoardHeight(&(cgol -> boardHeight))){
				cgol_freeBoard((cgol -> board), oldBoardHeight);
				(cgol -> board) = cgol_initializeBoard((cgol -> boardWidth), (cgol -> boardHeight));
				printf("\nBoard width changed to (%d)\n", (cgol -> boardWidth));
			}else{
				printf("\nInvalid input\n");
			}
			break;
		case 2:
			//Update maxStep
			if(changeMaxStep(&(cgol -> maxStep))){
				printf("\nMax step changed to (%d)\n", (cgol -> maxStep));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 3:
			index = EXIT_CONDITION;
			break;
		default:
			index = SKIP_CONDITION;
			printf("\nInvalid input\n");
			break;
	}
	return index;
}
//==================================================================================================================


//==================================================================================================================
//From RunCGoL.c
int runCGoL(struct Solution *solution, int solutionWidth, int solutionHeight, int fitnessSpecifier, struct CGoL *cgol, int visabilityModifier){
	//reset board
	resetBoard((cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight));
	
	//insert seed into the center of the board
	int seedTooLarge;
	seedTooLarge = loadSeed((solution -> seed), solutionWidth, solutionHeight, (cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight));
	if(seedTooLarge == 0) return seedTooLarge; //Temp fix
	
	//Play the game
	for((cgol -> currentStep) = 0; (cgol -> currentStep) < (cgol -> maxStep); (cgol -> currentStep)++){
		//Print step information
		if(visabilityModifier == 1){
			printf("\ncurrentStep: %d\n", (cgol -> currentStep));
			printf("\nmaxStep: %d\n", (cgol -> maxStep));
		}
		
		//Print the board
		if(visabilityModifier == 1){
			printBoard(cgol, 1);
			sleep(1);
		}
		
		//Determine the next state of the game
		setFutureBoardState((cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight));
		
		//Update the game to its next state
		updateBoardState((cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight));
	}
	
	//Print the board
	if(visabilityModifier == 1){
		printBoard(cgol, 1);
		sleep(1);
	}
	
	//DetermineFitness
	(solution -> fitness) = getFitness((cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight), fitnessSpecifier);
	
	return 1;
}
//==================================================================================================================


//==================================================================================================================
//From hammDrewFinalProj.c
int main(int argc, char* argv[])
{
	//Random attribute
	srand((unsigned) time(&t));
	
	//File attributes
	FILE *fp;
	char *settingsFileName;
	char *seedFileName;
	
	
	//================================================================
	//Evaluate command line arguments and open the relevant file
	switch(argc){
		case 1:
			fp = fopen(defaultFileName, "r");
			break;
		case 2:
			fp = fopen(argv[1], "r");
			break;
		default:
			printf("Error in argument count\nUsage: %s <Saved_File>", argv[0]);
			printf("\nargc = %d", argc);
			exit(2);
	}
	//================================================================
	//Test the file for containing characters
	if(debugMode) test_FileCharacterOutput(fp);
	
	
	//================================================================
	//Read from the base file to get the names of the secondary files
	settingsFileName = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	seedFileName = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	fscanf(fp, "%s %s", settingsFileName, seedFileName);
	fclose(fp);
	//================================================================
	
	
	//================================================================
	//Ensure that the file names have valid lengths
	if((sizeof(settingsFileName) == 0 || sizeof(seedFileName) == 0)){
		printf("Invalid file input.");
        exit(2);
    } else if(sizeof(settingsFileName) == 50 || sizeof(seedFileName) == 50){
		printf("File names too large.");
        exit(2);
	}
	//================================================================
	//Test that the file names were read correctly
	if(debugMode) test_FileNamesFromBaseFile(settingsFileName, seedFileName);
	
	
	//================================================================
	//Intro Message
	printf("\nFile: \t%s\nTitle: \t%s\nBy: \t%s\nDate: \t%s\nClass: \t%s\n\n", argv[0], "Final Project", "Drew Hamm", "03/18/2015", "CS 133c");
	printf("This program is designed from Conway's Game of Life.(CGoL)\n");
	printf("In addition, a Genetic Algorithm(GA) is used to find optimal seeds.\n");
	printf("Options are provided to change the game environment as well as the behaviour of the GA.\n\n");
	
	printf("Hit enter to begin...\n");
	while(getchar() != '\n');
	//================================================================
	
	
	//================================================================
	//Create structs
	struct Settings settings;
	struct CGoL cgol;
	struct GA ga;
	
	//Open settings file
	fp = fopen(settingsFileName, "r");
	rewind(fp);
	
	//Initialize structs values
	//Settings
	strcpy(settings.settingsFileName, settingsFileName);
	strcpy(settings.seedFileName, seedFileName);
	fscanf (fp, "%d", &settings.viewWidth);
	fscanf (fp, "%d", &settings.viewHeight);
	//CGoL
	cgol.currentStep = 0;
	fscanf (fp, "%d", &cgol.maxStep);
	fscanf (fp, "%d", &cgol.boardWidth);
	fscanf (fp, "%d", &cgol.boardHeight);
	//GA
	ga.currentSolution = 0;
	fscanf (fp, "%d", &ga.maxSolution);
	fscanf (fp, "%d", &ga.solutionWidth);
	fscanf (fp, "%d", &ga.solutionHeight);
	ga.currentGeneration = 0;
	fscanf (fp, "%d", &ga.maxGeneration);
	fscanf (fp, "%d", &ga.mutationRate);
	fscanf (fp, "%d", &ga.fitnessSpecifier);
	fscanf (fp, "%d", &ga.selectionSpecifier);
	fscanf (fp, "%d", &ga.crossoverSpecifier);
	fclose(fp);
	
	//Initialize cgol.board
	cgol.board = cgol_initializeBoard(cgol.boardWidth, cgol.boardHeight);
	
	//Initialize ga.bestSolution
	ga.bestSolution.seed = ga_initializeBestSolution(ga.solutionWidth, ga.solutionHeight, settings.seedFileName);

	//Initialize ga.population
	ga.population = ga_initializePopulation(ga.maxSolution, ga.solutionWidth, ga.solutionHeight);
	
	//================================================================
	//Check if each struct was initialized correctly
	if(debugMode) {
		test_StructValuesInitialized(&settings, &cgol, &ga);
		test_CGoLBoardInitialized(&cgol);
		test_GASolutionsInitiallized(&ga);
	}
	
	
	//================================================================
	//For readability I moved this to Run.c
	//I have a new debugMode this function which is currently included in run.c
	run(&settings, &cgol, &ga);
	//================================================================
	
	
	
	//================================================================
	//Exit Message
	printf("\n\nThis concludes the program.\n");
	//================================================================
	
	
	//================================================================
	//File output
	//Not sure if I need this at this point...
	//================================================================
	return 0;
}

void test_FileCharacterOutput(FILE *fp){
	int c;
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_FileCharacterOutput\n\n");
	while(1){
		c = fgetc(fp);
		if(feof(fp)){
			break;
		}
		if(c != '\r') printf("[%c]", c);
   }
   printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
   rewind(fp);
}

void test_FileNamesFromBaseFile(char *settingsFileName, char *seedFileName){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_FileNamesFromBaseFile\n\n");
	printf("Settings File Name: \"%s\"\nSeed File Name: \"%s\"\n", settingsFileName, seedFileName);
	printf("strlen(settingsFileName): %d\nstrlen(seedFileName): %d", strlen(settingsFileName), strlen(seedFileName));
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}

void test_StructValuesInitialized(struct Settings *settings, struct CGoL *cgol, struct GA *ga){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_settingStructInit\n\n");
	printf("settingsFileName: %s", settings -> settingsFileName);
	printf("\nseedFileName: %s", settings -> seedFileName);
	printf("\nviewWidth: %d", settings -> viewWidth);
	printf("\nviewHeight: %d", settings -> viewHeight);
	
	printf("\n\ncurrentStep: %d", cgol -> currentStep);
	printf("\nmaxStep: %d", cgol -> maxStep);
	printf("\nboardWidth: %d", cgol -> boardWidth);
	printf("\nboardHeight: %d", cgol -> boardHeight);
	
	printf("\n\ncurrentSolution: %d", ga -> currentSolution);
	printf("\nmaxSolution: %d", ga -> maxSolution);
	printf("\nsolutionWidth: %d", ga -> solutionWidth);
	printf("\nsolutionHeight: %d", ga -> solutionHeight);
	printf("\ncurrentGeneration: %d", ga -> currentGeneration);
	printf("\nmaxGeneration: %d", ga -> maxGeneration);
	printf("\nmutationRate: %d", ga -> mutationRate);
	printf("\nfitnessSpecifier: %d", ga -> fitnessSpecifier);
	printf("\nselectionSpecifier: %d", ga -> selectionSpecifier);
	printf("\ncrossoverSpecifier: %d", ga -> crossoverSpecifier);
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}
//==================================================================================================================