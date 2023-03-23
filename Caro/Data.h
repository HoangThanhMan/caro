#pragma once
#pragma comment(lib, "winmm.lib")

#define BGM TEXT("assets\\sounds\\Wallpaper.wav")
#define CLICK_SFX TEXT("assets\\sounds\\click_sfx.wav")
#define WIN_SFX TEXT("assets\\sounds\\win_sfx.wav")

// Included libraries
#include <iostream>
#include <cctype>
#include <Windows.h>
#include <conio.h>

// Namespace
using namespace std;

// Console size
#define WIDTH 120
#define HEIGHT 30

// Board size
#define B_SIZE 12

// Color code
#define BLUE ((15 << 4) | 1)
#define GREEN ((15 << 4) | 2)
#define CYAN ((15 << 4) | 3)
#define RED ((15 << 4) | 4)
#define MAGENTA ((15 << 4) | 5)
#define YELLOW ((15 << 4) | 6)
#define WHITE ((15 << 4) | 7)
#define GRAY ((15 << 4) | 8)
#define LIGHT_BLUE ((15 << 4) | 9)
#define LIGHT_GREEN ((15 << 4) | 10)
#define LIGHT_CYAN ((15 << 4) | 11)
#define LIGHT_RED ((15 << 4) | 12)
#define LIGHT_MAGENTA ((15 << 4) | 13)
#define LIGHT_YELLOW ((15 << 4) | 14)
#define BRIGHT_WHITE ((15 << 4) | 15)
#define X_COLOR RED
#define O_COLOR BLUE
#define BACKGROUND_YELLOW (14 << 4)

// ASCII code
// special key
#define ENTER 13
#define ESC 27
// for drawing the caro table
#define H_LINE (char)196
#define V_LINE (char)179
#define CROSS (char)197
#define TOP_LEFT (char)218
#define TOP_RIGHT (char)191
#define BOTTOM_LEFT (char)192
#define BOTTOM_RIGHT (char)217
#define TOP_CROSS (char)194
#define BOTTOM_CROSS (char)193
#define	LEFT_CROSS (char)195
#define RIGHT_CROSS (char)180
// for drawing boxes (menu, etc.)
#define BOX_TOP_LEFT (char)201
#define BOX_TOP_RIGHT (char)187
#define BOX_BOTTOM_LEFT (char)200
#define BOX_BOTTOM_RIGHT (char)188
#define BOX_V_LINE (char)186
#define BOX_H_LINE (char)205
// moving keys
#define W 87
#define A 65
#define S 83
#define D 68
// others
#define SPACE (char)32

// Data cua Man
#define Color_BLACK      0
#define Color_DarkBlue  1
#define Color_DarkGreen  2
#define Color_DarkCyan  3
#define Color_DarkRed  4
#define Color_DarkPink  5
#define Color_DarkYellow 6
#define Color_DarkWhite  7
#define Color_Grey   8
#define Color_Blue   9
#define Color_Green   10
#define Color_Cyan   11
#define Color_Red   12
#define Color_Pink   13
#define Color_Yellow  14
#define Color_White   15
#define key_Up  1072
#define key_Down 1080
#define key_Left 1075
#define key_Right 1077
#define key_none -1
#define LEFT 1
#define TOP 1

// Data types
struct _POINT {
	int x, y, c;
	// x, y: coordinate
	// p -> {0, 1, 2}, 0: vacant, 1: player X, 2: player O
};