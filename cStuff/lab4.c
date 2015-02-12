#include <stdio.h>
#include <string.h>

#define EOL 0
#define ALPHA 1
#define DIGIT 2
#define OTHER 3

#define NEARZERO .00000001

int charType();
int flag(float);
int stringy(char *, int);
float numberThing(float, float, float);

//a program to show some messy code, hopefully to be cleaned during lab
int main()
{

    printf("charType function call:\n______________________________\n");
    printf("%d\n\n", charType());

/*

    printf("flag function calls:\n______________________________\n");
    printf("%d\n", flag(1));
    printf("%d\n", flag(0));
    printf("%d\n\n", flag(-1));



    printf("stringy function call:\n______________________________\n");
    char myStr[10] = {"DDDDDDDDDD"};
    int myStrLen = sizeof(myStr);
	int i;
	printf("size of array: %d\n", myStrLen);
    stringy(myStr, myStrLen);
    printf("%s\n", myStr);
	myStrLen = sizeof(myStr);
    printf("New string length: %d\n", strlen(myStr));

    printf("numberThing function call:\n______________________________\n");
    printf("%f\n", numberThing(1, 1, 1));
*/


    return 0;
}

//find type of character
int charType()
{
    char c = '\n';
    while((c=getchar()) != '\n')
    {
        if(c==' ') continue;
        if(c=='\t') continue;
        if(c<'0') return(OTHER);
        if(c<='9') return(DIGIT);
        if(c<'a') return(OTHER);
        if(c<='z') return(ALPHA);
        return(OTHER);
    } return(EOL);
}

//check sign of a number?
int flag(float a)
{
    int result = 0;

	if(a<0) result = -1;
	else if(a>0) result = 1;

	return result;
}

//get a string?
int stringy(char * s, int sLen)
{
    int i=0;
    char c = '1';
    while( (i < sLen) && ( (c=getchar()) != '\n') )
    {
        if(c=='\t') c=' ';
		s[i]=c;
		i++;
    }
	if(c == '\n') s[i] = '\0';
	else if(i == sLen) s[i] = 'G';
    return 0;
}

//something to do with numbers
float numberThing(float x, float j, float k)
{
    float y = -1;

    if(x!=0)
        if(j>k) y=j/x;
        else y=k/x;
    else
        if(j>k) y=j/NEARZERO;
        else y=k/NEARZERO;

    return y;
}