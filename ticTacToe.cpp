#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

const char EMPTY = ' ';
const char NO_ONE = 'N';
const char X = 'X';
const char O = 'O';
const char TIE = 'T';


//funtion declaretion
void instructions();
char humanPiece();
char askYesNo(std::string question);
char opponent(char piece);
void displayBoard(const std::vector<char>& board);
char winner(const std::vector<char>& board);
int askNumber(std::string question, int high, int low = 0);
bool isLegal( int move, const std::vector<char>& board);
int humanMove(const std::vector<char>& board, char human);
int computerMove(std::vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

int main()
{
	int move;
	const int NUM_SQUARES = 9;
	std::vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;

	displayBoard(board);

	while (winner(board) == NO_ONE)
	{
		if (turn == human)
		{
			move = humanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}

	announceWinner(winner(board), computer, human);
	return 0;

}

void instructions()
{
	std::cout << "Welcome to the ultimate man-machine showdoen: Tic-tac-toe.\n";
	std::cout << "-- WHere human brain is put against silicon processor\n\n";
	std::cout << "Make your move known by entering a number: 0 - 8. The number \n";
	std::cout << "Corresponds to the desired board positionm as illustrated as:\n\n";
	std::cout << " 0 | 1 | 2\n";
	std::cout << " 3 | 4 | 5\n";
	std::cout << " 6 | 7 | 8\n\n";
	std::cout << "prepare youself, human, The battle is about to start. \n\n";
}

char humanPiece()
{
	char go_first = askYesNo("Do you require the first move? ");
	if (go_first == 'Y')
	{
		std::cout << "\n Take the first move human \n";
		return X;
	}
	else
	{
		std::cout << "\n Your bravery will be your undoing. \n";
		return O;
	}
}

char askYesNo(std::string question)
{
	char response;
	do
	{
		std::cout << question << std::endl;
		std::cin >> response;
	} while ((response != 'Y') && (response != 'N'));
	return response;
}

char opponent(char piece)
{
	if (piece == 'X')
		return O;
	else
		return X;
}

void displayBoard(const std::vector<char>& board)
{
	std::cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	std::cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	std::cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	std::cout << "\n\n";
}


char winner(const std::vector<char>& board)
{
	const int WINNING_ROWS[8][3] = { {0, 1, 2 },
	{3, 4, 5 } ,
	{6, 7, 8 } ,
	{0, 3, 6 } ,
	{1, 4, 7 } ,
	{2, 5, 8 } ,
	{0, 4, 8 } ,
	{2, 4, 6 } };

	const int TOTAL_ROWS = 8;

	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if (((board[WINNING_ROWS[row][0]]) != EMPTY) && (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) && (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}

	if (count(board.begin(), board.end(), EMPTY) == 0)
		return TIE;
	return NO_ONE;
}

int humanMove(const std::vector<char>& board, char human)
{
	int move = askNumber("Where will you move?:", (board.size() - 1));
	while (!isLegal(move, board))
	{
		std::cout << "\nThat square is already occupied, foolish human.\n";
		move = askNumber("WHere will you move", (board.size() - 1));
	}
	std::cout << "Fine...\n";
	return move;
}

int askNumber(std::string question, int high, int low)
{
	int number;
	do
	{
		std::cout << question << " (" << low << " - " << high << "):";
		std::cin >> number;
	} while (number > high || number < low);

	return number;
}

int computerMove(std::vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;

	while (!found && move < board.size())
	{
		if (isLegal(move, board))
		{
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!found)
			++move;
	}

	if (!found)
	{
		move = 0;
		char human = opponent(computer);

		while ((!found) && (move < board.size()))
		{
			if (isLegal(move, board))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!found)
				++move;
		}
	}

	if (!found)
	{
		move = 0;
		unsigned int i = 0;

		const int BEST_MOVES[] = { 4,0,2,6,8,1,3,5,7 };
		while ((!found) && (move < board.size()))
		{
			move = BEST_MOVES[i];
			if (isLegal(move, board))
			{
				found = true;
			}
			++i;
		}

	}

	std::cout << "I shall take the square number :" << move << std::endl;
	return move;
}

inline bool isLegal( int move, const std::vector<char>& board)
{
	return (board[move] == EMPTY);
}

void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		std::cout << winner << "'s won!\n";
		std::cout << "As I predicted, human, I am triumphant once more --proof\n";
		std::cout << "That computers are superior to human in all regards.\n";
	}

	else if (winner == human)
	{
		std::cout << winner << "'s won!\n";
		std::cout << "No No ! It cannot be!! \n";
		std::cout << "But never again.\n";
	}
	else
	{
		std::cout << "Its a tie\n";
		std::cout << "You were most lucky,human and somehow managed to tie me \n";
		std::cout << "Celebrate.. for this is the best you will ever achieve.\n";
	}
}
