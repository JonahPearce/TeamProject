#define MAXLEN 50
#define NUMLEN 10
#include <stdio.h>
void Add() {
	char continueCheck = '1';
	int time;
	while (continueCheck != '0') {
		printf("\nPlease enter the time that needs to be added: \n");
		scanf("%d", &time);
		if //parameters does not fit
		{
			printf("\nThat time does not work! \n");
		}
		else {
			//add it
		}
		if (continueCheck != '0')
		{
			int Buffer;
			while ((Buffer = getchar()) != '\n' && Buffer != EOF);
		}
		printf("\nPlease enter 1 to add a different time\nOr enter 0 if you are done: \n");
		scanf(" %c", &continueCheck);
	}
	Save(); //safe function
	return;
}