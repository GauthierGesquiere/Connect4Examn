#include "pch.h"
#include "Game.h"
#include <iostream>
#include <iomanip>

//Basic game functions
#pragma region gameFunctions											
void MakeBoard()
{
	for (int i = 0; i < g_Rows; i++)
	{
		for (int y = 0; y < g_Columns; y++)
		{
			g_Board[i][y] = GridCell::Empty;
		}
	}
}
bool IsValidLocation(int col)
{
	if (g_Board[0][col] == GridCell::Empty)
		return true;
	else
		false;
}
int GetNextOpenRow(int col)
{
	for (int r = g_Rows - 1; r >= 0; r--)
	{
		if (g_Board[r][col] == GridCell::Empty)
		{
			return r;
		}
	}
}
void DropPiece(int row, int col, GridCell piece)
{
	g_Board[row][col] = piece;
}
bool WinningMove(GridCell piece)
{
	//Check all horizontal Locations
	for (int c = 0; c < g_Columns - 3; c++)
	{
		for (int r = 0; r < g_Rows; r++)
		{
			if (g_Board[r][c] == piece && g_Board[r][c + 1] == piece && g_Board[r][c + 2] == piece && g_Board[r][c + 3] == piece)
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
			if (g_Board[r][c] == piece && g_Board[r + 1][c] == piece && g_Board[r + 2][c] == piece && g_Board[r + 3][c] == piece)
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
			if (g_Board[r][c] == piece && g_Board[r - 1][c + 1] == piece && g_Board[r - 2][c + 2] == piece && g_Board[r - 3][c + 3] == piece)
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
			if (g_Board[r][c] == piece && g_Board[r + 1][c + 1] == piece && g_Board[r + 2][c + 2] == piece && g_Board[r + 3][c + 3] == piece)
			{
				return true;
			}
		}
	}
	return false;
}
void PrintBoard()
{
	for (int i = 0; i < g_Rows; i++)
	{
		for (int y = 0; y < g_Columns; y++)
		{
			std::cout << int(g_Board[i][y]) << " ";
		}
		std::cout << std::endl;
	}
}

void DrawBoard()
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
			if (g_Board[r][c] == GridCell::RedCoin)
			{
				SetColor(1, 0, 0);
				Ellipsef elipse = Ellipsef{ c * g_SquareSize + (g_SquareSize / 2), g_WindowHeight - ( r * g_SquareSize + g_SquareSize +(g_SquareSize / 2)), (g_SquareSize - 3) / 2, (g_SquareSize - 3) / 2 };
				FillEllipse(elipse);
			}
			else if (g_Board[r][c] == GridCell::YellowCoin)
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

void Start()
{
	// initialize game resources here
	MakeBoard();
	PrintBoard();
}

void Draw()
{
	ClearBackground();
	DrawBoard();
	// Put your own draw statements here
	
}

void Update(float elapsedSec)
{
	// process input, do physics 
	while (!g_GameOver && g_ClickedMouse)
	{
		//Ask for Player1 Input
		if (g_Turn == Turn::Player1)
		{
			int col = int(round((g_MouseXPosition - g_SquareSize / 2) / g_SquareSize));
			if (IsValidLocation(col))
			{
				int row = GetNextOpenRow(col);
				DropPiece(row, col, GridCell::RedCoin);

				if (WinningMove(GridCell::RedCoin))
				{
					std::cout << "Player1 Wins" << std::endl;
					g_GameOver = true;
				}
			}

			//At last
			g_Turn = Turn::Player2;
		}


		//Ask for Player2 Input
		else
		{
			int col = int(round((g_MouseXPosition - g_SquareSize / 2) / g_SquareSize));
			if (IsValidLocation(col))
			{
				int row = GetNextOpenRow(col);
				DropPiece(row, col, GridCell::YellowCoin);
				if (WinningMove(GridCell::YellowCoin))
				{
					std::cout << "Player2 Wins" << std::endl;
					g_GameOver = true;
				}
			}

			//At last
			g_Turn = Turn::Player1;
		}
		PrintBoard();
		g_ClickedMouse = false;
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
	//switch (key)
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
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
	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Initialize your own variables here

// Define your own functions here
void PrintSnake(int lines, int character, char snake_character)
{
	int linesCounter(0);
	int snakeCounter(0);
	int counter(1);

	while (linesCounter < lines)
	{
		int characterCounter(0);
		while (characterCounter < character)
		{
			if (characterCounter == snakeCounter)
			{
				std::cout << snake_character;	//write the snakecharacter
			}
			else
			{
				std::cout << "*";	//else write *
			}
			characterCounter++;
		}
		std::cout << "\n";

		if (snakeCounter > character - 2)counter = -1;	//limits of the snake
		if (snakeCounter < 1)counter = 1;

		snakeCounter += counter;
		linesCounter++;
	}
}
