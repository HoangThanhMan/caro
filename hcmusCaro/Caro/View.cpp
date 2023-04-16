#include "View.h"
#include "Data.h"
#include "Model.h"
#include "Control.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void TextColor(int x) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void SetConsoleBlank() {
	int h = HEIGHT, w = WIDTH;
	TextColor(WHITE);
	for (int i = 0; i < h; i++) {
		GotoXY(0, i);
		for (int j = 0; j < w; j++)
			cout << SPACE;
	}
	GotoXY(0, 0);
}

int GetCurrentColor() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	WORD textAttributes = consoleInfo.wAttributes;
	return textAttributes;
}

void DrawBoard(int r, int c, int x, int y, int color) {
	int tmp = GetCurrentColor();
	GotoXY(x, y);
	TextColor(color);

	// top row
	cout << TOP_LEFT << H_LINE << H_LINE << H_LINE;
	for (int i = 1; i < c; i++) {
		cout << TOP_CROSS << H_LINE << H_LINE << H_LINE;
	}
	cout << TOP_RIGHT;
	GotoXY(x, y + 1);
	for (int i = 0; i <= c; i++) {
		cout << V_LINE << SPACE << SPACE << SPACE;
	}

	// all the middle row
	for (int i = 1; i < r; i++) {
		GotoXY(x, y + i * 2);
		cout << LEFT_CROSS << H_LINE << H_LINE << H_LINE;
		for (int j = 1; j < c; j++)
			cout << CROSS << H_LINE << H_LINE << H_LINE;
		cout << RIGHT_CROSS;
		GotoXY(x, y + i * 2 + 1);
		for (int j = 0; j <= c; j++) {
			cout << V_LINE << SPACE << SPACE << SPACE;
		}
	}

	// bottom row
	GotoXY(x, y + 2 + 2 * (r - 1));
	cout << BOTTOM_LEFT << H_LINE << H_LINE << H_LINE;
	for (int i = 1; i < c; i++) {
		cout << BOTTOM_CROSS << H_LINE << H_LINE << H_LINE;
	}
	cout << BOTTOM_RIGHT;
	TextColor(tmp);
}

//void DrawBox(int w, int h, int x, int y, int color, int Time) {
//	TextColor(color);
//	GotoXY(x, y);
//	cout << BOX_TOP_LEFT;
//	for (int i = 1; i < w - 1; i++)
//	{
//		cout << BOX_H_LINE;
//		Sleep(Time);
//	}
//
//	cout << BOX_TOP_RIGHT;
//
//	for (int i = 1; i < h - 1; i++) {
//		GotoXY(x, i + y);
//		cout << BOX_V_LINE;
//		for (int j = 1; j < w - 1; j++)
//			cout << SPACE;
//		cout << BOX_V_LINE;
//		Sleep(Time);
//	}
//
//	GotoXY(x, h + y - 1);
//	cout << BOX_BOTTOM_LEFT;
//	for (int i = w - 1; i > 1; i--)
//	{
//		cout << BOX_H_LINE;
//		Sleep(Time);
//	}
//	cout << BOX_BOTTOM_RIGHT;
//}

void DrawBox(int w, int h, int x, int y, int color, int Time) {
	TextColor(color);
	for (int i = 0; i < w / 2; i++) {
		GotoXY(x + w / 2 - i, y);
		cout << BOX_H_LINE;
		GotoXY(x + w / 2 + i, y);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	GotoXY(x, y);
	cout << BOX_TOP_LEFT;
	GotoXY(x + w, y);
	cout << BOX_TOP_RIGHT;
	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, y + i);
		cout << BOX_V_LINE;
		for (int j = 1; j < w; j++)
			cout << SPACE;
		cout << BOX_V_LINE;
		Sleep(Time);
	}
	GotoXY(x, y + h - 1);
	cout << BOX_BOTTOM_LEFT;
	GotoXY(x + w, y + h - 1);
	cout << BOX_BOTTOM_RIGHT;
	for (int i = w / 2 - 1; i >= 0; i--) {
		GotoXY(x + w / 2 - i, y + h - 1);
		cout << BOX_H_LINE;
		GotoXY(x + w / 2 + i, y + h - 1);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
}

//update
void PrintCARO(int x, int y, int color)
{
	TextColor(color);
	unsigned char logo[] = { 32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 219, 219, 219, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32,
							179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 219, 219, 219, 32, 179, 219, 219, 219, 219, 219, 219, 219, 32, 32, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32 };
	int num_lines = 7, num_chars = 45;
	for (int i = 0; i < num_lines; i++)
	{
		GotoXY(x, i + y);
		for (int j = 0; j < num_chars; j++)
			putchar(logo[i * num_chars + j]);
	}
}

void PrintNote(int x, int y, int color)
{
	TextColor(color);
	GotoXY(x, y);
	unsigned char Note[] = { 179, 32, 80, 114, 111, 106, 101, 99, 116, 32, 98, 121, 32, 71, 114, 111, 117, 112, 32, 49, 51, 32, 45, 32, 50, 50, 67, 84, 84, 52, 32, 72, 67, 77, 85, 83, 32, 179 };
	for (int i = 0; i < 38; i++)
	{
		cout << Note[i];
		Sleep(10);
	}

}

void DrawHeart(int x, int y, int color)
{
	TextColor(color);
	unsigned char pattern = 3;
	for (int i = 0; i < 30; i = i + 6)
	{
		GotoXY(y, x + i);
		putchar(pattern);
	}
}

void DrawDiamond(int x, int y, int color)
{
	TextColor(color);
	unsigned char pattern = 4;
	for (int i = 0; i < 30; i = i + 6)
	{
		GotoXY(y, x + i);
		putchar(pattern);
	}
}

void BackGround()
{
	DrawHeart(1, 6, LIGHT_RED);
	DrawDiamond(4, 24, MAGENTA);
	DrawHeart(1, 42, LIGHT_RED);
	DrawDiamond(4, 60, MAGENTA);
	DrawHeart(1, 78, LIGHT_RED);
	DrawDiamond(4, 96, MAGENTA);
	DrawHeart(1, 114, LIGHT_RED);

}

void DrawBoxMini(int w, int h, int x, int y, int color)
{
	TextColor(color);
	GotoXY(x, y);
	cout << TOP_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << H_LINE;
	cout << TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, i + y);
		cout << V_LINE;
		for (int j = 1; j < w - 1; j++)
			cout << SPACE;
		cout << V_LINE;
	}

	GotoXY(x, h + y - 1);
	cout << BOTTOM_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << H_LINE;
	cout << BOTTOM_RIGHT;
}

void DrawButton()
{
	DrawBoxMini(14, 3, 89, 6, BLUE);
	GotoXY(94, 7);
	cout << "PLAY";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 9, BLUE);
	GotoXY(94, 10);
	cout << "LOAD";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 12, BLUE);
	GotoXY(94, 13);
	cout << "HELP";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 15, BLUE);
	GotoXY(93, 16);
	cout << "SETTING";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 18, BLUE);
	GotoXY(94, 19);
	cout << "EXIT";
	Sleep(200);
}

