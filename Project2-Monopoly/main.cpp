#include "Game.h"
#include <Windows.h>
#include "Begin.h"

int main() {
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //視窗最大化
    setConsole(135, 46, 15);
    setCursorVisable(false);

	Begin beginning;
	beginning.start();
	/*if (beginning.getPlayerNumber() == 20)
	{
		Game game("basemap.txt");
	}*/

	Game game("basemap.txt");
    game.runGame();
}