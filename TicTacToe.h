#pragma once

// function declarations for TicTacToe game
void humanTurn(char player, char computer, char board[]);
void computerTurn(char player, char computer, char board[]);
void instructions();
void displayBoard(char board[]);
void playGame();

char getWinner(char board[]);

bool checkGameState(char board[]);

