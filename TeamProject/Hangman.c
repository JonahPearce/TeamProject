// Hangman Game
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Hangman.h"


#define MAXATTEMPTS 6

#pragma warning(disable:4996) // Remove warning with strncpy

// All Potential Keywords (from a random word generator) 
char words[MAXINPUT][MAXINPUT] = { "identical", "chocolate", "beautiful", "happiness", "challenge", "adventure", "dangerous", "irregular", "pollution", "president", "undefined", "pineapple", "wrestling",
"congruent", "community", "structure", "invisible", "packaging", "crocodile", "begining", "integrity", "everybody", "attention", "lightning", "chemistry", "agreement", "architect",
"deception", "generator", "perimeter", "radiation", "direction", "moustache", "hurricane", "scorching", "scientist", "astronaut", "legendary", "brilliant", "dedicated" };

int gameModule() {
    // Initialization
    letterData.incorrectLetters = 0;
    memset(&letterData, 0, sizeof(letterData));
    fflush(stdin); // Flush input 
    fflush(stdout); // Fluch output 
    getchar(); // Absorb the newline from the menu 

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

    // Welcoming message and rules 
    puts("--------------- Welcome to Hangman! ---------------");
    puts("You can enter up to six incorrect letters!\n");

    //Generate a random number (to select a keyword) 
    srand(time(NULL));

    int randomNumber = rand() % ((40 + 1) - 1) + 1;

    strncpy(letterData.letters,
        words[randomNumber], strlen(words[randomNumber]));

    // Store the keyword in a structure for end reveal 
    strncpy(answerWord.wordToGuess,
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
    puts("\nThe word is: ");
    for (int j = 0; j < ansLength; ++j) {
        printf("%c", letterData.correctLetters[j]);
    }
    printf("\n");
}

void displayWin() {
    // Display winning statement 
    puts("You win!");
    // Display the keyword 
    printf("\nThe word was %s.\n\n", answerWord.wordToGuess);
}

void displayLoss() {
    // Display losing statement 
    puts("You lose!");
    // Display the keyword 
    printf("\nThe word was %s.\n\n", answerWord.wordToGuess);
}