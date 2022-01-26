#include "pch.h"
#include "Game.h"
#include <iostream>
#include <iomanip>

//Basic game functions
#pragma region gameFunctions											
void MakeBoard(GridCell board[][g_Columns])
{
	for (int i = 0; i < g_Rows; i++)
	{
		for (int y = 0; y < g_Columns; y++)
		{
			board[i][y] = GridCell::Empty;
		}
	}
}
bool IsValidLocation(GridCell board[][g_Columns], int col)
{
	if (board[0][col] == GridCell::Empty)
		return true;
	else
		return false;
}
int GetNextOpenRow(GridCell board[][g_Columns], int col)
{
	for (int r = g_Rows - 1; r >= 0; r--)
	{
		if (board[r][col] == GridCell::Empty)
		{
			return r;
		}
	}
}
void DropPiece(GridCell board[][g_Columns], int row, int col, GridCell piece)
{
	board[row][col] = piece;
}
bool WinningMove(GridCell board[][g_Columns], GridCell piece)
{
	//Check all horizontal Locations
	for (int c = 0; c < g_Columns - 3; c++)
	{
		for (int r = 0; r < g_Rows; r++)
		{
			if (board[r][c] == piece && board[r][c + 1] == piece && board[r][c + 2] == piece && board[r][c + 3] == piece)
			{
				return true;
			}
		}
	}

	//Check all vertical Locations
	for (int r = 0; r < g_Rows - 3; r++)
	{
		for (int c = 0; c < g_Columns; c++)
		{
			if (board[r][c] == piece && board[r + 1][c] == piece && board[r + 2][c] == piece && board[r + 3][c] == piece)
			{
				return true;
			}
		}
	}

	//Check positively Slopes diagonals
	for (int r = 3; r < g_Rows; r++)
	{
		for (int c = 0; c < g_Columns - 3; c++)
		{
			if (board[r][c] == piece && board[r - 1][c + 1] == piece && board[r - 2][c + 2] == piece && board[r - 3][c + 3] == piece)
			{
				return true;
			}
		}
	}

	//Check negatively Slopes diagonals
	for (int r = 0; r < g_Rows - 3; r++)
	{
		for (int c = 0; c < g_Columns - 3; c++)
		{
			if (board[r][c] == piece && board[r + 1][c + 1] == piece && board[r + 2][c + 2] == piece && board[r + 3][c + 3] == piece)
			{
				return true;
			}
		}
	}
	return false;
}
void PrintBoard(GridCell board[][g_Columns])
{
	for (int i = 0; i < g_Rows; i++)
	{
		for (int y = 0; y < g_Columns; y++)
		{
			std::cout << int(board[i][y]) << " ";
		}
		std::cout << std::endl;
	}
}

void DrawBoard(GridCell board[][g_Columns])
{
	SetColor(0, 0, 0);
	FillRect(Rectf(0, 0, g_WindowWidth, g_WindowHeight));
	for (int r = 0; r < g_Rows; r++)
	{
		for (int c = 0; c < g_Columns; c++)
		{
			SetColor(0, 0, 1);
			Rectf rect = Rectf{ c * g_SquareSize, r * g_SquareSize, g_SquareSize, g_SquareSize };
			FillRect(rect);
			SetColor(0, 0, 0);
			Ellipsef elipse = Ellipsef{ c * g_SquareSize  + (g_SquareSize / 2), r * g_SquareSize + (g_SquareSize / 2), (g_SquareSize - 3) / 2, (g_SquareSize - 3) / 2 };
			FillEllipse(elipse);
		}
	}

	for (int r = 0; r < g_Rows; r++)
	{
		for (int c = 0; c < g_Columns; c++)
		{
			if (board[r][c] == GridCell::RedCoin)
			{
				SetColor(1, 0, 0);
				Ellipsef elipse = Ellipsef{ c * g_SquareSize + (g_SquareSize / 2), g_WindowHeight - ( r * g_SquareSize + g_SquareSize +(g_SquareSize / 2)), (g_SquareSize - 3) / 2, (g_SquareSize - 3) / 2 };
				FillEllipse(elipse);
			}
			else if (board[r][c] == GridCell::YellowCoin)
			{
				SetColor(1, 1, 0);
				Ellipsef elipse = Ellipsef{ c * g_SquareSize + (g_SquareSize / 2), g_WindowHeight - ( r * g_SquareSize + g_SquareSize + (g_SquareSize / 2)), (g_SquareSize - 3) / 2, (g_SquareSize - 3) / 2 };
				FillEllipse(elipse);
			}
			
		}
	}

	if (g_Turn == Turn::Player1)
	{
		Ellipsef elipse = Ellipsef{ g_MouseXPosition, g_WindowHeight -(g_SquareSize / 2), (g_SquareSize - 3) / 2, (g_SquareSize - 3) / 2 };
		SetColor(1, 0, 0);
		FillEllipse(elipse);
	}
	else if (g_Turn == Turn::Player2)
	{
		Ellipsef elipse = Ellipsef{ g_MouseXPosition, g_WindowHeight - (g_SquareSize / 2), (g_SquareSize - 3) / 2, (g_SquareSize - 3) / 2 };
		SetColor(1, 1, 0);
		FillEllipse(elipse);
	}
}

