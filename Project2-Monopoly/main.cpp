#include "Game.h"
#include <Windows.h>
#include "Begin.h"

int main() {
    setConsole(135, 46, 13.5);
    setCursorVisable(false);

	/*Begin beginning;
	beginning.start();
	if (beginning.getPlayerNumber() == 20)
	{
		Game game("basemap.txt");
	}*/

	Game game("basemap.txt");
    game.runGame();
}