#pragma once

class Game
{
	char grid[3][3];
	bool isOccupied[3][3];
	char player;
	bool PvAI;
	bool gameOver;
	char winner;
	int winRow[3];
	int winCol[3];

public:

	Game();
	void reset(bool mode);
	bool makeMove(int r, int c);
	void AI();
	bool checkWin();
	bool checkWin(char p);
	bool isMoveAvailable();
	bool createsFork(char p, int r, int c);
	char getCell(int r, int c);
	char getPlayer();
	bool getGameOver();
	char getWinner();
	bool getMode();
	void switchPlayer();
	bool isWinningCell(int r, int c);
};