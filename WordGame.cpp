#include<iostream>
#include<ctime>
#include<cstdlib>

int main()
{
	enum fields { WORD, HINT, NUM_FIELDS };
	const int NUM_WORD = 2;
	const std::string WORDS[NUM_WORD][NUM_FIELDS] =
	{
		{"wall","look at that wlall"},
		{"glass","look at that glass"}
	};

	srand(static_cast<unsigned int>(time(0)));
	int choice = (rand() % NUM_WORD);
	std::string theWord = WORDS[choice][WORD];
	std::string theHint = WORDS[choice][HINT];

	// Creat the jumble of the word

	std::string jumble = theWord;
	int length = jumble.size();

	for (int i = 0; i < length; i++)
	{
		int INDEX1 = (rand() % length);
		int INDEX2 = (rand() % length);
		int temp = jumble[INDEX1];
		jumble[INDEX1] = jumble[INDEX2];
		jumble[INDEX2] = temp;
	}

	//Wlcome the player

	std::cout << "\t\t\t Welcome to world of Jumble!!\n\n";
	std::cout << "Unscramble the letter to make a word" << std::endl;
	std::cout << "Enter 'hint' to get some hint" << std::endl;
	std::cout << "enter 'quit' to quit the game" << std::endl;
	std::cout << "The jumble is:" << jumble;

	std::string guess;
	std::cout << "\n\n Enter your guess" << std::endl;

	do
	{
		std::cin >> guess;

		if (guess == theWord)
			std::cout << "You are correct" << std::endl;
		else if (guess == "quit")
		{
			std::cout << "Thanks for playing" << std::endl;
			guess = theWord;
		}
		else if (guess == "hint")
		{
			std::cout << theHint << std::endl;
			std::cout << "Try again:" << std::endl;
		}
		else
			std::cout << "Its incorrect\n" << std::endl;
	} while (guess != theWord);

}