#include <iostream>
#include <cstdlib>
#include "TicTacToe.h"

//================================================================================================

/*bool isTie(char board[], int limit)
{
	if (limit == 1)
	{
		char tie = getWinner(board);
		if (tie == 'd')
		{
			std::cout << "It's a tie!\n";
			return true;
		}
	}

	return false;
}*/

//================================================================================================

// Contains the game logic
// Returns prematurely on bad input
void playGame()
{

	char board[9] = {
				 ' ', ' ', ' ',
				 ' ', ' ', ' ',
				 ' ', ' ', ' '
	};

	const char X = 'X';
	const char O = 'O';
	char winner = ' ';

	bool gameOver = false;

	displayBoard(board);

	// Let Player choose between Heads or Tails
	std::cout << "Enter 1 for Heads or enter 0 (zero) for Tails: ";
	int choice;
	std::cin >> choice;

	if (choice != 0 && choice != 1)
	{
		return;  // -1 indicates failure
	}
	else
	{
		// Choose a player to go first at random
		srand(static_cast<unsigned int>(time(0)));

		int coinFlip = rand();

		int coinResult = (coinFlip % 2);  // Remainder will be 0 (Tails) or 1 (Heads)

		char player, computer;
		int limit = 8; // There can be a possible 9 turns

		// Game loop
		if (choice == coinResult)
		{
			player = X;
			computer = O;

			std::cout << "Player to go first...\n\n";

			while (!gameOver && limit > 0)
			{
				humanTurn(player, computer, board);
				gameOver = checkGameState(board);

				limit--;
				//gameOver = isTie(board, limit);
				

				if (!gameOver)
				{
					computerTurn(player, computer, board);
					gameOver = checkGameState(board);
				}

				limit--;
				//gameOver = isTie(board, limit);
			}

			if (!gameOver)
				std::cout << "It's a tie!\n";
		}
		else
		{
			computer = X;
			player = O;

			std::cout << "Computer to go first...\n";

			while (!gameOver && limit > 0)
			{
				computerTurn(player, computer, board);
				gameOver = checkGameState(board);

				limit--;
				//gameOver = isTie(board, limit);

				if (!gameOver)
				{
					humanTurn(player, computer, board);
					gameOver = checkGameState(board);
				}

				limit--;
				//gameOver = isTie(board, limit);
			}

			if (!gameOver)
				std::cout << "It's a tie!\n";
		}
	}
}

//================================================================================================

// Print instructions
void instructions()
{
	std::cout << "Welcome to Tic-Tac-Toe.\n\n";
	std::cout << "The players will first pick between heads and tails.\n";
	std::cout << "Once the coin is flipped, if it lands on the chosen face, the corresponding player goes first.\n";
	std::cout << "The winner of the coin flip will be assigned X.\n";
	std::cout << "The player's will then take turns in choosing positions on the board.\n";
	std::cout << "The winner will have three X's or O's in a row (this includes a column or diagonal sequence).\n";
	std::cout << "If no one has won, the game is a draw and you'll have a chance to play again.\n\n";
	std::cout << "Have fun - and play nice!\n\n";
}

//================================================================================================

// Display the current state of the game
void displayBoard(char board[])
{
	std::cout << '\n';
	std::cout << board[0] << '|' << board[1] << '|' << board[2] << std::endl;
	std::cout << "-----\n";
	std::cout << board[3] << '|' << board[4] << '|' << board[5] << std::endl;
	std::cout << "-----\n";
	std::cout << board[6] << '|' << board[7] << '|' << board[8] << std::endl;
	std::cout << '\n';
}

//================================================================================================

// Calculate a winner
// Returns the winner (X or O)
char getWinner(char board[])
{
	// Possible winning positions on board
	int winnings[8][3] = { {0, 1, 2},
					   {3, 4, 5},
					   {6, 7, 8},
					   {0, 3, 6},
					   {1, 4, 7},
					   {2, 5, 8},
					   {0, 4, 8},
					   {2, 4, 6} };

	for (int i = 0; i < 8; i++)
	{
		if (board[winnings[i][0]] != ' ' && board[winnings[i][0]] == board[winnings[i][1]] &&
				board[winnings[i][1]] == board[winnings[i][2]])
		{
			return board[winnings[i][2]];
		}
	}

	return 'd'; // no winners yet
}

//================================================================================================

// Checks if there has been a winner
// Returns true if there is a winner
// Returns false if no winner found
bool checkGameState(char board[])
{
	if (getWinner(board) != 'd')
	{
		std::cout << "The winner is the " << getWinner(board) << "'s!\n";
		return true;
	}

	return false;
}

//================================================================================================

void humanTurn(char player, char computer, char board[])
{
	std::cout << "Choose a position between 0 and 8: \n";

	int position;
	std::cin >> position;

	if (position < 0 || position > 8)
		return;   // indicates failure

	// Is the board position free?
	while (board[position] != ' ')
	{
		std::cout << "Position not free! Try again.\n";
		std::cout << "Choose a position between 0 and 8: \n";
		std::cin >> position;
	}

	board[position] = player;
	displayBoard(board);
}

//================================================================================================

void computerTurn(char player, char computer, char board[])
{
	std::cout << "Computer's turn...\n";

	// search a possible winning position for the computer
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == ' ')
		{
			board[i] = computer;
			if (getWinner(board) == computer)
			{
				board[i] = computer;
				displayBoard(board);
				return;
			}
			board[i] = ' ';   // reset element back to "empty"
		}
	}

	// search for a possible winning position for the player
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == ' ')
		{
			board[i] = player;
			if (getWinner(board) == player)
			{
				board[i] = computer;
				displayBoard(board);
				return;
			}
			board[i] = ' ';  // reset element back to "empty"
		}
	}

	// If there are no "winning" solutions
	// search for an empty position on the board at random
	int cmpTurn = (rand() % 8) + 1;

	// If element is empty, go there
	while (board[cmpTurn] != ' ')
	{
		cmpTurn = (rand() % 8) + 1;
	}

	board[cmpTurn] = computer;
	displayBoard(board);
	return;
}

//================================================================================================

