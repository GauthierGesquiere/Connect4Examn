#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Prog1DAE09_Q39_Gesquiere_Gauthier, Gauthier, Gesquiere - 1DAE09" };

// Declare your own global variables here
float g_SquareSize = 100;
const int g_Rows = 6;
const int g_Columns = 7;

// Change the window dimensions here
float g_WindowWidth{ g_SquareSize * g_Columns };
float g_WindowHeight{ g_SquareSize * (g_Rows + 1) };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
bool g_GameOver = false;

bool g_ClickedMouse = false;

float g_MouseXPosition = g_WindowWidth / 2;

enum class Turn
{
	Player1,
	Player2
};
Turn g_Turn = Turn::Player1;

enum class GridCell
{
	Empty,
	RedCoin,
	YellowCoin
};
GridCell g_Board[g_Rows][g_Columns];

// Declare your own functions here
void MakeBoard();
bool IsValidLocation(int col);
int GetNextOpenRow(int col);
void DropPiece(int row, int col, GridCell piece);
bool WinningMove(GridCell piece);
void PrintBoard();
void DrawBoard();

#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling