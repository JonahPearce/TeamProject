#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "taskManager.h"

int taskMenu()
{
	int i = 0;
	int IDNum;
	char searchWord[20];
	struct Task list[10];

	bool complete = false;

	//loops while the complete condition is not met. Once an invalid input
	//is detected, then the complete condition is met and the module will return
	//to the main program
	while (!complete)
	{
		char selection = ' ';

		//input selection prompt to navigate this module
		printf("Choose one of the following options from the menu below\n");
		printf("To add a new task or update an existing one - (a)\n");
		printf("To delete an existing task - (b)\n");
		printf("To display current task list - (c)\n");
		printf("To print all tasks in list - (d)\n");
		printf("To intialize list - (e)\n");
		printf("To search for a keyword in the tasks - (f)\n");
		printf("Your choice:");

		selection = getchar();

		//Used to avoid printing menu twice
		if (selection == '\n')
		{
			selection = getchar();
		}

		//Calls various functions depending on the input
		switch (selection)
		{
		case 'a':


			IDNum = 0;
			char newDesc[100];
			char activePrompt = ' ';


			//input statements for ID, whether it's active, and the description
			printf("What is the taskID (0-9) of the task you would like to Add/Update?:");

			scanf_s("%d", &IDNum);

			printf("\n");

			printf("Enter the new task's description:");

			fgets(newDesc, 100, stdin); //used to get around the newline left over from scanf_s
			fgets(newDesc, 100, stdin);


			printf("\nNew desc:%s\n", newDesc);

			printf("\n");

			printf("Is this task active? (Enter 'y' for yes or 'n' for no): ");

			activePrompt = getchar();

			if (activePrompt == '\n')
			{
				activePrompt = getchar();
			}

			printf("\n");

			//used to determine if the active bool should be true or false. If it's true,
			//then the task will be considered active, if false, it will be considered inactive
			//both of this terms are used when displaying and are used to help organise

			switch (activePrompt)
			{
			case 'y':
				list[IDNum].active = true;
				printf("You chose active\n");
				break;
			case 'n':
				list[IDNum].active = false;
				printf("You chose inactive\n");
				break;
			}

			strcpy(list[IDNum].description, newDesc);



			break;

		case 'b':

			IDNum = 0;
			printf("Please input the ID of the task you would like to remove.");
			scanf("%d", &IDNum);

			IDNum++;

			list[i].active = false;
			strcpy(list[i].description, "Empty");


			break;

		case 'c':
			//Display One
			IDNum = 0;
			printf("Please input the ID of the task you would like to see.");
			scanf("%d", &IDNum);


			//used for printing a border around the task description
			printf("IDNumber:%d\n", IDNum);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			printf("++ %s ++\n", list[IDNum].description);


			//checks to see if task is active or not
			if (list[IDNum].active == true)
			{
				printf("++\t\t\t Task is active \t\t\t++\n++\n");
			}
			else
			{
				printf("++\t\t\t Task is not active \t\t\t\n++\n");
			}

			printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			break;

		case 'd':
			i = 0;
			IDNum = 0;

			//similar to the display task, this one runs through all of them, skipping the input prompt
			//and using a for loop instead
			for (i = 0; i < 10; i++)
			{
				IDNum = i;
				printf("IDNumber:%d\n", IDNum);
				printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n++\n++\n");
				printf("++ %s ++\n++\n", list[IDNum].description);


				if (list[IDNum].active == true)
				{
					printf("++\t\t\t Task is active \t\t\t\n++\n");
				}
				else
				{
					printf("++\t\t\t Task is not active \t\t\t\n++\n");
				}

				printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			}
			break;

		case 'e':


			for (i = 0; i < 10; i++)
			{
				list[i].active = false;
				strcpy(list[i].description, "Empty");
			}

			printf("Still being implemented, please wait\n");
			break;

		case 'f':

			printf("Please enter the word you would like to search the active tasks for:");
			fgets(searchWord, 20, stdin); //get searchword
			fgets(searchWord, 20, stdin);


			for (i = 0; i < 10; i++)
			{
				char* searchTerm = strstr(list[i].description, searchWord);

				if (searchTerm != NULL)
				{
					printf("Task %d has the search term\n", i);
				}

			}

			break;

		case 'q':
			printf("Returning to Main Menu...\n");
			complete = true;
			break;

		default:
			printf("Invalid input, please try again\n");
			break;

		}


	}

	return 0;
}

