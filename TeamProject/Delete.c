#include <stdio.h>
void Delete() {
	char continueCheck = '1';
	int time;
	while (continueCheck != '0') {
		printf("\nPlease enter the time that needs to be deleted: \n");
		scanf("%d", &time);
		time--;
		if //has already been deleted
		{
			printf("\nThat time was already deleted! \n");
		}
		else {
			//delete it
		}
		if (continueCheck != '0')
		{
			int Buffer;
			while ((Buffer = getchar()) != '\n' && Buffer != EOF);
		}
		printf("\nPlease enter 1 to delete a different time\nOr enter 0 if you are done: \n");
		scanf(" %c", &continueCheck);
	}
	Save(); //safe to file function
	return;
}