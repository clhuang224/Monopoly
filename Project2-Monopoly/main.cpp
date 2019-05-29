#include "Game.h"
#include <Windows.h>

int main() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //視窗最大化
	Game game("basemap.txt");
	game.runGame();
}