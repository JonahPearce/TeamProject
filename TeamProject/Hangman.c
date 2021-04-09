// Hangman Game
#include <stdio.h>
#include <string.h>
#include "Source.h"
#include <stdbool.h>

#define MAXINPUT    30
#define MAXATTEMPTS 6


int main() {
    // Initialization
    letterData.incorrectLetters = 0;

    // Get word to guess
    getAnswer();

    // Begin the game 
    play();

    return 0;
}

void play() {
    // Variable determines exit status 
    int gameOver = 0;

    // While !gameOver, loop through displaying guesses/dashes, and getting the letter 
    while (!gameOver) {
        // Determine if the word has been guessed 
        gameOver = compareAns();
        // If the player has guessed the word, display winning message 
        if (gameOver == 1) {
            displayWin();
            return;
        }
        else if (gameOver == 2) {
            displayLoss();
            return;
        }

        // Display guesses and dashes 
        showGuesses();

        // Get user letter guess 
        getLetter();
    }
}

// Function to get the answer for the game 
int getAnswer() {
    //char* newAnswer = letterData.letters;

    //Generate a random number (to select a keyword) 
    srand(time(NULL));

    int randomNumber = rand() % ((40 + 1) - 1) + 1;
   
    strncpy(letterData.letters,
        words[randomNumber], strlen(words[randomNumber]));

    // Initialize correctLetters
    int ansLength = strlen(letterData.letters);
    for (int j = 0; j < ansLength; ++j) {
        letterData.correctLetters[j] = '_';
    }

    return 0;
}

// Function to get players letter guess 
void getLetter() {
    char* newLetter = letterData.unconfirmedLetter;

    puts("Please enter your letter guess: ");
    fgets(&letterData.unconfirmedLetter, MAXINPUT, stdin);
    // Remove the newline from letter
    newLetter[strlen(letterData.unconfirmedLetter) - 1] = 0;
}

int compareAns() {
    int ansLength = strlen(letterData.letters);

    char guessedLetter = letterData.unconfirmedLetter[0];

    bool matchFound = false;

    // TODO: make sure they entered a letter

    // Identify correct letters and move to guessedLetters.correctLetters  
    // Compare all letters in answer to the letter in guessed letters 
    for (int y = 0; y < ansLength; y++) {
        if (guessedLetter == letterData.letters[y]) {
            letterData.correctLetters[y] = guessedLetter;
            matchFound = true;
        }
    }

    // Did we get a match?
    if (!matchFound) {
        letterData.incorrectLetters++;

        // Check to see if we lost
        if (letterData.incorrectLetters > MAXATTEMPTS)
        {
            return 2;
        }
    }

    // Check to see if we won
    if (strcmp(letterData.letters, letterData.correctLetters) == 0)
    {
        return 1;
    }

    return 0;
}

// Function to display guesses/dashes
void showGuesses() {
    int ansLength = strlen(letterData.letters);

    // Print word with "-" for missing letters 
    puts("The word is : ");
    for (int j = 0; j < ansLength; ++j) {
        printf("%c", letterData.correctLetters[j]);
    }
    printf("\n");
}

void displayWin() {
    puts("You win!");
}

void displayLoss() {
    puts("You lose!");
}