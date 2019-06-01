#include "Option.h"
#include "Game.h"
#include "Stock.h"
#include "Player.h"
#include "Console.h"

const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;
const int MENU_LEN = 4;
const vector<string> menu = { "儲存遊戲","載入存檔","音樂設定","離開遊戲" };
Option::Option(Game* game,vector<string> input)
{
	options = input;
	ptr = game;
	if (!options.empty())
	{
		int p = 0;
		int p_menu;
		string filename;
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
				if (input[p] == "擲骰子")
				{
					//int position = (ptr->players.at(ptr->run).getPosition() + 1);//固定走一步 用於測試
					int position = (ptr->players.at(ptr->run).getPosition() + ptr->rollTheDice()) % (ptr->map.getMapSize());
					ptr->players.at(ptr->run).setPosition(position);
					ptr->printUI();
					cout << "前進到" << ptr->map.getMap().at(position)->getName() <<" 位置："<< position << "\n";
					system("pause");
					ptr->printUI();
					ptr->is_FinishRound = true;
				}
				if (input[p] == "銀行")
				{
					bool inBank = true;

					position temp = getCursorPosition();
					position nowPos = { 40,17 };
					
					int nowPoint = 0;
					while (inBank)
					{
						SetPosition({40,17}); SetColor(14);
						cout << " /$$$$$$$    /$$$$$$     /$$   /$$   /$$   /$$"; nowPos = { 40,18 }; SetPosition(nowPos);
						cout << "| $$__  $$  / $$__  $$  | $$$  |$$  | $$  /$$"; nowPos = { 40,19 }; SetPosition(nowPos);
						cout << "| $$  \\ $$  | $$   \\$$  | $$$$ |$$  | $$ /$$"; nowPos = { 40,20 };  SetPosition(nowPos);
						cout << "| $$$$$$$   | $$$$$$$$  | $$ $$ $$  | $$$$$"; nowPos = { 40,21 }; SetPosition(nowPos);
						cout << "| $$__  $$  | $$__  $$  | $$  $$$$  | $$  $$"; nowPos = { 40,22 };  SetPosition(nowPos);
						cout << "| $$  \\ $$  | $$  | $$  | $$\\  $$$  | $$\\  $$"; nowPos = { 40,23 };  SetPosition(nowPos);
						cout << "| $$$$$$$/  | $$  | $$  | $$ \\  $$  | $$ \\  $$"; nowPos = { 40,24 };  SetPosition(nowPos);
						cout << "| _______/  |__/  |__/  |__ / \\__/  |__ / \\__/ ";
						SetColor(7); nowPos = { 46,28 }; SetPosition(nowPos);
						cout << "歡迎來到銀行 !!! 需要什麼服務呢 ?";

						nowPos = { 56,30 }; SetPosition(nowPos);
						cout << "存款";
						nowPos = { 64,30 }; SetPosition(nowPos);
						cout << "提款";
						nowPos = { 56,32 }; SetPosition(nowPos);
						cout << "查看今日股票";
						nowPos = { 58,34 }; SetPosition(nowPos);
						cout << "買入股票";
						nowPos = { 58,36 }; SetPosition(nowPos);
						cout << "賣出股票";
						nowPos = { 58,38 }; SetPosition(nowPos);
						cout << "離開銀行";

						switch (nowPoint)
						{
						case 0:
							SetColor(240);
							nowPos = { 56,30 }; SetPosition(nowPos);
							cout << "存款";
							SetColor(7);
							break;
						case 1:
							SetColor(240);
							nowPos = { 64,30 }; SetPosition(nowPos);
							cout << "提款";
							SetColor(7);
							break;
						case 2:
							SetColor(240);
							nowPos = { 56,32 }; SetPosition(nowPos);
							cout << "查看今日股票";
							SetColor(7);
							break;
						case 3:
							SetColor(240);
							nowPos = { 58,34 }; SetPosition(nowPos);
							cout << "買入股票";
							SetColor(7);
							break;
						case 4:
							SetColor(240);
							nowPos = { 58,36 }; SetPosition(nowPos);
							cout << "賣出股票";
							SetColor(7);
							break;
						case 5:
							SetColor(240);
							nowPos = { 58,38 }; SetPosition(nowPos);
							cout << "離開銀行";
							SetColor(7);
							break;
						}

						switch (char keyin = _getch())
						{
						case UP:
							if (nowPoint > 0)
							{
								nowPoint--;
							}
							break;
						case DOWN:
							if (nowPoint < 5)
							{
								nowPoint++;
							}
							break;
						case ENTER:

							switch (nowPoint)
							{
							case 0://存款
								ptr->printUI();
								cout << "您現在有現金" << ptr->players[ptr->run].getCash() << "元，請問要存入多少錢?(最少0元最多總現金)\n";
								{
									int input;
									bool loop_flag = true;
									position tmp = getCursorPosition();
									while (loop_flag)
									{
										setCursorVisable(true);
										cout << "存入：";
										cin >> input;
										setCursorVisable(false);
										if (input >= 0 && input <= ptr->players[ptr->run].getCash())
										{
											cout << "存入成功！！";
											ptr->players[ptr->run].setCash(ptr->players[ptr->run].getCash() - input);
											ptr->players[ptr->run].setDeposit(ptr->players[ptr->run].getDeposit() + input);
											loop_flag = false;
										}
										else
										{
											cout << "存入失敗，請重新輸入，按任意鍵繼續";
											system("pause>nul");
											SetPosition(tmp);
											cout << "                                                                                                                                    \n";
											cout << "                                                                                                                                    \n";
											SetPosition(tmp);
										}
									}
								}
								break;
							// 提款
							case 1:
								ptr->printUI();
								cout << "您現在有存款" << ptr->players[ptr->run].getDeposit() << "元，請問要提出多少錢?(最少0元最多總現金)\n";
								{
									int input;
									bool loop_flag = true;
									position tmp = getCursorPosition();
									while (loop_flag)
									{
										setCursorVisable(true);
										cout << "提出：";
										cin >> input;
										setCursorVisable(false);
										if (input >= 0 && input <= ptr->players[ptr->run].getDeposit())
										{
											cout << "提出成功！！";
											ptr->players[ptr->run].setCash(ptr->players[ptr->run].getCash() + input);
											ptr->players[ptr->run].setDeposit(ptr->players[ptr->run].getDeposit() - input);
											loop_flag = false;
										}
										else
										{
											cout << "提出失敗，請重新輸入，按任意鍵繼續";
											system("pause>nul");
											SetPosition(tmp);
											cout << "                                                                                                                                    \n";
											cout << "                                                                                                                                    \n";
											SetPosition(tmp);
										}
									}
								}
								break;

							// 查看股票
							case 2:
								break;

							// 買入股票
							case 3:
								break;

							// 賣出股票
							case 4:
								break;

							// 離開銀行
							case 5:
								inBank = false;
								break;
							}
							break;
						case ESC:
							inBank = false;
							break;
						}
					}

					for (int i = 17; i < 40; i++)
					{
						nowPos = { 40, i }; SetPosition(nowPos);
						cout << "                                               ";
					}
					ptr->clearNotationUI();
					SetPosition(temp);
				}
				if (input[p] == "升級")
				{
					House* house = (House*)ptr->map.getMap().at(ptr->players.at(ptr->run).getPosition());
					house->setLevel((house->getLevel()) + 1);
					cout << "\n恭喜升級成功                          \n";
					system("pause");
				}
				if (input[p] == "購買此空地")
				{
					/*"買空屋"的實作*/
					/*待補游標位置設定*/
					ptr->players.at(ptr->run).buyHouse((House*)ptr->map.getMap().at(ptr->players.at(ptr->run).getPosition()));
					ptr->printUI();
					cout << "\n恭喜購買成功                          \n";
					system("pause");
					cout << "                                                   ";
					ptr->printUI();
				}
				options_flag = false;//停止選擇Option的內容
				break;
			case ESC:
				p_menu = 0;
				bool menu_flag = true;
				PrintMenu(0);
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
						/*待補音樂調整的fun()*/
						switch (p_menu)
						{
						case 0:
							cin >> filename;
							ptr->save(filename);
							break;
						case 1:
							cin >> ptr->newGameName;
							ptr->restartFlag = true;
							ptr->is_FinishRound = false;
							menu_flag = false;
							options_flag = false;
							break;
						case 2:
							/*待補音樂設定*/
							break;
						case 3:
							exit(0);
						}
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
	/*待改x才能放置在正確位置，待補選項列上清除目前已印出的字*/
	p.x = 0 ;
	SetPosition(p);
	cout << "                                    \n                                    ";
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
	position p = getCursorPosition();
	/*待改x才能放置在正確位置，待補選項列上清除目前已印出的字*/
	p.x = 0;
	SetPosition(p);
	cout << "                                    \n                                    ";
	SetPosition(p);
	for (int i = 0; i < menu.size(); i++)
	{
		if (i == choosen) SetColor(0x70);
		else SetColor();

		cout << menu[i];
		SetColor();
		cout << " ";
	}
}
