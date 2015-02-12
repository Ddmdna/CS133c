#include <stdio.h>

struct person
{
	char name[20];
	int age;
	float height;
};

typedef struct person per;

int main(int argc, char *argv[])
{
	struct person joseph = {"Joseph Jess", 28, 5.9};
	struct person differentName = {"DIfferent Name", 100, 2.1};
	per *perPtr;
	perPtr = &joseph;
	printPerPtr(perPtr);
	
	/*
	printf("Joseph's attributes are:\n\tname: %s\n\tage: %4d\n\theight: %.2f\n", joseph.name, joseph.age, joseph.height);
	printPerson(differentName);
	*/

	return 0;
}

//print a person struct's member variables out in a structured format
int printPerson(per aPerson)
{
	printf("%s's attributes are:\n\tname: %s\n\tage: %4d\n\theight: %.2f\n", aPerson.name, aPerson.name, aPerson.age, aPerson.height);
	
	return 0;
}

//print a person struct's member variables out in a structured format
int printPerPtr(per *aPerson)
{
	printf("%s's attributes are:\n\tname: %s\n\tage: %4d\n\theight: %.2f\n", aPerson->name, (*aPerson).name, aPerson->age, aPerson->height);
	
	return 0;
}