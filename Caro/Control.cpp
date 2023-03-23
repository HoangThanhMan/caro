#include "Data.h"
#include "Control.h"
#include "View.h"
#include "Model.h"

void StopSound() {
	PlaySound(NULL, 0, SND_PURGE);
}

int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224) // special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return key_none;
	}

	return key_none;
}

void GotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void MoveRight(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, int& cX, int& cY)
{
	if (_X < _A[B_SIZE - 1][B_SIZE - 1].x)
	{
		GotoXY(_X, _Y);
		UnHover(_A, cX, cY);
		_X += 4;
		cX++;
		GotoXY(_X, _Y);
		Hover(_A, cX, cY);
	}
}

void MoveLeft(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, int& cX, int& cY) {
	if (_X > _A[0][0].x)
	{
		GotoXY(_X, _Y);
		UnHover(_A, cX, cY);
		_X -= 4;
		cX--;
		GotoXY(_X, _Y);
		Hover(_A, cX, cY);
	}
}

void MoveUp(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, int& cX, int& cY) {
	if (_Y > _A[0][0].y)
	{
		GotoXY(_X, _Y);
		UnHover(_A, cX, cY);
		_Y -= 2;
		cY--;
		GotoXY(_X, _Y);
		Hover(_A, cX, cY);
	}
}

void MoveDown(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, int& cX, int& cY) {
	if (_Y < _A[B_SIZE - 1][B_SIZE - 1].y)
	{
		GotoXY(_X, _Y);
		UnHover(_A, cX, cY);
		_Y += 2;
		cY++;
		GotoXY(_X, _Y);
		Hover(_A, cX, cY);
	}
}