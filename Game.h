#pragma once
using namespace utils;


#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Connect4, Examn, Gauthier, Gesquiere - 2GD06" };

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

float g_Depth = 5;

enum class Turn
{
	Player1,
	Player2,
	AI
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
void MakeBoard(GridCell board[][g_Columns]);
bool IsValidLocation(GridCell board[][g_Columns], int col);
int GetNextOpenRow(GridCell board[][g_Columns], int col);
void DropPiece(GridCell board[][g_Columns], int row, int col, GridCell piece);
bool WinningMove(GridCell board[][g_Columns], GridCell piece);
void PrintBoard(GridCell board[][g_Columns]);
void DrawBoard(GridCell board[][g_Columns]);
int ScorePosition(GridCell board[][g_Columns], GridCell piece);
int PickBestMove(GridCell board[][g_Columns], GridCell piece);
std::vector<int> GetValidLocations(GridCell board[][g_Columns]);
int EvaluateWindow(std::vector<GridCell> window, GridCell piece);

bool IsTerminalNode(GridCell board[][g_Columns]);
std::pair<int, int> MiniMax(GridCell board[][g_Columns], int depth, int alpha, int beta, bool maximizingPlayer);

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