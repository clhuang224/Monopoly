#include "Game.h"
#include <Windows.h>

int main() {
    setConsole(120, 46,15);
    setFullScreen();
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //�����̤j��
	Game game("basemap.txt");
	game.runGame();
}