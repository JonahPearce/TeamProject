#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//include statements for module files

int main()
{
	bool complete = false;
	char selection = ' ';

	printf("Welcome to the Management Suite\n");
	
	while (!complete)
	{
		printf("Please choose an option by entering the corresponding letter.\n");
		printf("To quit the program, press 'q'.\n");
		printf("To use the Task Manager - (a)\n");
		printf("To use the File Manager - (b)\n");
		printf("To use the Schedule Manager - (c)\n");
		printf("To play the Game Module - (d)\n");
		printf("Your selection: ");

		scanf("%c", &selection);

		switch (selection)
		{
		case 'a':
			//taskManager();
			break;
		case 'b':
			//fileManager();
			break;
		case 'c':
			//scheduleManager();
			break;
		case 'd':
			//gameModule();
			break;
		case 'q':
			printf("Thank you for using the Management Suite, goodbye...\n");
			complete = true;
		default:
			printf("Invalid input, please select a different option \n");
			scanf("%c", &selection);
		}

		if (!complete)
		{
			scanf("%c", &selection);
		}

	}


	return 0;
}