#pragma once
#include "Data.h"

void ResetData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO);
bool CheckFullBoard(_POINT _A[B_SIZE][B_SIZE]);
void SetupGame(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int cntWinO, int cntLoseO, int cntDraw,int cntRound);
int TestBoard(int& saveTurn, int& cntWinO, int& cntLoseO, int& cntDraw,int& cntRound, bool check);
bool CheckWin(_POINT _A[B_SIZE][B_SIZE], int x, int y);
bool CheckWinLose(_POINT _A[B_SIZE][B_SIZE], int& saveTurn);
int CheckBoard(_POINT _A[B_SIZE][B_SIZE], bool _TURN, int pX, int pY);
void StartGame(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw,int& cntRound, int& saveTurn);