void CaroAnimation()
{
	PrintCARO(20, 9, MAGENTA);
	Sleep(150);
	PrintCARO(20, 9, YELLOW);
	Sleep(150);
	PrintCARO(20, 9, LIGHT_CYAN);
	Sleep(150);
	PrintCARO(20, 9, GREEN);
	Sleep(150);
	PrintCARO(20, 9, BLUE);
	Sleep(150);
	PrintCARO(20, 9, LIGHT_YELLOW);
	Sleep(150);
	PrintCARO(20, 9, RED);
}

void ascii_art(string input, int x, int y, int t_color)
{
	//	set_console_size();
	TextColor(t_color);
	//first layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "  ___   ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << " _____  ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << " _____  ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << " _____  ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << " _____  ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << " _____  ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << " _____  ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << " _   _  ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << " _____  ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "   ___  ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << " _   __ ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << " _      ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << " __  __  ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << " _   _  ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << " _____  ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << " _____  ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << " _____  ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << " _____  ";
		if (input[i] == 'S' || input[i] == 's')
			cout << " _____  ";
		if (input[i] == 'T' || input[i] == 't')
			cout << " _____  ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << " _   _  ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << " _   _  ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << " _    _  ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << "__   __ ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "__   __ ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << " ______ ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << " _  ";
		if (input[i] == '~')
			cout << "      ";
		if (input[i] == '1')
			cout << " __   ";
		if (input[i] == '2')
			cout << " _____  ";
		if (input[i] == '3')
			cout << " _____  ";
		if (input[i] == '4')
			cout << "   ___  ";
		if (input[i] == '5')
			cout << " _____  ";
		if (input[i] == '6')
			cout << "  ____  ";
		if (input[i] == '7')
			cout << " ______ ";
		if (input[i] == '8')
			cout << " _____  ";
		if (input[i] == '9')
			cout << " _____  ";
		if (input[i] == '0')
			cout << " _____  ";
		if (input[i] == '!')
			cout << " _  ";
		if (input[i] == '@')
			cout << "   ____   ";
		if (input[i] == '#')
			cout << "   _  _    ";
		if (input[i] == '$')
			cout << "  _   ";
		if (input[i] == '%')
			cout << " _   __ ";
		if (input[i] == '^')
			cout << " /\\  ";
		if (input[i] == '&')
			cout << "         ";
		if (input[i] == '*')
			cout << "    _     ";
		if (input[i] == '(')
			cout << "  __ ";
		if (input[i] == ')')
			cout << "__   ";
		if (input[i] == '-')
			cout << "         ";
		if (input[i] == '_')
			cout << "         ";
		if (input[i] == '=')
			cout << "         ";
		if (input[i] == '+')
			cout << "        ";
		if (input[i] == '[')
			cout << " ___  ";
		if (input[i] == '{')
			cout << "   __ ";
		if (input[i] == ']')
			cout << " ___  ";
		if (input[i] == '}')
			cout << "__    ";
		if (input[i] == '|')
			cout << " _  ";
		if (input[i] == '\\')
			cout << "__      ";
		if (input[i] == ';')
			cout << " _  ";
		if (input[i] == ':')
			cout << "    ";
		if (input[i] == '\'')
			cout << " _  ";
		if (input[i] == '"')
			cout << " _ _  ";
		if (input[i] == '<')
			cout << "   __ ";
		if (input[i] == ',')
			cout << "    ";
		if (input[i] == '>')
			cout << "__    ";
		if (input[i] == '/')
			cout << "     __ ";
		if (input[i] == '?')
			cout << " ___   ";
	}
	cout << endl;
	//second layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << " / _ \\  ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "| ___ \\ ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << "/  __ \\ ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "|  _  \\ ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "|  ___| ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "|  ___| ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << "|  __ \\ ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "| | | | ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << "|_   _| ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "  |_  | ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "| | / / ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "| |     ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "|  \\/  | ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "| \\ | | ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << "|  _  | ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "| ___ \\ ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << "|  _  | ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "| ___ \\ ";
		if (input[i] == 'S' || input[i] == 's')
			cout << "/  ___| ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "|_   _| ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << "| | | | ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << "| | | | ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << "| |  | | ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << "\\ \\ / / ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "\\ \\ / / ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "|___  / ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << "( ) ";
		if (input[i] == '~')
			cout << "      ";
		if (input[i] == '1')
			cout << "/  |  ";
		if (input[i] == '2')
			cout << "/ __  \\ ";
		if (input[i] == '3')
			cout << "|____ | ";
		if (input[i] == '4')
			cout << "  /   | ";
		if (input[i] == '5')
			cout << "|  ___| ";
		if (input[i] == '6')
			cout << " / ___| ";
		if (input[i] == '7')
			cout << "|___  / ";
		if (input[i] == '8')
			cout << "|  _  | ";
		if (input[i] == '9')
			cout << "|  _  | ";
		if (input[i] == '0')
			cout << "|  _  | ";
		if (input[i] == '!')
			cout << "| | ";
		if (input[i] == '@')
			cout << "  / __ \\  ";
		if (input[i] == '#')
			cout << " _| || |_  ";
		if (input[i] == '$')
			cout << " | |  ";
		if (input[i] == '%')
			cout << "(_) / / ";
		if (input[i] == '^')
			cout << "|/\\| ";
		if (input[i] == '&')
			cout << "  ___    ";
		if (input[i] == '*')
			cout << " /\\| |/\\  ";
		if (input[i] == '(')
			cout << " / / ";
		if (input[i] == ')')
			cout << "\\ \\  ";
		if (input[i] == '-')
			cout << "         ";
		if (input[i] == '_')
			cout << "         ";
		if (input[i] == '=')
			cout << " ______  ";
		if (input[i] == '+')
			cout << "   _    ";
		if (input[i] == '[')
			cout << "|  _| ";
		if (input[i] == '{')
			cout << "  / / ";
		if (input[i] == ']')
			cout << "|_  | ";
		if (input[i] == '}')
			cout << "\\ \\   ";
		if (input[i] == '|')
			cout << "| | ";
		if (input[i] == '\\')
			cout << "\\ \\     ";
		if (input[i] == ';')
			cout << "(_) ";
		if (input[i] == ':')
			cout << " _  ";
		if (input[i] == '\'')
			cout << "( ) ";
		if (input[i] == '"')
			cout << "( | ) ";
		if (input[i] == '<')
			cout << "  / / ";
		if (input[i] == ',')
			cout << "    ";
		if (input[i] == '>')
			cout << "\\ \\   ";
		if (input[i] == '/')
			cout << "    / / ";
		if (input[i] == '?')
			cout << "|__ \\  ";
	}
	cout << endl;
	//third layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "/ /_\\ \\ ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "| |_/ / ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << "| /  \\/ ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "| | | | ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "| |__   ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "| |_    ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << "| |  \\/ ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "| |_| | ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << "  | |   ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "    | | ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "| |/ /  ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "| |     ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "| .  . | ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "|  \\| | ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << "| | | | ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "| |_/ / ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << "| | | | ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "| |_/ / ";
		if (input[i] == 'S' || input[i] == 's')
			cout << "\\ `--.  ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "  | |   ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << "| | | | ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << "| | | | ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << "| |  | | ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << " \\ V /  ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << " \\ V /  ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "   / /  ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << " \\| ";
		if (input[i] == '~')
			cout << " /\\/| ";
		if (input[i] == '1')
			cout << "`| |  ";
		if (input[i] == '2')
			cout << "`' / /' ";
		if (input[i] == '3')
			cout << "    / / ";
		if (input[i] == '4')
			cout << " / /| | ";
		if (input[i] == '5')
			cout << "|___ \\  ";
		if (input[i] == '6')
			cout << "/ /___  ";
		if (input[i] == '7')
			cout << "   / /  ";
		if (input[i] == '8')
			cout << " \\ V /  ";
		if (input[i] == '9')
			cout << "| |_| | ";
		if (input[i] == '0')
			cout << "| |/' | ";
		if (input[i] == '!')
			cout << "| | ";
		if (input[i] == '@')
			cout << " / / _` | ";
		if (input[i] == '#')
			cout << "|_  __  _| ";
		if (input[i] == '$')
			cout << "/ __) ";
		if (input[i] == '%')
			cout << "   / /  ";
		if (input[i] == '^')
			cout << "     ";
		if (input[i] == '&')
			cout << " ( _ )   ";
		if (input[i] == '*')
			cout << " \\ ` ' /  ";
		if (input[i] == '(')
			cout << "| |  ";
		if (input[i] == ')')
			cout << " | | ";
		if (input[i] == '-')
			cout << " ______  ";
		if (input[i] == '_')
			cout << "         ";
		if (input[i] == '=')
			cout << "|______| ";
		if (input[i] == '+')
			cout << " _| |_  ";
		if (input[i] == '[')
			cout << "| |   ";
		if (input[i] == '{')
			cout << " | |  ";
		if (input[i] == ']')
			cout << "  | | ";
		if (input[i] == '}')
			cout << " | |  ";
		if (input[i] == '|')
			cout << "| | ";
		if (input[i] == '\\')
			cout << " \\ \\    ";
		if (input[i] == ';')
			cout << "    ";
		if (input[i] == ':')
			cout << "(_) ";
		if (input[i] == '\'')
			cout << "|/  ";
		if (input[i] == '"')
			cout << " V V  ";
		if (input[i] == '<')
			cout << " / /  ";
		if (input[i] == ',')
			cout << "    ";
		if (input[i] == '>')
			cout << " \\ \\  ";
		if (input[i] == '/')
			cout << "   / /  ";
		if (input[i] == '?')
			cout << "   ) | ";
	}
	cout << endl;
	//fourth layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "|  _  | ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "| ___ \\ ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << "| |     ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "| | | | ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "|  __|  ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "|  _|   ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << "| | __  ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "|  _  | ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << "  | |   ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "    | | ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "|    \\  ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "| |     ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "| |\\/| | ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "| . ` | ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << "| | | | ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "|  __/  ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << "| | | | ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "|    /  ";
		if (input[i] == 'S' || input[i] == 's')
			cout << " `--. \\ ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "  | |   ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << "| | | | ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << "| | | | ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << "| |/\\| | ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << " / ^ \\  ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "  \\ /   ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "  / /   ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << "    ";
		if (input[i] == '~')
			cout << "|/\\/  ";
		if (input[i] == '1')
			cout << " | |  ";
		if (input[i] == '2')
			cout << "  / /   ";
		if (input[i] == '3')
			cout << "    \\ \\ ";
		if (input[i] == '4')
			cout << "/ /_| | ";
		if (input[i] == '5')
			cout << "    \\ \\ ";
		if (input[i] == '6')
			cout << "| ___ \\ ";
		if (input[i] == '7')
			cout << "  / /   ";
		if (input[i] == '8')
			cout << " / _ \\  ";
		if (input[i] == '9')
			cout << "\\____ | ";
		if (input[i] == '0')
			cout << "|  /| | ";
		if (input[i] == '!')
			cout << "| | ";
		if (input[i] == '@')
			cout << "| | (_| | ";
		if (input[i] == '#')
			cout << " _| || |_  ";
		if (input[i] == '$')
			cout << "\\__ \\ ";
		if (input[i] == '%')
			cout << "  / /   ";
		if (input[i] == '^')
			cout << "     ";
		if (input[i] == '&')
			cout << " / _ \\/\\ ";
		if (input[i] == '*')
			cout << "|_     _| ";
		if (input[i] == '(')
			cout << "| |  ";
		if (input[i] == ')')
			cout << " | | ";
		if (input[i] == '-')
			cout << "|______| ";
		if (input[i] == '_')
			cout << "         ";
		if (input[i] == '=')
			cout << " ______  ";
		if (input[i] == '+')
			cout << "|_   _| ";
		if (input[i] == '[')
			cout << "| |   ";
		if (input[i] == '{')
			cout << "< <   ";
		if (input[i] == ']')
			cout << "  | | ";
		if (input[i] == '}')
			cout << "  > > ";
		if (input[i] == '|')
			cout << "| | ";
		if (input[i] == '\\')
			cout << "  \\ \\   ";
		if (input[i] == ';')
			cout << " _  ";
		if (input[i] == ':')
			cout << "    ";
		if (input[i] == '\'')
			cout << "    ";
		if (input[i] == '"')
			cout << "      ";
		if (input[i] == '<')
			cout << "< <   ";
		if (input[i] == ',')
			cout << " _  ";
		if (input[i] == '>')
			cout << "  > > ";
		if (input[i] == '/')
			cout << "  / /   ";
		if (input[i] == '?')
			cout << "  / /  ";
	}
	cout << endl;
	//fifth layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "| | | | ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "| |_/ / ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << "| \\__/\\ ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "| |/ /  ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "| |___  ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "| |     ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << "| |_\\ \\ ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "| | | | ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << " _| |_  ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "/\\__/ / ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "| |\\  \\ ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "| |____ ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "| |  | | ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "| |\\  | ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << "\\ \\_/ / ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "| |     ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << "\\ \\/' / ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "| |\\ \\  ";
		if (input[i] == 'S' || input[i] == 's')
			cout << "/\\__/ / ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "  | |   ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << "| |_| | ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << "\\ \\_/ / ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << "\\  /\\  / ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << "/ / \\ \\ ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "  | |   ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "./ /___ ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << "    ";
		if (input[i] == '~')
			cout << "      ";
		if (input[i] == '1')
			cout << "_| |_ ";
		if (input[i] == '2')
			cout << "./ /___ ";
		if (input[i] == '3')
			cout << ".___/ / ";
		if (input[i] == '4')
			cout << "\\___  | ";
		if (input[i] == '5')
			cout << "/\\__/ / ";
		if (input[i] == '6')
			cout << "| \\_/ | ";
		if (input[i] == '7')
			cout << "./ /    ";
		if (input[i] == '8')
			cout << "| |_| | ";
		if (input[i] == '9')
			cout << ".___/ / ";
		if (input[i] == '0')
			cout << "\\ |_/ / ";
		if (input[i] == '!')
			cout << "|_| ";
		if (input[i] == '@')
			cout << " \\ \\__,_| ";
		if (input[i] == '#')
			cout << "|_  __  _| ";
		if (input[i] == '$')
			cout << "(   / ";
		if (input[i] == '%')
			cout << " / / _  ";
		if (input[i] == '^')
			cout << "     ";
		if (input[i] == '&')
			cout << "| (_>  < ";
		if (input[i] == '*')
			cout << " / , . \\  ";
		if (input[i] == '(')
			cout << "| |  ";
		if (input[i] == ')')
			cout << " | | ";
		if (input[i] == '-')
			cout << "         ";
		if (input[i] == '_')
			cout << " ______  ";
		if (input[i] == '=')
			cout << "|______| ";
		if (input[i] == '+')
			cout << "  |_|   ";
		if (input[i] == '[')
			cout << "| |_  ";
		if (input[i] == '{')
			cout << " | |  ";
		if (input[i] == ']')
			cout << " _| | ";
		if (input[i] == '}')
			cout << " | |  ";
		if (input[i] == '|')
			cout << "| | ";
		if (input[i] == '\\')
			cout << "   \\ \\  ";
		if (input[i] == ';')
			cout << "( ) ";
		if (input[i] == ':')
			cout << " _  ";
		if (input[i] == '\'')
			cout << "    ";
		if (input[i] == '"')
			cout << "      ";
		if (input[i] == '<')
			cout << " \\ \\  ";
		if (input[i] == ',')
			cout << "( ) ";
		if (input[i] == '>')
			cout << " / /  ";
		if (input[i] == '/')
			cout << " / /    ";
		if (input[i] == '?')
			cout << " |_|   ";
	}
	cout << endl;
	//sixth layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "\\_| |_/ ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "\\____/  ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << " \\____/ ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "|___/   ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "\\____/  ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "\\_|     ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << " \\____/ ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "\\_| |_/ ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << " \\___/  ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "\\____/  ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "\\_| \\_/ ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "\\_____/ ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "\\_|  |_/ ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "\\_| \\_/ ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << " \\___/  ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "\\_|     ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << " \\_/\\_\\ ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "\\_| \\_| ";
		if (input[i] == 'S' || input[i] == 's')
			cout << "\\____/  ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "  \\_/   ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << " \\___/  ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << " \\___/  ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << " \\/  \\/  ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << "\\/   \\/ ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "  \\_/   ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "\\_____/ ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << "    ";
		if (input[i] == '~')
			cout << "      ";
		if (input[i] == '1')
			cout << "\\___/ ";
		if (input[i] == '2')
			cout << "\\_____/ ";
		if (input[i] == '3')
			cout << "\\____/  ";
		if (input[i] == '4')
			cout << "    |_/ ";
		if (input[i] == '5')
			cout << "\\____/  ";
		if (input[i] == '6')
			cout << "\\_____/ ";
		if (input[i] == '7')
			cout << "\\_/     ";
		if (input[i] == '8')
			cout << "\\_____/ ";
		if (input[i] == '9')
			cout << "\\____/  ";
		if (input[i] == '0')
			cout << " \\___/  ";
		if (input[i] == '!')
			cout << "(_) ";
		if (input[i] == '@')
			cout << "  \\____/  ";
		if (input[i] == '#')
			cout << "  |_||_|   ";
		if (input[i] == '$')
			cout << " |_|  ";
		if (input[i] == '%')
			cout << "/_/ (_) ";
		if (input[i] == '^')
			cout << "     ";
		if (input[i] == '&')
			cout << " \\___/\\/ ";
		if (input[i] == '*')
			cout << " \\/|_|\\/  ";
		if (input[i] == '(')
			cout << " \\_\\ ";
		if (input[i] == ')')
			cout << "/_/  ";
		if (input[i] == '-')
			cout << "         ";
		if (input[i] == '_')
			cout << "|______| ";
		if (input[i] == '=')
			cout << "         ";
		if (input[i] == '+')
			cout << "        ";
		if (input[i] == '[')
			cout << "|___| ";
		if (input[i] == '{')
			cout << "  \\_\\ ";
		if (input[i] == ']')
			cout << "|___| ";
		if (input[i] == '}')
			cout << "/_/   ";
		if (input[i] == '|')
			cout << "|_| ";
		if (input[i] == '\\')
			cout << "    \\_\\ ";
		if (input[i] == ';')
			cout << "|/  ";
		if (input[i] == ':')
			cout << "(_) ";
		if (input[i] == '\'')
			cout << "    ";
		if (input[i] == '"')
			cout << "      ";
		if (input[i] == '<')
			cout << "  \\_\\ ";
		if (input[i] == ',')
			cout << "|/  ";
		if (input[i] == '>')
			cout << "/_/   ";
		if (input[i] == '/')
			cout << "/_/     ";
		if (input[i] == '?')
			cout << " (_)   ";
	}
	cout << endl;
}

