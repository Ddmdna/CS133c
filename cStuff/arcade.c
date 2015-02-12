// arcade.c
#include <stdio.h>
int main()
{
	int const CANDYBAR_RATIO = 10;
	int const GUMBALL_RATIO = 3;
	
	int coupons;
	int candybars;
	int gumballs;
	
	printf("How many coupons would you like to spend?\n");

	scanf(" %d", &coupons);
	
	candybars = coupons / CANDYBAR_RATIO;
	coupons-= candybars * CANDYBAR_RATIO;
	gumballs = coupons / GUMBALL_RATIO;
	coupons-= gumballs * GUMBALL_RATIO;
	
	printf("\n\nCandy bars received: %d\n", candybars);
	printf("Gumballs received: %d\n", gumballs);
	printf("Coupons returned: %d\n", coupons);
	
	return 0;
}