#include "Option.h"
#include "Game.h"

const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;
const int MENU_LEN = 4;
const string menu[] = { "SAVE","LOAD","MUSIC_SET","CLOSE_GAME" };
Option::Option(Game* game, int PlayerID,vector<string> input)
{
	options = input;
	ptr = game;
	if (!options.empty())
	{
		int p = 0;
		int p_menu;
		bool options_flag = true;
		PrintOption(p);
		while (options_flag)
		{
			switch (char keyin = _getch())
			{
			case LEFT:
				p = p > 0 ? p - 1 : p;
				PrintOption(p);
				break;
			case RIGHT:
				p = p < options.size() - 1 ? p + 1 : p;
				PrintOption(p);
				break;
			case ENTER:
				if (input[p] == "THROW_DICE")
				{
					/*"來骰！"的實作*/
					int position = (ptr->players.at(PlayerID).getPosition() + ptr->rollTheDice()) % (ptr->map.getMapSize());
					ptr->players.at(PlayerID).setPosition(position);
					ptr->printUI();
					ptr->is_FinishRound = true;
				}
				options_flag = false;
				break;
			case ESC:
				p_menu = 0;
				bool menu_flag = true;
				while (menu_flag)
				{
					switch (char keyin_menu = _getch())
					{
					case LEFT:
						p_menu = p_menu > 0 ? p_menu - 1 : p_menu;
						PrintMenu(p_menu);
						break;
					case RIGHT:
						p_menu = p_menu < MENU_LEN - 1 ? p_menu + 1 : p_menu;
						PrintMenu(p_menu);
						break;
					case ENTER:
						/*待game補讀取、儲存、音樂調整、離開遊戲的fun()*/
						break;
					case ESC://退回上一選單內容
						menu_flag = false;
						break;
					}
				}
				PrintOption(p);
				break;
			}
		}
	}
}
Option::~Option()
{
}

void Option::PrintOption(int choosen)
{
	position p = getCursorPosition();
	/*待改x才能放置在正確位置*/
	p.x = 0 ;
	SetPosition(p);

	for (int i = 0; i < options.size(); i++)
	{
		if(i== choosen) SetColor(0x70);
		else SetColor();

		cout << options[i];
		SetColor();
		cout << " ";
	}
}

void Option::PrintMenu(int choosen)
{
	/*待補*/
}
