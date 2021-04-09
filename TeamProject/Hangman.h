#pragma once

#define MAXINPUT    40

int getAnswer();
void play();
void getLetter();
void displayWin();
void displayLoss();
int compareAns();
void showGuesses();


// Data for a keyword and guesses 
struct data {
	char unconfirmedLetter[MAXINPUT];
	char correctLetters[MAXINPUT];
	char letters[MAXINPUT];
	int incorrectLetters;
};

struct data letterData; // Create the structure for the guesses 


// All Potential Keywords (from a random word generator) 
char words[MAXINPUT][MAXINPUT] = { "software", "allocation", "concert", "lecture", "exotic", "formation", "directory", "telephone", "sequence", "classroom", "example", "realize", "cinema",
"restaurant", "hemisphere", "workshop", "climate", "crossing", "economy", "helicoptor", "definition", "standard", "exploration", "performer", "service", "display", "confuse",
"electronics", "computer", "skilled", "interface", "transparent", "conscience", "coverage", "technique", "calculation", "temporary", "executive", "accountant", "athlete"};
