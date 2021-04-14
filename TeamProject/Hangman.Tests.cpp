#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "Hangman.h"
} 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Mock Functions
// Mock Function of getLetter - takes a char pointer parameter 
char mock_getLetter(char* TESTguessed_Letter) {

	char* newLetter = letterData.unconfirmedLetter;

	strncpy(newLetter, TESTguessed_Letter, strlen(TESTguessed_Letter));

	// Remove the newline from letter
	newLetter[strlen(letterData.unconfirmedLetter) - 1] = 0;

	return newLetter[0];

}

// Mock Function of compareAns() 






// Mock play() function
int mockPlayCompareAns(int guessedLetters) {

	// Copy guessedLetters into letterdata
	letterData.incorrectLetters = guessedLetters;

	// Variable determines exit status 
	int gameOver = 0;

	// While !gameOver, loop through displaying guesses/dashes, and getting the letter
	while (!gameOver) {
		// Determine if the word has been guessed 
		gameOver = compareAns();
		// If the player has guessed the word, display winning message 
		if (gameOver == 1) {
			puts("You win!");
		}
		else if (gameOver == 2) {
			puts("You lose!");
		}
	}

	int MAXATTEMPTS = 5;

	// Check to see if we lost
	if (letterData.incorrectLetters > MAXATTEMPTS)
	{
		return 2;
	}

	// Check to see if we won
	if (strcmp(letterData.letters, letterData.correctLetters) == 0)
	{
		return 1;
	}

	return 0;

}



namespace HangmanGameTests
{
	TEST_CLASS(HangmanGameTests)
	{
	public:

		// Testing the ability to get a character input 
		TEST_METHOD(T001_getLetter_sameLetter)
		{
			//Arrange
			char letter_input = 'x';
			char* letter_input_pointer = &letter_input;

			//Act
			char returned_letter = mock_getLetter(letter_input_pointer);

			//Assert 
			Assert::AreEqual('x', returned_letter);
		}

		TEST_METHOD(T002_HG_REQ_PROG_002_Shutdown)
		{
			//Arrange
			int guessedLetters = 6;

			//Act
			int returnedValue = mockPlayCompareAns(guessedLetters);

			//Assert 
			// A return value of 2 indicates a loss 
			Assert::AreEqual(2, returnedValue);

		}
	};
}