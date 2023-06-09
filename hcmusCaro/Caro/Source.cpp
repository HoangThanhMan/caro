﻿#include "Data.h"
#include "Control.h"
#include "View.h"
#include "Model.h"

_POINT _A[B_SIZE][B_SIZE]; //Ma trận bàn cờ
bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y, cX, cY; //Tọa độ hiện hành trên màn hình bàn cờ
int cntX;
int cntO;
int saveTurn = 0;
int cntWinO = 0, cntLoseO = 0;
int cntDraw = 0;
int cntRound = 1;
bool sound = 1;
string NamePlayer_O = "", NamePlayer_X = "";
WinningPos WP[5];
int main() {
	HideCursor();
	FixConsoleWindow();
	LoadSound(sound);
	while (true) {
		MainMenu(_A, _TURN, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, WP);
	}
	return 0;
}