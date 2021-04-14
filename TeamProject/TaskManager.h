#pragma once
#include <stdio.h>
#include <stdbool.h>

struct TaskManager
{
	char* description;
	bool active;
};

struct TaskManager initialize();

void displayTask(struct TaskManager* Item);

void displayAll(struct TaskManager* Item);

void addNewUpdate(struct TaskManager* list);

void removeFromList(struct TaskManager* list);

void searchTask(struct TaskManager* list);