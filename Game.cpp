#include "Game.h"

Game::Game()
{
	reset(false);
}

void Game::reset(bool mode)
{
	PvAI = mode;

	player = 'X';

	gameOver = false;
	winner = '.';
	for (int i = 0; i < 3; i++)
	{
		winRow[i] = -1;
		winCol[i] = -1;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			grid[i][j] = '.';
			isOccupied[i][j] = false;
		}
	}
}

char Game::getCell(int r, int c)
{
	return grid[r][c];
}

char Game::getPlayer()
{
	return player;
}

bool Game::getGameOver()
{
	return gameOver;
}

char Game::getWinner()
{
	return winner;
}

bool Game::getMode()
{
	return PvAI;
}

void Game::switchPlayer()
{
	if (player == 'X')
		player = 'O';
	else
		player = 'X';
}

bool Game::makeMove(int r, int c)
{
	if (gameOver)
		return false;

	if (r < 0 || r > 2 || c < 0 || c > 2)
		return false;

	if (isOccupied[r][c])
		return false;

	grid[r][c] = player;
	isOccupied[r][c] = true;

	if (checkWin())
	{
		gameOver = true;
		winner = player;
		return true;
	}

	if (!isMoveAvailable())
	{
		gameOver = true;
		winner = 'D';
		return true;
	}

	switchPlayer();

	if (PvAI && player == 'O')
	{
		AI();

		if (checkWin())
		{
			gameOver = true;
			winner = player;
			return true;
		}

		if (!isMoveAvailable())
		{
			gameOver = true;
			winner = 'D';
			return true;
		}

		switchPlayer();
	}

	return true;
}

bool Game::checkWin()
{
	// Rows
	for (int i = 0; i < 3; i++)
	{
		if (grid[i][0] == player &&
			grid[i][1] == player &&
			grid[i][2] == player)
		{
			winRow[0] = i; winCol[0] = 0;
			winRow[1] = i; winCol[1] = 1;
			winRow[2] = i; winCol[2] = 2;

			return true;
		}
	}

	// Columns
	for (int i = 0; i < 3; i++)
	{
		if (grid[0][i] == player &&
			grid[1][i] == player &&
			grid[2][i] == player)
		{
			winRow[0] = 0; winCol[0] = i;
			winRow[1] = 1; winCol[1] = i;
			winRow[2] = 2; winCol[2] = i;

			return true;
		}
	}

	// Main diagonal
	if (grid[0][0] == player &&
		grid[1][1] == player &&
		grid[2][2] == player)
	{
		winRow[0] = 0; winCol[0] = 0;
		winRow[1] = 1; winCol[1] = 1;
		winRow[2] = 2; winCol[2] = 2;

		return true;
	}

	// Other diagonal
	if (grid[2][0] == player &&
		grid[1][1] == player &&
		grid[0][2] == player)
	{
		winRow[0] = 2; winCol[0] = 0;
		winRow[1] = 1; winCol[1] = 1;
		winRow[2] = 0; winCol[2] = 2;

		return true;
	}

	return false;
}

bool Game::checkWin(char p)
{
	for (int i = 0; i < 3; i++)
	{
		if (grid[i][0] == p &&
			grid[i][1] == p &&
			grid[i][2] == p)
			return true;

		if (grid[0][i] == p &&
			grid[1][i] == p &&
			grid[2][i] == p)
			return true;
	}

	if (grid[0][0] == p &&
		grid[1][1] == p &&
		grid[2][2] == p)
		return true;

	if (grid[0][2] == p &&
		grid[1][1] == p &&
		grid[2][0] == p)
		return true;

	return false;
}

bool Game::isMoveAvailable()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!isOccupied[i][j])
				return true;
		}
	}

	return false;
}

bool Game::createsFork(char p, int r, int c)
{
	grid[r][c] = p;
	isOccupied[r][c] = true;

	int winningMoves = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!isOccupied[i][j])
			{
				grid[i][j] = p;
				isOccupied[i][j] = true;

				if (checkWin(p))
					winningMoves++;

				grid[i][j] = '.';
				isOccupied[i][j] = false;
			}
		}
	}

	grid[r][c] = '.';
	isOccupied[r][c] = false;

	return (winningMoves >= 2);
}

void Game::AI()
{
	// Win

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!isOccupied[i][j])
			{
				grid[i][j] = 'O';
				isOccupied[i][j] = true;

				if (checkWin('O'))
					return;

				grid[i][j] = '.';
				isOccupied[i][j] = false;
			}
		}
	}

	// Block

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!isOccupied[i][j])
			{
				grid[i][j] = 'X';
				isOccupied[i][j] = true;

				if (checkWin('X'))
				{
					grid[i][j] = 'O';
					return;
				}

				grid[i][j] = '.';
				isOccupied[i][j] = false;
			}
		}
	}

	// Create Fork

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!isOccupied[i][j] && createsFork('O', i, j))
			{
				grid[i][j] = 'O';
				isOccupied[i][j] = true;
				return;
			}
		}
	}

	// Block Fork

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!isOccupied[i][j] && createsFork('X', i, j))
			{
				grid[i][j] = 'O';
				isOccupied[i][j] = true;
				return;
			}
		}
	}

	// Centre

	if (!isOccupied[1][1])
	{
		grid[1][1] = 'O';
		isOccupied[1][1] = true;
		return;
	}

	// Opposite Corner

	if (grid[0][0] == 'X' && !isOccupied[2][2])
	{
		grid[2][2] = 'O';
		isOccupied[2][2] = true;
		return;
	}

	if (grid[2][2] == 'X' && !isOccupied[0][0])
	{
		grid[0][0] = 'O';
		isOccupied[0][0] = true;
		return;
	}

	if (grid[0][2] == 'X' && !isOccupied[2][0])
	{
		grid[2][0] = 'O';
		isOccupied[2][0] = true;
		return;
	}

	if (grid[2][0] == 'X' && !isOccupied[0][2])
	{
		grid[0][2] = 'O';
		isOccupied[0][2] = true;
		return;
	}

	// Corners

	int corners[4][2] =
	{
		{0,0},
		{0,2},
		{2,0},
		{2,2}
	};

	for (int i = 0; i < 4; i++)
	{
		int r = corners[i][0];
		int c = corners[i][1];

		if (!isOccupied[r][c])
		{
			grid[r][c] = 'O';
			isOccupied[r][c] = true;
			return;
		}
	}

	// Sides

	int sides[4][2] =
	{
		{0,1},
		{1,0},
		{1,2},
		{2,1}
	};

	for (int i = 0; i < 4; i++)
	{
		int r = sides[i][0];
		int c = sides[i][1];

		if (!isOccupied[r][c])
		{
			grid[r][c] = 'O';
			isOccupied[r][c] = true;
			return;
		}
	}
}

bool Game::isWinningCell(int r, int c)
{
	for (int i = 0; i < 3; i++)
	{
		if (winRow[i] == r && winCol[i] == c)
			return true;
	}

	return false;
}