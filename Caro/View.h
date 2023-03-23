#pragma once
#include "Data.h"

void FixConsoleWindow();
void SetConsoleBlank();
void DrawBoard(int row, int col, int x, int y, int color);
void TextColor(int x);
int GetCurrentColor();
void DrawBox(int w, int h, int x, int y, int color);
void PrintCARO(int x, int y, int color);
void PrintNote(int x, int y, int color);
void DrawHeart(int x, int y, int color);
void DrawDiamond(int x, int y, int color);
void BackGround();
void DrawBoxMini(int w, int h, int dx, int dy, int color);
void DrawButton();
void CaroAnimation();
void MainScreen();
void MainMenu();
int ProcessFinish(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, bool& _TURN, int pWhoWin);
char AskContinue(_POINT _A[B_SIZE][B_SIZE]);
void AskTurn(bool& _TURN);
void CntTurn(bool& _TURN, int& cntX, int& cntO, bool validEnter);
void ShowTurn(int _X, int _Y, bool _TURN, bool validEnter);
void UnHover(_POINT _A[B_SIZE][B_SIZE], int x, int y);
void Hover(_POINT _A[B_SIZE][B_SIZE], int x, int y);

void exitGame();