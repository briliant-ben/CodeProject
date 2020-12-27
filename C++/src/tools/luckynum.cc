#include <stdio.h>

int luckynum(float money){
	printf("You have %4.2f $.\n", money);
	if(money <= 100 && money > 50){
		printf("A cup of drink and a facinating bueaty!\n");
		return 1;
	}
	else if(money <= 50 && money > 20){
		printf("A beautiful beach ticket!\n");
		return 2;
	}
	else if(money <= 20 && money > 0){
		printf("A ice-creame!\n");
		return 3;
	}
	else{
		printf("You don't need to buy anything!\n");
		return 4;
	}
	printf("Now have a grate time!\n");
	return 0;
}
