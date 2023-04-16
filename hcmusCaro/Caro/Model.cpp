#include "Model.h"
#include "Data.h"
#include "View.h"
#include "Control.h"

void ResetData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO)
{//ham khoi tao du lieu mac dinh ban dau cho ban co
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			_A[i][j].y = i * 2 + 1 + BOARD_Y;
			_A[i][j].x = j * 4 + 2 + BOARD_X;
			_A[i][j].c = 0;
		}
	}
	_TURN = 1; _COMMAND = -1;
	_X = _A[0][0].x;
	_Y = _A[0][0].y;
	cX = cY = 0;
	cntX = 0;
	cntO = 0;
}

// Kiểm tra board trả về giá trị tương ứng để in ra màn hình bằng hàm processFinish
int TestBoard(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int& cntWinO, int& cntLoseO, int& cntDraw, int& cntRound, bool check) {
	if (check == true && saveTurn == 1)
	{
		cntRound++;
		cntWinO++;
		return 1; // trả về 1 nếu O thắng
	}
	else if (check == true && saveTurn == -1)
	{
		cntRound++;
		cntLoseO++;
		return -1; // trả về -1 nếu X thắng
	}
	else if (check == false && CheckFullBoard(_A) == true)
	{
		cntRound++;
		cntDraw++;
		return 0; // trả về không nếu không có người nào thắng và đã đánh full board
	}
	return 2;
}

// Hàm duyệt tại vị trí (x,y) và xét quanh điểm đó
bool CheckWin(_POINT _A[B_SIZE][B_SIZE], int x, int y, WinningPos WP[5]) {
	int count = 0;
	int i, j;
	int n = B_SIZE;
	if (_A[y][x].c == 0)
		return false;	
	// Kiểm tra hàng ngang
	for (i = x - 4; i <= x; i++) {
		int k = 0;
		if (i < 0 || i + 4 >= n) continue;
		count = 0;
		for (j = i; j <= i + 4; j++) {
			if (_A[y][j].c == _A[y][x].c) count++;
		}
		if (count == 5) {
			for (j = i; j <= i + 4; j++) {
				WP[k].x = y;
				WP[k].y = j;
				k++;
			}
			return true;
		}
	}

	// Kiểm tra hàng dọc
	for (i = y - 4; i <= y; i++) {
		int k = 0;
		if (i < 0 || i + 4 >= n) continue;
		count = 0;
		for (j = i; j <= i + 4; j++) {
			if (_A[j][x].c == _A[y][x].c) count++;
		}
		if (count == 5)
		{
			for (j = i; j <= i + 4; j++) {
				WP[k].x = j;
				WP[k].y = x;
				k++;
			}
			return true;
		}
	}

	// kiểm tra đường chéo chính
	for (i = x - 4, j = y - 4; i <= x && j <= y; i++, j++) {
		int l = 0;
		if (i < 0 || i + 4 >= n || j < 0 || j + 4 >= n) continue;
		count = 0;
		for (int k = 0; k < 5; k++) {
			if (_A[j + k][i + k].c == _A[y][x].c) count++;
		}
		if (count == 5)
		{
			for (int k = 0; k < 5; k++) {
				WP[l].x = j + k;
				WP[l].y = i + k;
				l++;
			}
			return true;
		}
	}

	// Kiểm tra đường chéo phụ
	for (i = x - 4, j = y + 4; i <= x && j >= y; i++, j--) {
		int l = 0;
		if (i < 0 || i + 4 >= n || j >= n || j - 4 < 0) continue;
		count = 0;
		for (int k = 0; k < 5; k++) {
			if (_A[j - k][i + k].c == _A[y][x].c) count++;
		}
		if (count == 5)
		{
			for (int k = 0; k < 5; k++) {
				WP[l].x = j - k;
				WP[l].y = i + k;
				l++;
			}
			return true;
		}
	}

	return false;
}

// Duyệt toàn BOARD để kiểm tra thắng thua
bool CheckWinLose(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int cX, int cY, WinningPos WP[5])
{
	if (CheckWin(_A, cX, cY, WP) == true)
	{
		saveTurn = _A[cY][cX].c;
		return true;
	}
	return false;
}