int ScorePosition(GridCell board[][g_Columns], GridCell piece)
{
	int score = 0;

	//CenterArray
	GridCell centerArray[g_Rows];
	for (int r = 0; r < g_Rows; r++)
	{
		centerArray[r] = board[r][g_Columns / 2];
	}

	int amountOfPieces = 0;
	int amountOfEmptyCells = 0;

	for (auto& Cell : centerArray)
	{
		if (Cell == piece)
		{
			amountOfPieces++;
		}
		if (Cell == GridCell::Empty)
		{
			amountOfEmptyCells++;
		}
	}
	score += amountOfPieces * 3;

	//Horisontal Score
	for (int r = 0; r < g_Rows; r++)
	{
		GridCell rowArray[g_Columns];
		for (int c = 0; c < g_Columns; c++)
		{
			rowArray[c] = board[r][c];
		}

		
		for (int c = 0; c < g_Columns - 3; c++)
		{
			std::vector<GridCell> window;
			window.push_back(rowArray[c]);
			window.push_back(rowArray[c + 1]);
			window.push_back(rowArray[c + 2]);
			window.push_back(rowArray[c + 3]);

			score += EvaluateWindow(window, piece);
		}
	}

	//Vertical Score
	for (int c = 0; c < g_Columns; c++)
	{
		GridCell ColumnArray[g_Rows];
		for (int r = 0; r < g_Rows; r++)
		{
			ColumnArray[r] = board[r][c];
		}


		for (int r = 0; r < g_Rows - 3; r++)
		{
			std::vector<GridCell> window;
			window.push_back(ColumnArray[r]);
			window.push_back(ColumnArray[r + 1]);
			window.push_back(ColumnArray[r + 2]);
			window.push_back(ColumnArray[r + 3]);

			score += EvaluateWindow(window, piece);
		}
	}

	//Positively Sloped Diagonals
	for (int r = 3; r < g_Rows; r++)
	{
		for (int c = 0; c < g_Columns - 3; c++)
		{
			std::vector<GridCell> window;
			window.push_back(board[r][c]);
			window.push_back(board[r - 1][c + 1]);
			window.push_back(board[r - 2][c + 2]);
			window.push_back(board[r - 3][c + 3]);

			score += EvaluateWindow(window, piece);
		}
	}

	//Negatively Sloped Diagonals
	for (int r = 0; r < g_Rows - 3; r++)
	{
		for (int c = 0; c < g_Columns - 3; c++)
		{
			std::vector<GridCell> window;
			window.push_back(board[r][c]);
			window.push_back(board[r + 1][c + 1]);
			window.push_back(board[r + 2][c + 2]);
			window.push_back(board[r + 3][c + 3]);

			score += EvaluateWindow(window, piece);
		}
	}

	return score;
}

