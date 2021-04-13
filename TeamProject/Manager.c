#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Manager.h"



//Used to initialize the list
struct TaskManager initialize()
{
	struct TaskManager newItem;
	
	newItem.description = ' ';
	newItem.active = true;

	return newItem;
}

//used to print an individual task
void displayTask(struct TaskManager* list)
{
	int IDNum = 0;
	printf("Please input the ID of the task you would like to see.");
	scanf("%d", &IDNum);

	//used for printing a border around the task description
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("++ %s ++\n", list[IDNum].description);

	//checks to see if task is active or not
	if (list[IDNum].active == true)
	{
		printf("++\t\t Task is active \t\t++\n ");
	}
	else
	{
		printf("++\t\t Task is not active \t\t++\n ");
	}
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");

}

void displayAll(struct TaskManager* list)
{
	int i = 0;
	int IDNum;

	//similar to the display task, this one runs through all of them, skipping the input prompt
	//and using a for loop instead
	for (i = 0; i<10; i++)
	{
		IDNum = i;
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("++ %s ++\n", list[IDNum].description);
		if (list[IDNum].active == true)
		{
			printf("++\t\t Task is active \t\t++\n ");
		}
		else
		{
			printf("++\t\t Task is not active \t\t++\n ");
		}
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	
}

//Users can either add a new task or update an existing one with this function
void addNewUpdate(struct TaskManager* list)
{
	int IDNum = 0;
	char description[100];
	char active = ' ';

	//input statements for ID, whether it's active, and the description
	printf("Enter where in the queue you would like the task to be: ");
	scanf_s("%d", &IDNum);

	printf("Enter the new task's description: ");
	fgets(description, 100, stdin);

	printf("Is this task active? (Enter 'y' for yes or 'n' for no): ");
	scanf_s("%c", &active);

	//used to determine if the active bool should be true or false. If it's true,
	//then the task will be considered active, if false, it will be considered inactive
	//both of this terms are used when displaying and are used to help organise

	switch (active)
	{
	case 'y':
		list[IDNum].active = true;
	case 'n':
		list[IDNum].active = false;
	default:
		printf("That input is not valid");
		break;
	}

	list[IDNum].description = description; //Ensure description from this function reaches main list
}

void removeFromList(struct TaskManager* list)
{
	int IDNum = 0;

	//This function takes in the value of the ID that the user wishes to remove, then
	//changes the value back to what is was when first initialized.

	printf("Please input the ID of the task to remove from the list:");
	scanf("%d", &IDNum);

	list[IDNum].description = ' ';
	list[IDNum].active = false;

	printf("Task %d deleted.\n", IDNum);
	}


