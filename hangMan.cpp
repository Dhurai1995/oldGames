#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<cctype>

int main()
{
	const int MAX_WRONG = 8;
	std::vector<std::string> words;
	words.push_back("WALL");
	words.push_back("ROOM");
	words.push_back("GLASS");

	srand(static_cast<unsigned int>(time(0)));
	random_shuffle(words.begin(), words.end());

	const std::string THE_WORD = words[0];
	int wrong = 0;

	std::string soFar(THE_WORD.size(), '-');
	std::string used = "";

	std::cout << "Welcome to hangman \n" << std::endl;

	// Entering the main loop

	while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
	{
		std::cout << "\n\nYou have " << MAX_WRONG - wrong << " Words left\n" << std::endl;
		std::cout << "You have Used the following letter: " << used << std::endl;
		std::cout << "\nSo far, the word is: " << soFar << "\n"<<std::endl;

		char guess;
		std::cout << "Enter your guess: ";
		std::cin >> guess;
		guess = toupper(guess);

		while (used.find(guess) != std::string::npos)
		{
			std::cout << "You have already tried\n" << guess << std::endl;
			std::cout << "Try again: " << std::endl;
			std::cin >> guess;
			guess = toupper(guess);
		}

		used += guess;

		if (THE_WORD.find(guess) != std::string::npos)
		{
			std::cout << "Thats right " << guess << " is in the word\n\n";
			for (unsigned int i = 0; i < THE_WORD.length(); ++i)
			{
				if (THE_WORD[i] == guess)
					soFar[i] = guess;
			}
		}
		else
		{
			std::cout << "Wrong prediction\n" << std::endl;
			++wrong;
		}
	}

	if (wrong == MAX_WRONG)
	{
		std::cout << "You have been hanged" << std::endl;
	}
	else
	{
		std::cout << "You have guesses it" << std::endl;
	}

	std::cout << "The word is " << THE_WORD << std::endl;
}