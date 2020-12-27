#include <stdio.h>
#include "luckynum.h"

int main(){
	printf("hello, summertime!\n");
	printf("How much money do you have?");
	float money = 0;
	scanf("%f", &money);
	luckynum(money);
	getchar();
	while ((getchar()) != '\n');
	return 0;
}