// Kiểm tra xem thử có full bảng chưa
bool CheckFullBoard(_POINT _A[B_SIZE][B_SIZE]) {
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			if (_A[i][j].c != 0)
				return false;
		}
	}
	return true;
}

// Kiểm tra dữ liệu tại ô đó và in ra X hoặc O
int CheckBoard(_POINT _A[B_SIZE][B_SIZE], bool _TURN, int pX, int pY)
{
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true)
					_A[i][j].c = 1; // người chơi thứ nhất đánh O
				else
					_A[i][j].c = -1; // người chơi thứ hai đánh X
				return _A[i][j].c;
			}
		}
	}
	return 0; // Trả về nếu ô đó đã có người đánh
}

// Hàm bắt đầu game và khởi tạo dữ liệu
void SetupGame(_POINT _A[B_SIZE][B_SIZE], bool reset, bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int cntWinO, int cntLoseO, int cntDraw, int& cntRound, string& NamePlayer_O, string& NamePlayer_X) {
	SetConsoleBlank();
	if (reset) {
		ResetData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO);
		EnterNamePlayer(NamePlayer_O, NamePlayer_X);
		SetConsoleBlank();
		AskTurn(_TURN, NamePlayer_O, NamePlayer_X);
		SetConsoleBlank();
	}
	GotoXY(40, 29);
	cout << "Created by Group 13 - 22CTT4 - HCMUS";
	TextColor(BLUE);
	DrawBoard(B_SIZE, B_SIZE, BOARD_X, BOARD_Y, GREEN);
	GotoXY(84, 1);
	cout << "<CARO>";
	GotoXY(84, 2);
	cout << "ROUND " << cntRound;
	GotoXY(85, 3);
	cout << "SCORE";
	GotoXY(83, 4);
	cout << "X " << cntLoseO << " : " << cntWinO << " O";
	GotoXY(71, 5);
	for (int i = 0; i < 30; i++) {
		if (i == 0)
			cout << "<<";
		else if (i == 29)
			cout << ">>";
		else
			cout << "-";
	}
	/*drawBoxInf(70,110,8,16);*/ //40,8,70,8
	int wideBox = 55;
	int highBox = 13;
	int xBox = 59;
	int yBox = 6;
	DrawBoxMini(wideBox,highBox, xBox, yBox, BLUE);
	GotoXY(xBox + 2, yBox + 3);
	cout << "Player O: " << NamePlayer_O;
	GotoXY(xBox + 2, yBox + 5);
	cout << "Player X: " << NamePlayer_X;
	GotoXY(xBox + 14,yBox + 1);
	cout << "NAME";
	GotoXY(xBox + 25, yBox + 1);
	cout << "STEP";
	//CntTurn(_TURN, cntX, cntO, false); //Hiển thị lượt đánh
	GotoXY(xBox + 36, yBox + 1);
	cout << "WIN/LOSE/DRAW";
	GotoXY(xBox + 39, yBox + 3);
	cout << cntWinO << "/" << cntLoseO << "/" << cntDraw;
	GotoXY(xBox + 39, yBox + 5);
	cout << cntLoseO << "/" << cntWinO << "/" << cntDraw;
	GotoXY(xBox + 17, yBox + 7);
	cout << "OX << Press Key >> XO";
	GotoXY(xBox + 3, yBox + 9);
	cout << "F1:New Game";
	GotoXY(xBox + 20, yBox + 9);
	cout << "F2:Save Game";
	GotoXY(xBox + 3, yBox + 11);
	cout << "F3:Load Game";
	GotoXY(xBox + 20, yBox + 11);
	cout << "F4:ReLoad Game";
	GotoXY(xBox + 38, yBox + 9);
	cout << "F5:Undo Step";
	GotoXY(xBox + 38, yBox + 11);
	cout << "Esc:Exit Game";
	ShowTurn(_X, _Y, !_TURN, true);
	for (int i = 0; i < B_SIZE; i++)
		for (int j = 0; j < B_SIZE; j++)
			if (_A[i][j].c == -1) {
				GotoXY(_A[i][j].x, _A[i][j].y);
				TextColor(X_COLOR);
				cout << 'X';
			}
			else if (_A[i][j].c == 1) {
				GotoXY(_A[i][j].x, _A[i][j].y);
				TextColor(O_COLOR);
				cout << 'O';
			}
	HoverCell(_A, cY, cX);
}

