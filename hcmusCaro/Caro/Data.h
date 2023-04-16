#pragma once
#pragma comment(lib, "winmm.lib")

#define BGM TEXT("assets\\sounds\\Wallpaper.wav")
#define CLICK_SFX TEXT("assets\\sounds\\click_sfx.wav")
#define WIN_SFX TEXT("assets\\sounds\\win_sfx.wav")
#define SOUND_PATH string("save\\sound.txt")

// Included libraries
#include <iostream>
#include <cctype>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>

// Namespace
using namespace std;

// Console size
#define WIDTH 120
#define HEIGHT 30

// Board size
#define B_SIZE 12
#define BOARD_X 5
#define BOARD_Y 2

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
#define L_TRIANGLE ((char)16)
#define R_TRIANGLE ((char)17)
// for drawing boxes (menu, etc.)
#define BOX_TOP_LEFT (char)201
#define BOX_TOP_RIGHT (char)187
#define BOX_BOTTOM_LEFT (char)200
#define BOX_BOTTOM_RIGHT (char)188
#define BOX_RIGHT (char)185
#define BOX_LEFT (char)204
#define BOX_V_LINE (char)186
#define BOX_H_LINE (char)205
#define BOX_X  WIDTH / 2 - 20
#define BOX_Y HEIGHT / 2 - 13
#define BOX_W 40
#define BOX_H 20
// moving keys
#define W 87
#define A 65
#define S 83
#define D 68
// others
#define SPACE (char)32
#define key_none -1

// Data types
struct _POINT {
	int x, y, c;
	// x, y: coordinate
	// c -> {0, 1, 2}, 0: vacant, 1: player X, 2: player O
};
struct WinningPos {
	int x, y;
};