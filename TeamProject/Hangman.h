#pragma once

#define MAXINPUT    40

int getAnswer();
void play();
void getLetter();
void displayWin();
void displayLoss();
int compareAns();
void showGuesses();

//Declare Mock Functions For Testing 
// char mock_getLetter(char* TESTguessed_Letter);



// Data for a keyword and guesses 
struct data {
	char unconfirmedLetter[MAXINPUT];
	char correctLetters[MAXINPUT];
	char letters[MAXINPUT];
	int incorrectLetters;
};

struct keyword {
	char wordToGuess[MAXINPUT];
};

struct data letterData; // Create the structure for the guesses 
struct keyword answerWord; // Create the structure for the keyword to be stored