int ProcessFinish(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, bool& _TURN, int pWhoWin, string& NamePlayer_O, string& NamePlayer_X, WinningPos WP[5])
{
	GotoXY(0, _A[B_SIZE - 1][B_SIZE - 1].y + 2);
	switch (pWhoWin) {
	case 1:
		SetOWin(NamePlayer_O, WP,_A);
		break;
	case -1:
		SetXWin(NamePlayer_X, WP, _A);
		break;
	case 0:
		SetConsoleBlank();
		ascii_art(" DRAW !!", 1, 5, RED);
		break;
	case 2:
		_TURN = !_TURN;
		break;
	}
	GotoXY(_X, _Y);
	return pWhoWin;
}

char AskContinue(_POINT _A[B_SIZE][B_SIZE])
{
	GotoXY(20, 25);
	cout << "DO YOU WANT CONTINUE ?? [Y/N] ";
	return toupper(_getch());
}

void AskTurn(bool& _TURN, string& NamePlayer_O, string& NamePlayer_X) { // Hỏi lượt đánh trước
	DrawBoxMini(90, 22, 15, 6, GREEN);//vẽ khung to
	// Vẽ hai ô hiển thị O vs X
	int wide = 20;
	int high = 10;
	int x = 20;
	int y = 10;
	DrawAsciiFile(0, 1, "DrawTurn", BLUE);
	DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnO", GRAY);
	DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnX", GRAY);
	// Vẽ ô hiển thị tên
	int WideBoxName = 30;
	int HighBoxName = 3;
	int X_BoxName = 44;
	int Y_BoxName = 10;
	DrawBoxMini(WideBoxName, HighBoxName, X_BoxName, Y_BoxName, MAGENTA);
	GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_O.size() / 2, Y_BoxName + 1);
	TextColor(GREEN);
	cout << NamePlayer_O;
	GotoXY(X_BoxName + 1, Y_BoxName + 1);
	TextColor(BLUE);
	cout << (unsigned char)17;
	GotoXY(X_BoxName + WideBoxName - 2, Y_BoxName + 1);
	TextColor(BLUE);
	cout << (unsigned char)16;
	TextColor(RED);
	bool check = true;
	while (true) {
		char press = toupper(_getch());
		PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		if (press == 'D' || press == 'A') {
			if (press == 'D')
			{
				GotoXY(X_BoxName + WideBoxName - 2, Y_BoxName + 1);
				TextColor(YELLOW);
				cout << (unsigned char)16;
				Sleep(200);
				GotoXY(X_BoxName + WideBoxName - 2, Y_BoxName + 1);
				TextColor(BLUE);
				cout << (unsigned char)16;
			}
			else if (press == 'A') {
				GotoXY(X_BoxName + 1, Y_BoxName + 1);
				TextColor(YELLOW);
				cout << (unsigned char)17;
				Sleep(200);
				GotoXY(X_BoxName + 1, Y_BoxName + 1);
				TextColor(BLUE);
				cout << (unsigned char)17;
			}
			if (check == true)
			{
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_O.size() / 2, Y_BoxName + 1);
				for (int i = 0; i < NamePlayer_O.size(); i++)
					cout << ' ';
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_X.size() / 2, Y_BoxName + 1);
				TextColor(GREEN);
				cout << NamePlayer_X;
				check = false;
			}
			else if (check == false) {
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_X.size() / 2, Y_BoxName + 1);
				for (int i = 0; i < NamePlayer_X.size(); i++)
					cout << ' ';
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_O.size() / 2, Y_BoxName + 1);
				TextColor(GREEN);
				cout << NamePlayer_O;
				check = true;
			}
		}
		else if (press == ENTER) {
			break;
		}
	}
	GotoXY(x, y);
	DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnO", BLUE);
	while (true) {
		unsigned char c = toupper(_getch());
		PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		if (c == 'A' || c == 'D') {
			if (c == 'A') {
				if (x == 50) {
					DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnX", GRAY);
					x -= 30;
					DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnO", BLUE);
				}
			}
			else if (c == 'D') {
				if (x == 20) {
					DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnO", GRAY);
					x += 30;
					DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnX", RED);
				}
			}
		}
		else if (c == ENTER) {
			if (x == 20) {
				_TURN = true; // true là lượt của O
				if (check == false)
					swap(NamePlayer_O, NamePlayer_X);
				return;
			}
			else if (x == 50) {
				_TURN = false; // false là lượt của X
				if (check == true)
					swap(NamePlayer_O, NamePlayer_X);
				return;
			}
		}
	}
}

