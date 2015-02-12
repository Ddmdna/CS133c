#include <stdio.h>

int main(int argc, char const *argv[])
{
	int maxCapacity = 0;
	int numPeopleAttending = 0;
	char stop = 'n';
	while(stop!='y' && stop!='Y'){
		printf("\nEnter the maximum capacity for the meeting room.\n");
		scanf(" %d", &maxCapacity);
	
		printf("\nEnter the number of members attending the meeting.\n");
		scanf(" %d", &numPeopleAttending);
	
		if(numPeopleAttending<=maxCapacity) {
			printf("\nIt is legal to hold the meeting.\n");
			printf("You may add %d more members.\n", (maxCapacity - numPeopleAttending) );
		}
		else{
			printf("\nIt is illegal to hold the meeting due to fire regulations.\n");
			printf("You must remove %d or more members to comply with fire regulations.\n\n\n", (numPeopleAttending - maxCapacity) );
		}
		
		printf("\nWould you like to end the program?(Y/N): ");
		scanf(" %c", &stop);
	}
	
	
	return 0;
}