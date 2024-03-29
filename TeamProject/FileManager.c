#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "FileManager.h"
#include "ScheduleManager.h"
#include "TaskManager.h"

struct dirent* FolderPointer;

struct Address PreviousAddress[MAX_ADDRESS_HISTORY];

int AddressLength;

char FolderAddress[MAX_STRING_SIZE];
char IntegrationFolderAddress[MAX_STRING_SIZE];
char CmdFeedback[MAX_STRING_SIZE];

bool Exit;
bool FileDetails = false;
bool Integration;

// Manager Functions

void FileManager(bool IsIntegration) {
	strcpy(FolderAddress, "/");
	strcpy(CmdFeedback, "Welcome to the File Manager. Please Select a Command.");
	Exit = false;
	AddressLength = 0;

	Integration = IsIntegration;

	DIR* Folder = opendir(FolderAddress);;

	while (Exit == false) {
		Folder = opendir(FolderAddress);

		if (!Folder) { // Reverts to the previous address if the new one is invalid
			ExitFolder();
			Folder = opendir(FolderAddress);
			strcpy(CmdFeedback, "That was an invalid Entry. Please try again.");
		}

		clrscr();
		ManagerDisplay(Folder);
		ManagerCommands();
		closedir(Folder);
	}
}

void ManagerDisplay(DIR* Folder) {
	printf("File Manager\n");
	printf("###############################\n");
	printf("List of commands:\n");
	printf("a) Enter a Folder\n");
	printf("b) Close Folder\n");
	printf("c) Create New Folder\n");
	printf("d) Delete Folder\n");
	printf("e) Search For File\n");
	printf("f) Open a Text File\n");
	printf("g) Create a New Text File\n");
	printf("h) Delete a Text File\n");
	if (FileDetails) {
		printf("i) Disable Extra File Details\n");
	}
	else {
		printf("i) Enable Extra File Details\n");
	}
	printf("j) Exit File Manager\n");

	if (Integration == true) {
		printf("\nk) Use Current folder for Module Data\n\n");
	}

	printf("###############################\n");
	printf("Folder: %s\n", FolderAddress);
	printf("###############################\n");

	if (FileDetails) {
		int FileNumbering = 0;
		while ((FolderPointer = readdir(Folder)) != NULL) { // Extra details such as whether the contents are files or folders and their numbering displayed
			if ((strcmp(FolderPointer->d_name, ".") != 0 && strcmp(FolderPointer->d_name, "..") != 0)) {
				FileNumbering += 1;
				if ((int)FolderPointer->d_type == FOLDER_ID_NUMBER) {
					printf("%d.  Folder  -  %s\n", FileNumbering, FolderPointer->d_name);
				}
				else {
					printf("%d.  File    -  %s\n", FileNumbering, FolderPointer->d_name);
				}
			}
		}
	}
	else {
		while ((FolderPointer = readdir(Folder)) != NULL) { // Default look for the file manager, for keeping it simple
			if ((strcmp(FolderPointer->d_name, ".") != 0 && strcmp(FolderPointer->d_name, "..") != 0))
				printf("%s\n", FolderPointer->d_name);
		}
	}

	printf("###############################\n");
	printf("\n%s\n", CmdFeedback);
	printf("\nEnter Option: ");
}

void ManagerCommands() {

	strcpy(CmdFeedback, "");
	char Input = MenuInput("abcdefghijk");

	switch (Input) {
	case 'a':
		OpenFolder();
		break;
	case 'b':
		ExitFolder();
		break;
	case 'c':
		CreateFolder();
		break;
	case 'd':
		DeleteFolder();
		break;
	case 'e':
		SearchForFolder();
		break;
	case 'f':
		TextFileLoop();
		break;
	case 'g':
		CreateText();
		break;
	case 'h':
		DeleteText();
		break;
	case 'i':
		if (FileDetails) {
			FileDetails = false;
		}
		else {
			FileDetails = true;
		}
		break;
	case 'j':
		Exit = true;
		break;
	case 'k':
		if (Integration == true) {
			strcpy(IntegrationFolderAddress, FolderAddress);
			Exit = true;
		}
		break;
	}
}

// Command Functions

void OpenFolder() {
	char* Input = InputName();
	if (AddressLength < 25) { // Stores the last file they were in a long array incase of a invalid input or the user wants to backtrack.
		strcpy(PreviousAddress[AddressLength].FolderName, FolderAddress);
		AddressLength += 1;
	}
	strcat(FolderAddress, Input);
	strcat(FolderAddress, "/");
}