void EnterNamePlayer(string& NamePlayer_O, string& NamePlayer_X) {
	DrawAsciiFile(0, 1, "DrawEnterName", BLUE);
	TextColor(BLUE);
	GotoXY(11, 11);
	cout << "Enter Name Player 1 (20 character max): "; 
	while (true) {
		getline(cin, NamePlayer_O);
		if (NamePlayer_O.size() <= 20)
			break;
		GotoXY(51, 11);
		for (int i = 0; i < NamePlayer_O.size(); i++)
			cout << ' ';
		GotoXY(51, 11);
	}

	GotoXY(11, 12);
	cout << "Enter Name Player 2 (20 character max): "; 
	while (true) {
		getline(cin, NamePlayer_X);
		if (NamePlayer_X.size() <= 20)
			break;
		GotoXY(51, 12);
		for (int i = 0; i < NamePlayer_X.size(); i++)
			cout << ' ';
		GotoXY(51, 12);
	}
}

// Đếm số lượt chơi và in ra màn hình console
void CntTurn(bool& _TURN, int& cntX, int& cntO, bool validEnter) {
	TextColor(BLUE);
	GotoXY(85, 9);
	cout << cntO;
	GotoXY(85, 11);
	cout << cntX;
	if (_TURN == false && validEnter == true)
	{
		++cntX;
		GotoXY(85, 11);
		cout << cntX;

	}
	else if (_TURN == true && validEnter == true)
	{
		++cntO;
		GotoXY(85, 9);
		cout << cntO;
	}
}