int PickBestMove(GridCell board[][g_Columns], GridCell piece)
{
	std::vector<int> validLocation = GetValidLocations(board);

	int BestScore = -9999;
	int BestColumn = validLocation[rand() % validLocation.size()];

	for (auto& c : validLocation)
	{
		int r = GetNextOpenRow(board, c);

		GridCell tempBoard[g_Rows][g_Columns];
		for (int r = 0; r < g_Rows; r++)
		{
			for (int c = 0; c < g_Columns; c++)
			{
				tempBoard[r][c] = board[r][c];
			}
		}

		DropPiece(tempBoard, r, c, piece);
		int score = ScorePosition(tempBoard, piece);
		if (score > BestScore)
		{
			BestScore = score;
			BestColumn = c;
		}
	}
	return BestColumn;
}

std::vector<int> GetValidLocations(GridCell board[][g_Columns])
{
	std::vector<int> validLocation;

	for (int c = 0; c < g_Columns; c++)
	{
		if (IsValidLocation(board, c))
		{
			validLocation.push_back(c);
		}
	}
	return validLocation;
}

int EvaluateWindow(std::vector<GridCell> window, GridCell piece)
{
	GridCell OpponentPiece = GridCell::RedCoin;
	if (piece == OpponentPiece)
	{
		OpponentPiece = GridCell::YellowCoin;
	}

	int score = 0;
	int amountOfPieces = 0;
	int amountOfEmptyCells = 0;
	int amountOfOpponentPieces = 0;


	for (auto& Cell : window)
	{
		if (Cell == piece)
		{
			amountOfPieces++;
		}
		if (Cell == GridCell::Empty)
		{
			amountOfEmptyCells++;
		}
		if (Cell == OpponentPiece)
		{
			amountOfOpponentPieces++;
		}
	}

	if (amountOfPieces == 4)
	{
		score += 100;
	}

	else if (amountOfPieces == 3 && amountOfEmptyCells == 1)
	{
		score += 5;
	}

	else if (amountOfPieces == 2 && amountOfEmptyCells == 2)
	{
		score += 2;
	}

	if (amountOfOpponentPieces == 3 && amountOfEmptyCells == 1)
	{
		score -= 3;
	}

	/*if (amountOfOpponentPieces == 2 && amountOfEmptyCells == 2)
	{
		score -= 5;
	}*/

	return score;
}
bool IsTerminalNode(GridCell board[][g_Columns])
{
	if (WinningMove(board, GridCell::RedCoin))
	{		
		return true;
	}
	else if (WinningMove(board, GridCell::YellowCoin))
	{
		return true;
	}
	else if (GetValidLocations(board).size() == 0)
	{
		return true;
	}
	return false;
}
//https://en.wikipedia.org/wiki/Minimax#Pseudocode
//https://www.youtube.com/watch?v=l-hh51ncgDI
//https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
std::pair<int, int> MiniMax(GridCell board[][g_Columns], int depth, int alpha, int beta, bool maximizingPlayer)
{
	std::vector<int> validLocations = GetValidLocations(board);
	bool isTerminal = IsTerminalNode(board);
	if ((depth == 0) || isTerminal)
	{
		if (isTerminal)
		{
			if (WinningMove(board, GridCell::YellowCoin))
			{
				//Debug
				GridCell tempBoard[g_Rows][g_Columns];
				for (int r = 0; r < g_Rows; r++)
				{
					for (int c = 0; c < g_Columns; c++)
					{
						tempBoard[r][c] = board[r][c];
					}
				}

				return std::make_pair(NULL, INT_MAX - INT_MAX / (depth + 1) / 2);
			}
			else if (WinningMove(board, GridCell::RedCoin))
			{
				return std::make_pair(NULL, 0 - INT_MAX /*- INT_MIN / (depth + 1) / 2*/);
			}
			else
			{
				return std::make_pair(NULL, 0);
			}
		}
		else
		{
			//Depth is zero
			int score = ScorePosition(board, GridCell::YellowCoin);
			return std::make_pair(NULL, score);		
		}
	}


	if (maximizingPlayer)
	{
		//Cuz -INFINITY IS not a thing
		int value = INT_MIN;
		int bestColumn = validLocations[rand() % validLocations.size()];
		for (auto& col : validLocations)
		{
			int row = GetNextOpenRow(board, col);

			GridCell tempBoard[g_Rows][g_Columns];
			for (int r = 0; r < g_Rows; r++)
			{
				for (int c = 0; c < g_Columns; c++)
				{
					tempBoard[r][c] = board[r][c];
				}
			}

			DropPiece(tempBoard, row, col, GridCell::YellowCoin);
			int newScore = MiniMax(tempBoard, depth - 1,alpha, beta, false).second;			
			if (newScore > value)
			{
				value = newScore;
				bestColumn = col;
			}
			if (value >= beta)
			{
				break;
			}
			alpha = std::max(alpha, value);
		}
		return std::make_pair(bestColumn, value);
	}
	else
	{
		int value = INT_MAX;
		int bestColumn = validLocations[rand() % validLocations.size()];

		for (auto& col : validLocations)
		{
			int row = GetNextOpenRow(board, col);

			GridCell tempBoard[g_Rows][g_Columns];
			for (int r = 0; r < g_Rows; r++)
			{
				for (int c = 0; c < g_Columns; c++)
				{
					tempBoard[r][c] = board[r][c];
				}
			}

			DropPiece(tempBoard, row, col, GridCell::RedCoin);
			int newScore = MiniMax(tempBoard, depth - 1, alpha, beta, true).second;
			if (newScore < value)
			{
				value = newScore;
				bestColumn = col;
			}
			if (alpha >= value)
			{
				break;
			}
			beta = std::min(beta, value);
		}
		return std::make_pair(bestColumn, value);
	}
}