void CreateFolder() {
	int Check;
	char* Input = InputName();
	char* Folder = (char*)malloc(1 + strlen(FolderAddress) + strlen(Input));
	strcpy(Folder, FolderAddress);
	strcat(Folder, Input);
	Check = mkdir(Folder, 0777);
	if (!Check)
		strcpy(CmdFeedback, "Folder Created");
	else {
		strcpy(CmdFeedback, "Failed to create Folder");
	}
}

void DeleteFolder() {
	int Check;
	char* Input = InputName();
	char* Folder = (char*)malloc(1 + strlen(FolderAddress) + strlen(Input));
	strcpy(Folder, FolderAddress);
	strcat(Folder, Input);
	Check = rmdir(Folder, 0777);
	if (!Check)
		strcpy(CmdFeedback, "Folder Deleted");
	else {
		strcpy(CmdFeedback, "Failed to delete Folder");
	}
}

void ExitFolder() {
	if (AddressLength < 1) {
		strcpy(CmdFeedback, "You cannot exit beyond this folder.");
	}
	else {
		AddressLength -= 1;
		strcpy(FolderAddress, PreviousAddress[AddressLength].FolderName);
		strcpy(CmdFeedback, "Successfully went back.");
	}
}

void SearchForFolder() {
	char SearchFolderAddress[MAX_STRING_SIZE];
	strcpy(SearchFolderAddress, FolderAddress);
	strcpy(CmdFeedback, "Search Results:");
	SearchAlgorithm(InputName(), SearchFolderAddress); // Runs my search algorithm function
}

void CreateText() {
	FILE* FilePointer;
	char* Input = InputName();
	char* File = (char*)malloc(1 + strlen(FolderAddress) + strlen(Input) + 4);
	strcpy(File, FolderAddress);
	strcat(File, Input);
	strcat(File, ".txt");
	if (FilePointer = fopen(File, "a")) {
		strcpy(CmdFeedback, "Text File Created");
	}
	else {
		strcpy(CmdFeedback, "Failed to create Text File.");
	}
	fclose(FilePointer);
}

void DeleteText() {
	char* Input = InputName();
	char* File = (char*)malloc(1 + strlen(FolderAddress) + strlen(Input) + 4);
	strcpy(File, FolderAddress);
	strcat(File, Input);
	strcat(File, ".txt");
	int Test = remove(File);
	if (!Test) {
		strcpy(CmdFeedback, "Text File Deleted");
	}
	else {
		strcpy(CmdFeedback, "Failed to delete Text File.");
	}
}

// Text File Manager Functions

void TextFileLoop() {
	FILE* FilePointer;
	char* Input = InputName();
	char* File = (char*)malloc(1 + strlen(FolderAddress) + strlen(Input) + 4);
	strcpy(File, FolderAddress);
	strcat(File, Input);
	strcat(File, ".txt");
	bool ExitTM = false;
	if (FilePointer = fopen(File, "r")) { // We need an additional loop for the multiple options for text file editor like editing or exiting
		fclose(FilePointer);
		while (ExitTM == false) {
			clrscr();
			TextFileDisplay(File);
			char Input = MenuInput("ab");
			switch (Input) {
			case 'a':
				TextFileEditText(File);
				break;
			case 'b':
				ExitTM = true;
				break;
			}
		}
	}
	else {
		strcpy(CmdFeedback, "Failed to Open Text File");
	}
}

void TextFileDisplay(char* File) {
	printf("Text File Editor\n");
	printf("###############################\n");
	printf("List of commands:\n");
	printf("a) Edit Text File\n");
	printf("b) Exit\n");
	printf("###############################\n");
	printf("Folder: %s\n", File);
	printf("###############################\n");
	FILE* FilePointer;
	char Text[MAXCHAR];
	FilePointer = fopen(File, "r");
	while (fgets(Text, MAXCHAR, FilePointer) != NULL)
		printf("%s", Text);
	fclose(FilePointer);
	printf("###############################\n");
	printf("\n%s\n", CmdFeedback);
	printf("\nEnter Option: ");
}

void TextFileEditText(char* File) {
	char Input[MAX_SENTENCE_SIZE];
	FILE* FilePointer;
	FilePointer = fopen(File, "w");
	printf("\nEnter your text: ");
	fgets(Input, sizeof(Input), stdin);
	fprintf(FilePointer, "%s", Input);
	fclose(FilePointer);
	strcpy(CmdFeedback, "Text written to Document");
}

char* InputName() {
	static char Input[MAX_STRING_SIZE];
	printf("\nPlease enter a valid name: ");
	gets(Input);
	return Input;
}

char* MenuInput(char* AcceptableInput) { // Proper Menu Input
	char Letter;
	bool Acceptable = false;
	while (!Acceptable) {
		Letter = getchar();
		if (getchar() != '\n') {
			FixInput();
		}
		else {
			if (strchr(AcceptableInput, Letter) != NULL) {
				Acceptable = true;
			}
		}
	}
	return Letter;
}