// Hiển thị lượt chơi
void ShowTurn(int _X, int _Y, bool _TURN, bool validEnter)
{
	if (_TURN == true && validEnter == true)
	{
		/*GotoXY(80, 0);
		cout << "Luot cua X danh !!";*/
		TurnX();
	}
	else if (_TURN == false && validEnter == true)
	{
		/*GotoXY(80, 0);
		cout << "Luot cua O danh !!";*/
		TurnO();
	}
	GotoXY(_X, _Y);
}

void UnHoverCell(_POINT _A[B_SIZE][B_SIZE], int x, int y) {
	int tmp = GetCurrentColor();
	TextColor(BLUE);
	GotoXY(_A[x][y].x - 1, _A[x][y].y);
	if (_A[x][y].c == 0)
		cout << "   ";
	else if (_A[x][y].c == 1) {
		TextColor(O_COLOR);
		cout << " O ";
	}
	else {
		TextColor(X_COLOR);
		cout << " X ";
	}
	TextColor(tmp);
}

void HoverCell(_POINT _A[B_SIZE][B_SIZE], int x, int y) {
	int tmp = GetCurrentColor();
	//TextColor(BLUE & 15 | BACKGROUND_YELLOW);
	TextColor(YELLOW);
	GotoXY(_A[x][y].x - 1, _A[x][y].y);
	if (_A[x][y].c == 0)
		cout << L_TRIANGLE << " " << R_TRIANGLE;
	else if (_A[x][y].c == 1) {
		cout << L_TRIANGLE;
		//TextColor(O_COLOR & 15 | BACKGROUND_YELLOW);
		TextColor(O_COLOR);
		cout << "O";
		TextColor(YELLOW);
		cout << R_TRIANGLE;
	}
	else {
		cout << L_TRIANGLE;
		//TextColor(X_COLOR & 15 | BACKGROUND_YELLOW);
		TextColor(X_COLOR);
		cout << "X";
		TextColor(YELLOW);
		cout << R_TRIANGLE;
	}
	TextColor(tmp);
}

void ExitGame() {
	SetConsoleBlank();
	exit(0);
}

void HideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void DrawSaveFilesPage(const vector <string>& v, int curPage) {
	int filePerPage = 9;
	int tmp = GetCurrentColor();
	TextColor(YELLOW);
	GotoXY(WIDTH / 2 - 5, HEIGHT / 2 + 8);
	cout << "< ";
	if (curPage <= 9)
		cout << "0";
	cout << curPage << " / ";
	int nPages = ceil(1.0 * v.size() / filePerPage);
	if (nPages <= 9)
		cout << 0;
	cout << nPages << " >";
	TextColor(tmp);

	for (int i = (curPage - 1) * 9, cnt = 1; i < curPage * 9; i++, cnt++) {
		GotoXY(BOX_X + 1, BOX_Y + 2 * cnt - 1);
		for (int j = 1; j < BOX_W - 1; j++)
			cout << " ";
		if (i < v.size()) {
			int n = v[i].size();
			GotoXY(WIDTH / 2 - n / 2, BOX_Y + 2 * cnt - 1);
			Sleep(50);
			cout << v[i];
		}
	}
}

