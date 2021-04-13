#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Manager.h"



int taskMenu()
{
	int i;//loop counter variable
	//Initialize an array of structs to hold the task list
	struct TaskManager list[10];
	for (i=0; i<10; i++)
	{
		list[i] = initialize();
	}

	//used to allow the while loop to run until a condition is met
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
		printf("Your choice:");
	
		scanf("%c",&selection);


		//Calls various functions depending on the input
		switch (selection)
		{
		case 'a':
			addNewUpdate(list);
			break;

		case 'b':
			removeFromList(list);
			break;

		case 'c':
			displayTask(list);
			break;

		case 'd':
			displayAll(list);
			break;

		default:
			printf("Returning to Main Menu...\n");
			complete = true;
		}
	
	}


	return (0);
}