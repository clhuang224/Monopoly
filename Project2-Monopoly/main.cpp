#include "Game.h"
#include <Windows.h>

int main() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //�����̤j��
	Game game("basemap.txt");
	game.runGame();
}