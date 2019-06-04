#include "Begin.h"
#include <iostream>
#include "Console.h"
#include <time.h>
#include <cstdlib>
#include <thread>

using namespace std;

Begin::Begin()
{
}


Begin::~Begin()
{
}

void Begin::dancing()
{
	srand((unsigned)time(NULL));
	
	while (1)
	{
		int a = rand() % 15 + 1;
		int b = rand() % 15 + 1;
		int c = rand() % 15 + 1;
		int d = rand() % 15 + 1;
		int e = rand() % 15 + 1;
		int f = rand() % 15 + 1;
		int g = rand() % 15 + 1;
		int h = rand() % 15 + 1;

		SetPosition({ 0,0 });
		SetColor(a);
		cout << "          _____       "; SetColor(b); cout << "            _______         "; SetColor(c); cout << "          _____             "; SetColor(d); cout << "      _______         " << endl; SetColor(a);
		cout << "         /\\    \\    "; SetColor(b); cout << "             /::\\    \\    "; SetColor(c); cout << "             /\\    \\      "; SetColor(d); cout << "           /::\\    \\        " << endl; SetColor(a);
		cout << "        /::\\____\\   "; SetColor(b); cout << "            /::::\\    \\    "; SetColor(c); cout << "           /::\\____\\     "; SetColor(d); cout << "          /::::\\    \\       " << endl; SetColor(a);
		cout << "       /::::|   |     "; SetColor(b); cout << "         /::::::\\    \\     "; SetColor(c); cout << "        /::::|   |         "; SetColor(d); cout << "     /::::::\\    \\      " << endl; SetColor(a);
		cout << "      /:::::|   |     "; SetColor(b); cout << "        /::::::::\\    \\     "; SetColor(c); cout << "      /:::::|   |         "; SetColor(d); cout << "    /::::::::\\    \\     " << endl; SetColor(a);
		cout << "     /::::::|   |     "; SetColor(b); cout << "       /:::/~~\\:::\\    \\   "; SetColor(c); cout << "      /::::::|   |        "; SetColor(d); cout << "    /:::/~~\\:::\\    \\    " << endl; SetColor(a);
		cout << "    /:::/|::|   |     "; SetColor(b); cout << "      /:::/    \\:::\\    \\  "; SetColor(c); cout << "     /:::/|::|   |        "; SetColor(d); cout << "   /:::/    \\:::\\    \\   " << endl; SetColor(a);
		cout << "   /:::/ |::|   |     "; SetColor(b); cout << "     /:::/    / \\:::\\    \\ "; SetColor(c); cout << "    /:::/ |::|   |        "; SetColor(d); cout << "  /:::/    / \\:::\\    \\  " << endl; SetColor(a);
		cout << "  /:::/  |::|___|______ "; SetColor(b); cout << "  /:::/____/   \\:::\\____\\"; SetColor(c); cout << "   /:::/  |::|   | _____  "; SetColor(d); cout << " /:::/____/   \\:::\\____\\ " << endl; SetColor(a);
		cout << " /:::/   |::::::::\\    \\"; SetColor(b); cout << " |:::|    |     |:::|    | "; SetColor(c); cout << "/:::/   |::|   |/\\    \\"; SetColor(d); cout << " |:::|    |     |:::|    |" << endl; SetColor(a);
		cout << "/:::/    |:::::::::\\____\\"; SetColor(b); cout << "|:::|____|     |:::|    |"; SetColor(c); cout << "/:: /    |::|   /::\\____\\"; SetColor(d); cout << "|:::|____|     |:::|    |" << endl; SetColor(a);
		cout << "\\::/    / ~~~~~/:::/    / "; SetColor(b); cout << "\\:::\\    \\   /:::/    / "; SetColor(c); cout << "\\::/    /|::|  /:::/    / "; SetColor(d); cout << "\\:::\\    \\   /:::/    / " << endl; SetColor(a);
		cout << " \\/____/      /:::/    /  "; SetColor(b); cout << " \\:::\\    \\ /:::/    / "; SetColor(c); cout << "  \\/____/ |::| /:::/    / "; SetColor(d); cout << "  \\:::\\    \\ /:::/    /  " << endl; SetColor(a);
		cout << "             /:::/    /    "; SetColor(b); cout << " \\:::\\    /:::/    /   "; SetColor(c); cout << "         |::|/:::/    /    "; SetColor(d); cout << " \\:::\\    /:::/    /   " << endl; SetColor(a);
		cout << "            /:::/    /     "; SetColor(b); cout << "  \\:::\\__/:::/    /   "; SetColor(c); cout << "          |::::::/    /   "; SetColor(d); cout << "    \\:::\\__/:::/    /    " << endl; SetColor(a);
		cout << "           /:::/    /      "; SetColor(b); cout << "   \\::::::::/    /    "; SetColor(c); cout << "          |:::::/    /    "; SetColor(d); cout << "     \\::::::::/    /     " << endl; SetColor(a);
		cout << "          /:::/    /       "; SetColor(b); cout << "    \\::::::/    /     "; SetColor(c); cout << "          |::::/    /     "; SetColor(d); cout << "      \\::::::/    /      " << endl; SetColor(a);
		cout << "         /:::/    /        "; SetColor(b); cout << "     \\::::/    /      "; SetColor(c); cout << "          /:::/    /      "; SetColor(d); cout << "       \\::::/    /       " << endl; SetColor(a);
		cout << "        /:::/    /          "; SetColor(b); cout << "     \\::/____/       "; SetColor(c); cout << "         /:::/    /       "; SetColor(d); cout << "        \\::/____/        " << endl; SetColor(a);
		cout << "        \\::/    /          "; SetColor(b); cout << "       ~~             "; SetColor(c); cout << "         \\::/    /      "; SetColor(d); cout << "           ~~              " << endl; SetColor(a);
		cout << "         \\/____/           "; SetColor(b); cout << "                      "; SetColor(c); cout << "          \\/____/        "; SetColor(d); cout << "                          " << endl; 





		SetColor(e);
		cout << "                                                   _____          "; SetColor(f); cout << "         _______            "; SetColor(g); cout << "       _____        "; SetColor(h); cout << "_____          " << endl; SetColor(e);
		cout << "                                                  /\\    \\       "; SetColor(f); cout << "          /::\\    \\       "; SetColor(g); cout << "          /\\    \\  "; SetColor(h); cout << "    |\\    \\         " << endl; SetColor(e);
		cout << "                                                 /::\\    \\      "; SetColor(f); cout << "         /::::\\    \\      "; SetColor(g); cout << "         /::\\____\\ "; SetColor(h); cout << "    |:\\____\\        " << endl; SetColor(e);
		cout << "                                                /::::\\    \\     "; SetColor(f); cout << "        /::::::\\    \\      "; SetColor(g); cout << "       /:::/    /  "; SetColor(h); cout << "   |::|   |        " << endl; SetColor(e);
		cout << "                                               /::::::\\    \\    "; SetColor(f); cout << "       /::::::::\\    \\     "; SetColor(g); cout << "      /:::/    /  "; SetColor(h); cout << "    |::|   |        " << endl; SetColor(e);
		cout << "                                              /:::/\\:::\\    \\    "; SetColor(f); cout << "     /:::/~~\\:::\\    \\   "; SetColor(g); cout << "      /:::/    /  "; SetColor(h); cout << "     |::|   |        " << endl; SetColor(e);
		cout << "                                             /:::/__\\:::\\    \\    "; SetColor(f); cout << "   /:::/    \\:::\\    \\   "; SetColor(g); cout << "    /:::/    /  "; SetColor(h); cout << "      |::|   |        " << endl; SetColor(e);
		cout << "                                            /::::\\   \\:::\\    \\  "; SetColor(f); cout << "   /:::/    / \\:::\\    \\ "; SetColor(g); cout << "    /:::/    /  "; SetColor(h); cout << "       |::|   |        " << endl; SetColor(e);
		cout << "                                           /::::::\\   \\:::\\    \\  "; SetColor(f); cout << " /:::/____/   \\:::\\____\\ "; SetColor(g); cout << "  /:::/    /  "; SetColor(h); cout << "        |::|___|______  " << endl; SetColor(e);
		cout << "                                          /:::/\\:::\\   \\:::\\____\\ "; SetColor(f); cout << "|:::|    |     |:::|    | "; SetColor(g); cout << "/:::/    /     "; SetColor(h); cout << "      /::::::::\\    \\ " << endl; SetColor(e);
		cout << "                                         /:::/  \\:::\\   \\:::|    |"; SetColor(f); cout << "|:::|____|     |:::|    |"; SetColor(g); cout << "/:::/____/        "; SetColor(h); cout << "   /::::::::::\\____\\ " << endl; SetColor(e);
		cout << "                                         \\::/    \\:::\\  /:::|____|"; SetColor(f); cout << " \\:::\\    \\   /:::/    /"; SetColor(g); cout << " \\:::\\    \\   "; SetColor(h); cout << "       /:::/~~~~/~~       " << endl; SetColor(e);
		cout << "                                          \\/_____/\\:::\\/:::/    / "; SetColor(f); cout << "  \\:::\\    \\ /:::/    / "; SetColor(g); cout << "  \\:::\\    \\  "; SetColor(h); cout << "      /:::/    /          " << endl; SetColor(e);
		cout << "                                                   \\::::::/    /    "; SetColor(f); cout << " \\:::\\    /:::/    /   "; SetColor(g); cout << "  \\:::\\    \\    "; SetColor(h); cout << "  /:::/    /           " << endl; SetColor(e);
		cout << "                                                    \\::::/    /     "; SetColor(f); cout << "  \\:::\\__/:::/    /    "; SetColor(g); cout << "   \\:::\\    \\  "; SetColor(h); cout << "  /:::/    /            " << endl; SetColor(e);
		cout << "                                                     \\::/____/       "; SetColor(f); cout << "  \\::::::::/    /      "; SetColor(g); cout << "   \\:::\\    \\  "; SetColor(h); cout << " \\::/    /             " << endl; SetColor(e);
		cout << "                                                      ~~              "; SetColor(f); cout << "  \\::::::/    /        "; SetColor(g); cout << "   \\:::\\    \\  "; SetColor(h); cout << " \\/____/              " << endl; SetColor(e);
		cout << "                                                                       "; SetColor(f); cout << "  \\::::/    /         "; SetColor(g); cout << "    \\:::\\    \\  "; SetColor(h); cout << "                     " << endl; SetColor(e);
		cout << "                                                                       "; SetColor(f); cout << "   \\::/____/          "; SetColor(g); cout << "     \\:::\\____\\"; SetColor(h); cout << "                      " << endl; SetColor(e);
		cout << "                                                                       "; SetColor(f); cout << "    ~~                 "; SetColor(g); cout << "     \\::/    /   "; SetColor(h); cout << "                   " << endl; SetColor(e);
		cout << "                                                                        "; SetColor(f); cout << "                      "; SetColor(g); cout << "      \\/____/    "; SetColor(h); cout << "                  " << endl; SetColor(e);
		
		Sleep(1000);
	}
}

void Begin::start()
{
	//thread mThread(&dancing());
	//mThread.join();
	//getchar();
	//mThread.detach();

}
