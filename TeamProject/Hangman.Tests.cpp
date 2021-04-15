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
int mockPlayCompareAns(char* incorrectMockLetters, char* mockKeyword) {

	// Initialization
	letterData.incorrectLetters = 0;
	memset(&letterData, 0, sizeof(letterData));


	// Copy guessedLetters into letterdata
	strncpy(letterData.unconfirmedLetter, incorrectMockLetters,
		strlen(incorrectMockLetters));

	// Copy keyword to letterdata 
	strncpy(letterData.letters, mockKeyword, strlen(mockKeyword));

	int ansLength = strlen(letterData.letters); // Length of keyword

	char guessedLetter = letterData.unconfirmedLetter[0];

	bool matchFound = false;

	// Compare all letters in answer to the letter in guessed letters 
	// If incorrect, add 1 to .incorrectLetters
	for (int y = 0; y < ansLength; y++) {
		if (guessedLetter != letterData.letters[y]) {
			letterData.incorrectLetters++;
		}
	}

	// Variable determines exit status 
	int gameOver = 0;

	int MAXATTEMPTS = 5;

	// Did we get a match?
	if (!matchFound) {
		letterData.incorrectLetters++;

		// Check to see if we lost
		if (letterData.incorrectLetters > MAXATTEMPTS)
		{
			return 2;
		}
	}
}


// Mock Menu Function
int mockMenu(char selection) {

	switch (selection)
	{
	case 'a':
		return 1;
		break;
	case 'b':
		return 2;
		break;
	case 'c':
		return 3;
		break;
	case 'd':
		return 4;
		break;
	case 'q':
		return 5;
		break;
	default:
		return 6;
		break; 
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

		TEST_METHOD(T002_HG_REQ_PROG_001_Startup)
		{
			//Arrange 
			char mockSelection = 'd'; 

			//Act
			int returnValue = mockMenu(mockSelection);

			//Assert 
			Assert::AreEqual(4, returnValue); 
		}

		TEST_METHOD(T003_HG_REQ_PROG_002_Shutdown)
		{
			//Arrange
			char guessedLetters[MAXINPUT] = { '!', '!', '!', '!', '!', '!' };
			char mockKeyword[MAXINPUT] = { "identical" };

			//Act
			int returnedValue = mockPlayCompareAns(guessedLetters, mockKeyword);

			//Assert 
			// A return value of 2 indicates a loss 
			Assert::AreEqual(2, returnedValue);

		}
	};
}