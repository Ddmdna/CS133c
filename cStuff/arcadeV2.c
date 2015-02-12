// arcadeV2.c
#include <stdio.h>
int main()
{
	int const CANDYBAR_RATIO = 10;
	int const GUMBALL_RATIO = 3;
	
	int coupons = 0;
	int candybars = 0;
	int gumballs = 0;
	
	int couponCounter = 0;
	
	printf("How many coupons would you like to spend?\n");

	scanf(" %d", &coupons);
	
	while(coupons > 0){
		coupons--;
		couponCounter++;
		if(couponCounter == CANDYBAR_RATIO){
			candybars++;
			couponCounter = 0;
		}
	}
	
	while(couponCounter > 0){
		couponCounter--;
		coupons++;
		if(coupons == GUMBALL_RATIO){
			gumballs++;
			coupons = 0;
		}
	}
	
	printf("\n\nCandy bars received: %d\n", candybars);
	printf("Gumballs received: %d\n", gumballs);
	printf("Coupons returned: %d\n", coupons);
	
	return 0;
}