void StartGame(_POINT _A[B_SIZE][B_SIZE], bool reset, bool& _TURN, int& _COMMAND, bool& sound, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, WinningPos WP[5]) {
	SetupGame(_A, reset, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, cntRound, NamePlayer_O, NamePlayer_X);
	bool validEnter = true, ok = 0;
	while (true) {
		_COMMAND = toupper(_getch());
		if (sound) PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		ok = true;
		if (_COMMAND == ESC) {
			return;
		}
		// Điều khiển
		int tmp = 0;
		if (_COMMAND == SPACE)
			SaveData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, "lanngu.txt");
		if (_COMMAND == ENTER) {
			switch (CheckBoard(_A, _TURN, _X, _Y)) {
			case -1:
				GotoXY(_X, _Y);
				tmp = GetCurrentColor();
				TextColor(X_COLOR);
				cout << "X";
				TextColor(tmp);
				break;
			case 1:
				GotoXY(_X, _Y);
				tmp = GetCurrentColor();
				TextColor(O_COLOR);
				cout << "O";
				TextColor(tmp);
				break;
			case 0:
				validEnter = false;
				break;
			}
			ShowTurn(_X, _Y, _TURN, validEnter);
			CntTurn(_TURN, cntX, cntO, validEnter);
			if (validEnter == true) {
				switch (ProcessFinish(_A, _X, _Y, _TURN, TestBoard(_A, saveTurn, cntWinO, cntLoseO, cntDraw, cntRound, CheckWinLose(_A, saveTurn, cX, cY, WP)), NamePlayer_O, NamePlayer_X, WP)) {
				case -1:
				case 1:
				case 0:
					if (AskContinue(_A) != 'Y') {
						return;
					}
					else
						SetupGame(_A, 1, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, cntRound, NamePlayer_O, NamePlayer_X);
				}
			}
			validEnter = true;
		}
		else if (_COMMAND == 'A') MoveLeft(_A, _X, _Y, cX, cY);
		else if (_COMMAND == 'W') MoveUp(_A, _X, _Y, cX, cY);
		else if (_COMMAND == 'S') MoveDown(_A, _X, _Y, cX, cY);
		else if (_COMMAND == 'D') MoveRight(_A, _X, _Y, cX, cY);
	}
}

bool LoadData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, string FileName) {
	fstream inp;
	inp.open("save\\data\\" + FileName, ios::in);
	if (inp.fail()) {
		inp.close();
		return 0;
	}
	ResetData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO);
	for (int i = 0; i < B_SIZE; i++)
		for (int j = 0; j < B_SIZE; j++)
			inp >> _A[i][j].c;
	inp >> _TURN >> _COMMAND >> _X >> _Y >> cX >> cY;
	inp >> cntX >> cntO >> cntWinO >> cntLoseO >> cntDraw >> saveTurn >> cntRound;
	inp.ignore();
	getline(inp, NamePlayer_O);
	getline(inp, NamePlayer_X);
	inp.close();
	return 1;
}

bool SaveData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, string FileName) {
	fstream out;
	out.open("save\\data\\" + FileName, ios::out);
	if (out.fail()) {
		out.close();
		return 0;
	}
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++)
			out << _A[i][j].c << ' ';
		out << endl;
	}
	out << _TURN << ' ' << _COMMAND << ' ' << _X << ' ' << _Y << ' ' << cX << ' ' << cY << endl;
	out << cntX << ' ' << cntO << ' ' << cntWinO << ' ' << cntLoseO << ' ' << cntDraw << ' ' << saveTurn << cntRound << endl;
	out << NamePlayer_O << endl << NamePlayer_X;
	out.close();
	return 1;
}

void LoadSound(bool& sound) {
	fstream inp;
	inp.open(SOUND_PATH, ios::in);
	if (inp.fail()) {
		cout << "Can't open file";
		return;
	}
	inp >> sound;
	inp.close();
}

void SetSound(bool& sound, bool value) {
	fstream out;
	out.open(SOUND_PATH, ios::out);
	if (out.fail()) {
		cout << "Can't open file";
		return;
	}
	sound = value;
	out << sound;
	out.close();
}