void FixInput(void) {
	bool Fixed = false;
	while (!Fixed) {
		if (getchar() == '\n')
			Fixed = true;
	}
}

void clrscr() {
	system("@cls||clear");
}

void SearchAlgorithm(char* Search, char SearchFolderAddress[]) {
	struct dirent* SearchFolderPointer = NULL;
	DIR* SearchFolder = opendir(SearchFolderAddress);
	if (!SearchFolder) {
	}
	else {
		while ((SearchFolderPointer = readdir(SearchFolder)) != NULL) {
			char* FileName = SearchFolderPointer->d_name;
			if ((strcmp(FileName, Search) == 0)) {
				char* Temp = CmdFeedback;
				strcpy(CmdFeedback, Temp);
				strcat(CmdFeedback, "  Match:");
				strcat(CmdFeedback, SearchFolderAddress);
				strcat(CmdFeedback, FileName);
			}
			int CheckIfFolder = (int)SearchFolderPointer->d_type;
			if (CheckIfFolder == FOLDER_ID_NUMBER) {
				if (strcmp(FileName, ".") != 0 && strcmp(FileName, "..") != 0) {
					char NewSearchFolderAddress[MAX_SENTENCE_SIZE];
					strcpy(NewSearchFolderAddress, SearchFolderAddress);
					strcat(NewSearchFolderAddress, FileName);
					strcat(NewSearchFolderAddress, "/");
					printf("%s\n", NewSearchFolderAddress);
					SearchAlgorithm(Search, NewSearchFolderAddress);
				}
			}
		}
		closedir(SearchFolder);
	}
	free(SearchFolderPointer);
}


void ScheduleManagerSave(SCHEDULE SaveData) {
	FILE* FilePointer;
	FileManager(true);

	printf("\nSaving Schedule Manager Data: \n");

	char* Input = InputName();
	char* File = (char*)malloc(1 + strlen(IntegrationFolderAddress) + strlen(Input) + 4);
	strcpy(File, IntegrationFolderAddress);
	strcat(File, Input);
	strcat(File, ".txt");

	if ((FilePointer = fopen(File, "wb")) != NULL)
	{
		for (int i = 0; i < MAX_YEARS; i++) {
			Year Temp = SaveData->Year[i];
			fwrite(&Temp, sizeof(Year), 1, FilePointer);
		}
		fclose(FilePointer);
	}
	else {
		printf("Failed");
	}

}

void ScheduleManagerLoad(SCHEDULE Scheduler) {
	FILE* FilePointer;
	FileManager(true);
	printf("\nPreparing to open file Schedule Manager Data: \n");
	char* Input = InputName();

	char* File = (char*)malloc(1 + strlen(IntegrationFolderAddress) + strlen(Input) + 4);
	strcpy(File, IntegrationFolderAddress);
	strcat(File, Input);
	strcat(File, ".txt");

	if ((FilePointer = fopen(File, "rb")) != NULL) {
		for (int i = 0; i < MAX_YEARS; i++) {
			Year Temp;
			fread(&Temp, sizeof(Year), 1, FilePointer);
			Scheduler->Year[i] = Temp;
		}
		fclose(FilePointer);
	}
	else {
		printf("Failed");
	}
}

void TaskManagerSave(struct CompiledTasks SaveData) {
	FILE* FilePointer;
	FileManager(true);

	printf("\nSaving Schedule Manager Data: \n");

	char* Input = InputName();
	char* File = (char*)malloc(1 + strlen(IntegrationFolderAddress) + strlen(Input) + 4);
	strcpy(File, IntegrationFolderAddress);
	strcat(File, Input);
	strcat(File, ".txt");

	if ((FilePointer = fopen(File, "wb")) != NULL)
	{
		struct CompiledTasks Temp = SaveData;
		fwrite(&Temp, sizeof(struct CompiledTasks), 1, FilePointer);
		fclose(FilePointer);
	}
	else {
		printf("Failed");
	}

}

struct CompiledTasks TaskManagerLoad() {
	FILE* FilePointer;
	FileManager(true);
	printf("\nPreparing to open file Schedule Manager Data: \n");
	char* Input = InputName();

	char* File = (char*)malloc(1 + strlen(IntegrationFolderAddress) + strlen(Input) + 4);
	strcpy(File, IntegrationFolderAddress);
	strcat(File, Input);
	strcat(File, ".txt");

	struct CompiledTasks Temp;

	if ((FilePointer = fopen(File, "rb")) != NULL) {
		struct CompiledTasks Temp2;
		fread(&Temp2, sizeof(struct CompiledTasks), 1, FilePointer);
		Temp = Temp2;
		fclose(FilePointer);
	}
	else {
		printf("Failed");
	}
	return Temp;
}