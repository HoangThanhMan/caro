#pragma once

void StopSound();
int inputKey();
void GotoXY(int column, int line);
int whereX();
int whereY();
void MoveRight(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, int& cX, int& cY);
void MoveLeft(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, int& cX, int& cY);
void MoveUp(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, int& cX, int& cY);
void MoveDown(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, int& cX, int& cY);