void UnhoverFileName(const vector <string>& v, int curPage, int curFile) {
	int id = 9 * (curPage - 1) + curFile;
	TextColor(CYAN);
	GotoXY(BOX_X + 1, BOX_Y + 2 * (curFile + 1) - 1);
	for (int j = 1; j < BOX_W - 1; j++)
		cout << " ";
	int n = v[id].size();
	GotoXY(WIDTH / 2 - n / 2, BOX_Y + 2 * (curFile + 1) - 1);
	cout << v[id];
}

void HoverFileName(const vector <string>& v, int curPage, int curFile) {
	int id = 9 * (curPage - 1) + curFile;
	int tmp = GetCurrentColor();
	TextColor(RED & 15 | BACKGROUND_YELLOW);
	GotoXY(BOX_X + 1, BOX_Y + 2 * (curFile + 1) - 1);
	cout << "        " << L_TRIANGLE;
	for (int j = 9; j < BOX_W - 11; j++) 
		cout << " ";
	cout << R_TRIANGLE << "        ";
	int n = v[id].size();
	GotoXY(WIDTH / 2 - n / 2, BOX_Y + 2 * (curFile + 1) - 1);
	cout << v[id];
	TextColor(tmp);
}

void LoadGameMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool& sound, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, WinningPos WP[5]) {
	// Open the file that contains all the name of the saved games.
	fstream inp;
	inp.open("save\\all_save.txt", ios::in);
	if (inp.fail()) {
		cout << "Can't open file\n";
		return;
	}

	SetConsoleBlank();
	BackGround();
	DrawBox(BOX_W, BOX_H - 1, BOX_X, BOX_Y, GREEN, 1);
	TextColor(CYAN);

	// Get the current save data
	string nameFile;
	int filePerPage = 9;
	vector <string> v;
	while (inp >> nameFile) {
		v.push_back(nameFile);
	}
	int nFiles = v.size();
	int nPages = ceil(1.0 * nFiles / filePerPage);

	int curFile = 0, curPage = 1;
	DrawSaveFilesPage(v, 1);
	GotoXY(47, 26);
	TextColor(MAGENTA);
	cout << " " << L_TRIANGLE << " PRESS ESC TO COMEBACK " << R_TRIANGLE << " ";
	HoverFileName(v, 1, 0);
	while (true) {
		int _COMMAND = toupper(_getch());
		if (sound) PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		if (_COMMAND == ESC) {
			return;
		}
		else if (_COMMAND == 'S') {
			UnhoverFileName(v, curPage, curFile);
			curFile = (curFile + 1) % filePerPage;
			if (curPage == nPages && curFile + 9 * (curPage - 1) >= nFiles)
				curFile = 0;
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == 'W') {
			UnhoverFileName(v, curPage, curFile);
			curFile = (curFile - 1 + filePerPage) % filePerPage;
			if (curPage == nPages && curFile + 9 * (curPage - 1) >= nFiles)
				curFile = nFiles % 9 - 1;
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == 'A') {
			curPage--;
			if (curPage == 0)
				curPage = nPages;
			if (curPage == nPages && curFile + 9 * (curPage - 1) >= nFiles)
				curFile = nFiles % 9 - 1;
			DrawSaveFilesPage(v, curPage);
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == 'D') {
			curPage++;
			if (curPage == nPages && curFile + 9 * (curPage - 1) >= nFiles)
				curFile = nFiles % 9 - 1;
			else if (curPage > nPages)
				curPage = 1;
			DrawSaveFilesPage(v, curPage);
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == ENTER) {
			LoadData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, v[(curPage - 1) * 9 + curFile]);
			LoadingScreen(BLUE, GREEN, LIGHT_CYAN);
			StartGame(_A, 0, _TURN, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, WP);
			return;
		}
	}
	inp.close();
}

void DrawCaroBox(int w, int h, int x, int y, int Time)
{
	TextColor(GREEN);
	GotoXY(x + w / 2, y);
	for (int i = 0; i < w / 2; i++)
	{
		GotoXY(x + w / 2 + i, y);
		cout << BOX_H_LINE;
		GotoXY(x + w / 2 - i, y);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	GotoXY(x, y);
	cout << BOX_TOP_LEFT;
	GotoXY(x + w, y);
	cout << BOX_TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, i + y);
		cout << BOX_V_LINE;
		for (int j = 1; j < w; j++)
			cout << SPACE;
		cout << BOX_V_LINE;
		Sleep(Time);
	}

	GotoXY(x, h + y - 1);
	cout << BOX_BOTTOM_LEFT;
	GotoXY(x + w, h + y - 1);
	cout << BOX_BOTTOM_RIGHT;
	GotoXY(x, y + h - 5);
	cout << BOX_LEFT;
	GotoXY(x + w, y + h - 5);
	cout << BOX_RIGHT;
	for (int i = 1; i <= w / 2; i++)
	{
		GotoXY(x + i, y + h - 1);
		cout << BOX_H_LINE;
		GotoXY(x + w - i, y + h - 1);
		cout << BOX_H_LINE;
		GotoXY(x + i, y + h - 5);
		cout << BOX_H_LINE;
		GotoXY(x + w - i, y + h - 5);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	DrawBoxMini(58, 13, 14, 6, LIGHT_YELLOW);
	CaroAnimation();
	Sleep(500);
	PrintNote(23, 21, MAGENTA);
}

void MainScreen() {
	BackGround();
	DrawCaroBox(62, 19, 12, 5, 5);
	Sleep(500);
	DrawButton();
}

void MainMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool& sound, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, WinningPos WP[5])
{
	LoadingScreen(BLUE, GREEN, LIGHT_CYAN);
	Sleep(50);
	SetConsoleBlank();
	BackGround();
	MainScreen();
	int x = 94;
	int y = 7;
	DrawBoxMini(14, 3, 89, y - 1, RED);
	GotoXY(x, y); // Đưa cursor tới phím chức năng đầu tiên.
	cout << (unsigned char)16 << "PLAY";
	while (true)
	{
		unsigned char c = toupper(_getch());
		if (sound) PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		if (c == 'W' || c == 'S')
		{
			//c = _getch();
			if (c == 'W')
			{
				if ((y >= 10) && (y <= 19))
				{
					// Đưa lại nút cũ về màu xanh
					DrawBoxMini(14, 3, 89, y - 1, BLUE);
					if (y == 7)
					{
						GotoXY(x, y);
						cout << "PLAY";
					}
					if (y == 10)
					{
						GotoXY(x, y);
						cout << "LOAD";
					}
					if (y == 13)
					{
						GotoXY(x, y);
						cout << "HELP";
					}
					if (y == 16)
					{
						GotoXY(x - 1, y);
						cout << "SETTING";
					}
					if (y == 19)
					{
						GotoXY(x, y);
						cout << "EXIT";
					}
					y = y - 3;
					//Biến nút đang trỏ vào thành màu đỏ 
					DrawBoxMini(14, 3, 89, y - 1, RED);
					GotoXY(x, y);

					if (y == 7)
					{
						GotoXY(x, y);
						cout << (unsigned char)16 << "PLAY";
					}
					if (y == 10)
					{
						GotoXY(x, y);
						cout << (unsigned char)16 << "LOAD";
					}
					if (y == 13)
					{
						GotoXY(x, y);
						cout << (unsigned char)16 << "HELP";
					}
					if (y == 16)
					{
						GotoXY(x - 1, y);
						cout << (unsigned char)16 << "SETTING";
					}
					if (y == 19)
					{
						GotoXY(x, y);
						cout << (unsigned char)16<< "EXIT";
					}

				}
			}
			else if (c == 'S')
			{
				if ((y >= 7) && (y <= 16))
				{
					DrawBoxMini(14, 3, 89, y - 1, BLUE);
					if (y == 7)
					{
						GotoXY(x, y);
						cout << "PLAY";
					}
					if (y == 10)
					{
						GotoXY(x, y);
						cout << "LOAD";
					}
					if (y == 13)
					{
						GotoXY(x, y);
						cout << "HELP";
					}
					if (y == 16)
					{
						GotoXY(x - 1, y);
						cout << "SETTING";
					}
					if (y == 19)
					{
						GotoXY(x, y);
						cout << "EXIT";
					}
					y = y + 3;
					DrawBoxMini(14, 3, 89, y - 1, RED);
					GotoXY(x, y);

					if (y == 7)
					{
						GotoXY(x, y);
						cout << (unsigned char)16 << "PLAY";
					}
					if (y == 10)
					{
						GotoXY(x, y);
						cout << (unsigned char)16 << "LOAD";
					}
					if (y == 13)
					{
						GotoXY(x, y);
						cout << (unsigned char)16 << "HELP";
					}
					if (y == 16)
					{
						GotoXY(x - 1, y);
						cout << (unsigned char)16 << "SETTING";
					}
					if (y == 19)
					{
						GotoXY(x, y);
						cout << (unsigned char)16 << "EXIT";
					}

				}
			}
		}
		else if ((c == 32) || (c == 13)) // Tương tác với phím bằng cách bấm Enter hoặc Space
		{
			if (y == 7)
			{
				StartGame(_A, 1, _TURN, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, WP);
				return;
			}
			if (y == 10)
			{
				LoadGameMenu(_A, _TURN, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, WP);
				return;
			}
			if (y == 13)
			{
				HelpScreen(sound);
				return;
			}
			if (y == 16)
			{
				SettingMenu(sound);
				return;
			}
			if (y == 19)
			{
				ExitGame();
			}
		}
	}
}

//Help1 2 là để nhét dô HelpScreen cho gọn
void Help1()
{
	TextColor(RED);
	GotoXY(20, 7);
	cout << L_TRIANGLE << " RULE " << R_TRIANGLE;
	TextColor(GREEN);
	GotoXY(20, 14);
	cout << L_TRIANGLE << " MOVE " << R_TRIANGLE;
	TextColor(MAGENTA);
	GotoXY(18, 20);
	cout << L_TRIANGLE << " ABOUT US " << R_TRIANGLE;
}

void Help2()
{
	TextColor(RED);
	GotoXY(40, 5);
	cout << "The game is played on a board with 12 rows and 12 columns." << endl;
	GotoXY(40, 7);
	cout << "To win the round, player needs to make a line consisting of 5" << endl;
	GotoXY(40, 8);
	cout << "consecutive pieces horizontally, vertically or diagonally." << endl;
	GotoXY(40, 10);
	cout << "If more than 90% of the board has been marked, the result will ";
	GotoXY(40, 11);
	cout << "be a draw.";
	TextColor(GREEN);
	GotoXY(40, 14);
	cout << "Up: W";
	GotoXY(40, 15);
	cout << "Down: S";
	GotoXY(55, 14);
	cout << "Left: A";
	GotoXY(55, 15);
	cout << "Right: D";
	GotoXY(70, 14);
	cout << "Choose: Enter";
	TextColor(MAGENTA);
	GotoXY(76, 19);
	cout << "Teacher: Truong Toan Thinh";
	GotoXY(76, 20);
	cout << "Group: 13";
	GotoXY(76, 21);
	cout << "22CTT4 - HCMUS";
	GotoXY(40, 18);
	cout << "Dang Duy Lan      -  22120182";
	GotoXY(40, 19);
	cout << "Nguyen Nhat Long  -  22120194";
	GotoXY(40, 20);
	cout << "Hoang Thanh Man   -  22120200";
	GotoXY(40, 21);
	cout << "Ly Truong Nam     -  22120218";
	GotoXY(40, 22);
	cout << "Tran Thao Ngan    -  22120225";
	TextColor(LIGHT_RED);
	GotoXY(47, 26);
	cout << " " << L_TRIANGLE << " PRESS ESC TO COMEBACK " << R_TRIANGLE << " ";
}

void HelpScreen(bool sound)
{
	SetConsoleBlank();
	DrawBox(98, 25, 11, 2, CYAN, 0);
	DrawBoxMini(94, 23, 13, 3, LIGHT_CYAN);
	for (int i = 0; i < 21; i++)
	{
		GotoXY(34, 4 + i);
		cout << V_LINE;
	}
	Help1();
	Help2();
	while (true) {
		char c = _getch();
		if (sound) PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		if (c == ESC)
			return;
	}
}

void LoadingScreen(int color1, int color2, int color3) //color 1 la mau khung, 2 la mau chu, 3 la mau cai thanh o giua
{
	SetConsoleBlank();
	unsigned char s = { 219 };
	DrawBoxMini(51, 3, 34, 13, color1);
	GotoXY(55, 17);
	TextColor(color2);
	cout << "LOADING...";
	GotoXY(36, 14);
	for (int i = 0; i < 34; i++)
	{
		TextColor(color3);
		cout << s;
		Sleep(10);
	}
	Sleep(200);
	GotoXY(70, 14);
	for (int i = 0; i < 13; i++)
	{
		TextColor(color3);
		cout << s;
		Sleep(10);
	}
}

void CreateConsoleWindow(int pWidth, int pHeight)
{
	HWND consoleWindow = GetConsoleWindow();
	RECT r;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 240);
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, 0, 0, pWidth, pHeight, TRUE);
}

void SettingMenu(bool& sound) {
	SetConsoleBlank();
	GotoXY(50, 15);
	int tmp = GetCurrentColor();
	TextColor(RED);
	cout << "Nhan ENTER di!";
	TextColor(tmp);
	while (true) {
		char c = _getch();
		if (c == ENTER)
			SetSound(sound, sound ^ 1);
		if (sound) PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		if (c == ESC)
			return;
	}
}

