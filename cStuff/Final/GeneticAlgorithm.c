// GeneticAlgorithm.c
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