void Start()
{
	// initialize game resources here
	MakeBoard(g_Board);
	//PrintBoard();
}

void Draw()
{
	// Put your own draw statements here
	ClearBackground();
	DrawBoard(g_Board);
	
}

void Update(float elapsedSec)
{
	// process input, do physics 
	if (!g_GameOver)
	{
		if (g_ClickedMouse)
		{
			//Ask for Player1 Input
			if (g_Turn == Turn::Player1)
			{
				int col = int(round((g_MouseXPosition - g_SquareSize / 2) / g_SquareSize));
				if (IsValidLocation(g_Board, col))
				{
					int row = GetNextOpenRow(g_Board, col);
					DropPiece(g_Board, row, col, GridCell::RedCoin);

					if (WinningMove(g_Board, GridCell::RedCoin))
					{
						std::cout << "Player1 Wins" << std::endl;
						g_GameOver = true;
					}
					//At last
					//g_Turn = Turn::Player2;
					//g_Depth += 0.5f;
					g_Turn = Turn::AI;
				}

			}


			//Ask for Player2 Input
			else if (g_Turn == Turn::Player2)
			{
				//Player2
				int col = int(round((g_MouseXPosition - g_SquareSize / 2) / g_SquareSize));
				if (IsValidLocation(g_Board, col))
				{
					int row = GetNextOpenRow(g_Board, col);
					DropPiece(g_Board, row, col, GridCell::YellowCoin);
					if (WinningMove(g_Board, GridCell::YellowCoin))
					{
						std::cout << "Player2 Wins" << std::endl;
						g_GameOver = true;
					}
					//At last
					g_Turn = Turn::Player1;
				}

			}
			//PrintBoard();
			g_ClickedMouse = false;
			return;
		}

		if (g_Turn == Turn::AI)
		{
			//Really Dumb AI
			//int col = rand() % g_Columns - 1;	

			//AI
			//int col = PickBestMove(g_Board, GridCell::YellowCoin);
			std::pair<int, int>columnAndScore = MiniMax(g_Board, int(g_Depth), INT_MIN, INT_MAX, true);
			int col = columnAndScore.first;
			//Sleep(500);
			if (IsValidLocation(g_Board, col))
			{
				int row = GetNextOpenRow(g_Board, col);
				DropPiece(g_Board, row, col, GridCell::YellowCoin);
				if (WinningMove(g_Board, GridCell::YellowCoin))
				{
					std::cout << "AI Wins" << std::endl;
					g_GameOver = true;
				}
			}

			//At last
			g_Turn = Turn::Player1;
		}
	}
}

void End()
{
	// free game resources here
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{

}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	g_MouseXPosition = float(e.x);
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		g_ClickedMouse = true;
		break;
	}
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{

}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Initialize your own variables here