void VeX1(int color) {
	TextColor(color);
	int x1 = 70;
	int x3 = 85;
	int x2 = 110;
	int y1 = 17;
	int y2 = 25;
	SetConsoleOutputCP(65001);
	GotoXY(x1, y1);
	ifstream Read("VeX1.txt");
	string Art = getFileContents(Read);
	cout << Art << endl;
	Read.close();
	SetConsoleOutputCP(437);
}

void VeX2(int color) {
	TextColor(color);
	int x1 = 70;
	int x3 = 85;
	int x2 = 110;
	int y1 = 17;
	int y2 = 25;
	SetConsoleOutputCP(65001);
	GotoXY(x1, y2);
	ifstream Read("VeX2.txt");
	string Art = getFileContents(Read);
	cout << Art << endl;
	Read.close();
	SetConsoleOutputCP(437);
}

void VeO1(int color) {
	TextColor(color);
	int x1 = 70;
	int x3 = 85;
	int x2 = 110;
	int y1 = 17;
	int y2 = 25;
	SetConsoleOutputCP(65001);
	GotoXY(x1, y2);
	ifstream Read("VeO1.txt");
	string Art = getFileContents(Read);
	cout << Art << endl;
	Read.close();
	SetConsoleOutputCP(437);
}

void VeO2(int color) {
	TextColor(color);
	int x1 = 70;
	int x3 = 85;
	int x2 = 110;
	int y1 = 17;
	int y2 = 25;
	SetConsoleOutputCP(65001);
	GotoXY(x1, y1);
	ifstream Read("VeO2.txt");
	string Art = getFileContents(Read);
	cout << Art << endl;
	Read.close();
	SetConsoleOutputCP(437);
}

void TurnX() {
	/*VeO1(GRAY);
	VeX2(RED);*/
	DrawAsciiFile(0, 20, "VeO1", GRAY);
	DrawAsciiFile(0, 20, "VeX2", RED);
}

void TurnO() {
	/*VeO2(BLUE);
	VeX1(GRAY);*/
	DrawAsciiFile(0, 20, "VeO2", BLUE);
	DrawAsciiFile(0, 20, "VeX1", GRAY);
}

string getFileContents(ifstream& File)
{
	string Lines = "";        //All lines

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			string TempLine;                  //Temp line
			getline(File, TempLine);        //Get temp line
			TempLine += "\n";                      //Add newline character

			Lines += TempLine;                     //Add newline
		}
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}

void DrawAsciiFile(int x, int y,string nameFile, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	GotoXY(x, y);
	ifstream Read(nameFile+".txt");
	string Art = getFileContents(Read);
	cout << Art << endl;
	Read.close();
	SetConsoleOutputCP(437);
}
void DrawClock(int x, int y, int time) {
	for (int i = time; i >= 0; i--) {
		TextColor(BLUE);
		GotoXY(x, y);
		cout << "00:" << i;
		if (i <= 5) {
			TextColor(RED);
			GotoXY(x, y);
			cout << "00:" << i;
		}
		Sleep(1000);
	}
}
void DrawXWin() {
	DrawAsciiFile(0, 20, "DrawXWin01", RED);
	Sleep(150);
	DrawAsciiFile(0, 20, "DrawXWin02", BLUE);
	Sleep(150);
	DrawAsciiFile(0, 20, "DrawXWin01", YELLOW);
	Sleep(150);
	DrawAsciiFile(0, 20, "DrawXWin02", RED);
	Sleep(150);
	DrawAsciiFile(0, 20, "DrawXWin01", BLUE);
	Sleep(150);
	DrawAsciiFile(0, 20, "DrawXWin02", YELLOW);
	Sleep(150);
	DrawAsciiFile(0, 20, "DrawXWin02", X_COLOR);
}
void DrawOWin() {
	DrawAsciiFile(0, 20, "DrawOWin01", RED);
	Sleep(100);
	DrawAsciiFile(0, 20, "DrawOWin02", BLUE);
	Sleep(100);
	DrawAsciiFile(0, 20, "DrawOWin01", YELLOW);
	Sleep(100);
	DrawAsciiFile(0, 20, "DrawOWin02", RED);
	Sleep(100);
	DrawAsciiFile(0, 20, "DrawOWin01", BLUE);
	Sleep(100);
	DrawAsciiFile(0, 20, "DrawOWin02", YELLOW);
	Sleep(100);
	DrawAsciiFile(0, 20, "DrawOWin02", O_COLOR);
}
void SetOWin(string NamePlayer_O, WinningPos WP[5],_POINT _A[B_SIZE][B_SIZE]) {
	for (int i = 0; i < 5; i++) {
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(BLUE);
		Sleep(80);
		cout << "O";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(RED);
		Sleep(80);
		cout << "O";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(GREEN);
		Sleep(80);
		cout << "O";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(O_COLOR & 15 | BACKGROUND_YELLOW);
		Sleep(80);
		cout << "O";
	}
	DrawOWin();
	GotoXY(50, 29);
	cout << "<< PRESS ENTER TO CONTINUE >>";
	int x = 3;
	int y = 2;
	while (true) {
		unsigned char c = _getch();
		if (c == ENTER) {
			SetConsoleBlank();
			Sleep(100);
			ascii_art("congratulation", x, y, RED);
			ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
			Sleep(100);
			ascii_art("congratulation", x, y, GREEN);
			ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
			Sleep(100);
			ascii_art("congratulation", x, y, YELLOW);
			ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
			Sleep(100);
			ascii_art("congratulation", x, y, BLUE);
			ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
			Sleep(100);
			ascii_art("congratulation", x, y, RED);
			ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
			break;
		}
	}
}
void SetXWin(string NamePlayer_X, WinningPos WP[5], _POINT _A[B_SIZE][B_SIZE]) {
	for (int i = 0; i < 5; i++) {
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(BLUE);
		Sleep(80);
		cout << "X";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(RED);
		Sleep(80);
		cout << "X";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(GREEN);
		Sleep(80);
		cout << "X";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(X_COLOR & 15 | BACKGROUND_YELLOW);
		Sleep(80);
		cout << "X";
	}
	DrawXWin();
	GotoXY(50, 29);
	cout << "<< PRESS ENTER TO CONTINUE >>";
	int x = 3;
	int y = 2;
	while (true) {
		unsigned char c = _getch();
		if (c == ENTER) {
			SetConsoleBlank();
			Sleep(100);
			ascii_art("congratulation", x, y, RED);
			ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
			Sleep(100);
			ascii_art("congratulation", x, y, GREEN);
			ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
			Sleep(100);
			ascii_art("congratulation", x, y, YELLOW);
			ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
			Sleep(100);
			ascii_art("congratulation", x, y, BLUE);
			ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
			Sleep(100);
			ascii_art("congratulation", x, y, RED);
			ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
			break;
		}
	}
}