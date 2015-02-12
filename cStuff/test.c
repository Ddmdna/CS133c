/*
	I need a string handling function
	Goals:
		get input from user
		return formatted input
		
	Steps:
		Determine how the input should be formatted
		Determine formatting limits
		Perform desired formatting within limits
		return results
		
	Questions:
		Function for each data type?
		Function for each data length? I guess that's data type...
		Determine max length?
		
	Immediate need:
		Receive input from user of any length
		Remove escape codes.(I don't think user can do this?)
		Format input
		Reduce input to desired length
		Output result
	
	Plan:
		Copy randNum2.c inputs process
		
	I think I might not be doing anything more than what fgets() does. 
	If I plan on doing anything worth while, I would need to return
	the input has specific data types.
	Most of the work here would be checking that the input is correct.
	So this would mostly be a list of helper functions. 
*/
	// test.c
	#include <stdio.h>
	#include <limits.h>
	
	int main()
	{
		//Attributes
		//char buffer[MAX+1];
		char charCatch = '0';
		char ch;
		int numbers[1000];
		//Get input from user
		//fgets(buffer, sizeof buffer, stdin );
		
		printf("Enter a string:\n");
		printf("\n\n");
		int i = 0;
		while ((ch = getchar()) != '\n')
		{
			
			switch(ch){
				case '9': 
					numbers[i] = 9;
					i++;
					break;
				case '8': 
					numbers[i] = 8;
					i++;
					break;
				case '7': 
					numbers[i] = 7;
					i++;
					break;
				case '6': 
					numbers[i] = 6;
					i++;
					break;
				case '5': 
					numbers[i] = 5;
					i++;
					break;
				case '4': 
					numbers[i] = 4;
					i++;
					break;
				case '3': 
					numbers[i] = 3;
					i++;
					break;
				case '2': 
					numbers[i] = 2;
					i++;
					break;
				case '1': 
					numbers[i] = 1;
					i++;
					break;
				case '0': 
					numbers[i] = 0;
					i++;
					break;
			}
		}
		printf("\n\n");
		int d;
		for(d = 0; d < i; d++){
			printf("%d\n", numbers[d]);
		}
		
		return 0;
	}
	
	

	