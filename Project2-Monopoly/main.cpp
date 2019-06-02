#include "Game.h"
#include <Windows.h>

int main() {
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //視窗最大化
    setConsole(135, 46, 15);
    setFullScreen();
    Game game("basemap.txt");
    game.runGame();
}