#include <Windows.h>
#include "Game.h"
#include "Begin.h"

int main() {
    setConsole(133, 46, 13);
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