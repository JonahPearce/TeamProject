#include <dirent.h>

// Important Constant Numbers
#define MAX_LINE 256
#define MAX_STRING_SIZE 1000
#define MAX_SENTENCE_SIZE 1000
#define MAX_ADDRESS_HISTORY 50
#define FOLDER_ID_NUMBER 16384

struct Address {
	char FolderName[MAX_STRING_SIZE];
};

void FileManager(bool);
void ManagerDisplay(DIR*);
void ManagerCommands();

void OpenFolder();
void CreateFolder();
void DeleteFolder();
void ExitFolder();
void SearchForFolder();
void CreateText();
void DeleteText();

void TextFileLoop();
void TextFileDisplay(char*);
void TextFileEditText(char*);

char* InputName();
char* MenuInput(char*);
void FixInput();
void clrscr();
void SearchAlgorithm(char*, char[]);
