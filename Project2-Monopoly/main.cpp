#include "Game.h"
#include <Windows.h>

int main() {
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //�����̤j��
    setConsole(135, 46, 15);
    setFullScreen();
    setCursorVisable(false);
    Game game("basemap.txt");
    game.runGame();
}