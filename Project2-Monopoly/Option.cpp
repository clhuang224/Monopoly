#include "Option.h"
#include "Game.h"
#include "Player.h"
#include "Console.h"
#include <string>

const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;
const int MENU_LEN = 4;
const vector<string> menu = { "�x�s�C��","���J�s��","���ֳ]�w","���}�C��" };
Option::Option(Game* game, vector<string> input)
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
				if (input[p] == "�Y��l")
				{
					//int position = (ptr->players.at(ptr->run).getPosition() + 1);//�T�w���@�B �Ω����
					int position = (ptr->players.at(ptr->run).getPosition() + ptr->rollTheDice()) % (ptr->map.getMapSize());
					ptr->players.at(ptr->run).setPosition(position);
					ptr->printUI();
					cout << "�e�i��" << ptr->map.getMap().at(position)->getName() << " ��m�G" << position << "\n";
					system("pause");
					ptr->printUI();
					ptr->is_FinishRound = true;
				}
				if (input[p] == "�Ȧ�")
				{
					/*"�Ȧ�"����@*/
					bool inBank = true;

					position temp = getCursorPosition();
					position nowPos = { 30,11 }; SetPosition(nowPos); SetColor(14);
					cout << " /$$$$$$$    /$$$$$$     /$$   /$$   /$$   /$$"; nowPos = { 30,12 }; SetPosition(nowPos);
					cout << "| $$__  $$  / $$__  $$  | $$$  |$$  | $$  /$$"; nowPos = { 30,13 }; SetPosition(nowPos);
					cout << "| $$  \\ $$  | $$   \\$$  | $$$$ |$$  | $$ /$$"; nowPos = { 30,14 };  SetPosition(nowPos);
					cout << "| $$$$$$$   | $$$$$$$$  | $$ $$ $$  | $$$$$"; nowPos = { 30,15 }; SetPosition(nowPos);
					cout << "| $$__  $$  | $$__  $$  | $$  $$$$  | $$  $$"; nowPos = { 30,16 };  SetPosition(nowPos);
					cout << "| $$  \\ $$  | $$  | $$  | $$\\  $$$  | $$\\  $$"; nowPos = { 30,17 };  SetPosition(nowPos);
					cout << "| $$$$$$$/  | $$  | $$  | $$ \\  $$  | $$ \\  $$"; nowPos = { 30,18 };  SetPosition(nowPos);
					cout << "| _______/  |__/  |__/  |__ / \\__/  |__ / \\__/ ";

					int nowPoint = 0;
					int nowBuy = 0;
					bool buying;
					while (inBank)
					{
						SetColor(7); nowPos = { 38,20 }; SetPosition(nowPos);
						cout << "�w��Ө�Ȧ� !!! �ݭn����A�ȩO ?";

						int deposit = ptr->players[ptr->run].getDeposit();
						int cash = ptr->players[ptr->run].getCash();

						nowPos = { 46,22 }; SetPosition(nowPos);
						cout << "�s��";
						nowPos = { 54,22 }; SetPosition(nowPos);
						cout << "����";
						nowPos = { 46,24 }; SetPosition(nowPos);
						cout << "�ɴ�";
						nowPos = { 54,24 }; SetPosition(nowPos);
						cout << "�ٿ�";
						nowPos = { 46,26 }; SetPosition(nowPos);
						cout << "�d�ݤ���Ѳ�";
						nowPos = { 48,28 }; SetPosition(nowPos);
						cout << "�R�J�Ѳ�";
						nowPos = { 48,30 }; SetPosition(nowPos);
						cout << "��X�Ѳ�";
						nowPos = { 48,32 }; SetPosition(nowPos);
						cout << "���}�Ȧ�";

						switch (nowPoint)
						{
						case 0:
							SetColor(240);
							nowPos = { 46,22 }; SetPosition(nowPos);
							cout << "�s��";
							SetColor(7);
							break;
						case 1:
							SetColor(240);
							nowPos = { 54,22 }; SetPosition(nowPos);
							cout << "����";
							SetColor(7);
							break;
						case 2:
							SetColor(240);
							nowPos = { 46,24 }; SetPosition(nowPos);
							cout << "�ɴ�";
							SetColor(7);
							break;
						case 3:
							SetColor(240);
							nowPos = { 54,24 }; SetPosition(nowPos);
							cout << "�ٿ�";
							SetColor(7);
							break;
						case 4:
							SetColor(240);
							nowPos = { 46,26 }; SetPosition(nowPos);
							cout << "�d�ݤ���Ѳ�";
							SetColor(7);
							break;
						case 5:
							SetColor(240);
							nowPos = { 48,28 }; SetPosition(nowPos);
							cout << "�R�J�Ѳ�";
							SetColor(7);
							break;
						case 6:
							SetColor(240);
							nowPos = { 48,30 }; SetPosition(nowPos);
							cout << "��X�Ѳ�";
							SetColor(7);
							break;
						case 7:
							SetColor(240);
							nowPos = { 48,32 }; SetPosition(nowPos);
							cout << "���}�Ȧ�";
							SetColor(7);
							break;
						}


						switch (char keyin = _getch())
						{
						case DOWN:
							if (nowPoint < 7)
							{
								nowPoint++;
							}
							break;
						case UP:
							if (nowPoint > 0)
							{
								nowPoint--;
							}
							break;
						case ENTER:
							string temp;
							long int amount;
							switch (nowPoint)
							{
							// �s��
							case 0:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									nowPos = { 38, i }; SetPosition(nowPos);
									cout << "                                               ";
								}

								nowPos = { 43,22 }; SetPosition(nowPos);
								cout << "�z�����Y�{�b�� $ " << ptr->players[ptr->run].getDeposit();
								nowPos = { 43,24 }; SetPosition(nowPos);
								cout << "�z��e���{�� $ " << ptr->players[ptr->run].getCash();

								nowPos = { 43,26 }; SetPosition(nowPos);
								cout << "�z�Q�n�s�h�ֿ��O ?";

								nowPos = { 43,28 }; SetPosition(nowPos);
								SetColor(240);
								cout << "                 ";
								nowPos = { 43,28 }; SetPosition(nowPos);
								getline(cin, temp);
								if (temp != "")
								{
									amount = stoi(temp);
									if (amount > cash)
									{
										SetColor(12);
										nowPos = { 42,28 }; SetPosition(nowPos);
										cout << "�{�������A�w�����s��";

									}
									else
									{
										ptr->players[ptr->run].plusDeposit(amount);
										ptr->players[ptr->run].minusCash(amount);
										SetColor(12);
										nowPos = { 43,28 }; SetPosition(nowPos);
										cout << "                              ";
										nowPos = { 46,28 }; SetPosition(nowPos);
										cout << "�s�������\ !";
									}
									SetColor(240);
									nowPos = { 50,30 }; SetPosition(nowPos);
									cout << "�T�{";
									game->printPlayer();

									getchar();
								}
								else
								{
									SetColor(12);
									nowPos = { 37,28 }; SetPosition(nowPos);
									cout << "�z�S����J������B�A�w�����s��";

									SetColor(240);
									nowPos = { 50,30 }; SetPosition(nowPos);
									cout << "�T�{";
									getchar();
								}

								SetColor(7);
								for (int i = 20; i < 32; i++)
								{
									nowPos = { 35, i }; SetPosition(nowPos);
									cout << "                                                ";
								}

								break;
							// ����
							case 1:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									nowPos = { 38, i }; SetPosition(nowPos);
									cout << "                                               ";
								}

								nowPos = { 43,22 }; SetPosition(nowPos);
								cout << "�z�����Y�{�b�� $ " << ptr->players[ptr->run].getDeposit();
								nowPos = { 43,24 }; SetPosition(nowPos);
								cout << "�z��e���{�� $ " << ptr->players[ptr->run].getCash();

								nowPos = { 43,26 }; SetPosition(nowPos);
								cout << "�z�Q�n��h�ֿ��O ?";

								nowPos = { 43,28 }; SetPosition(nowPos);
								SetColor(240);
								cout << "                 ";
								nowPos = { 43,28 }; SetPosition(nowPos);
								getline(cin, temp);
								if (temp != "")
								{
									amount = stoi(temp);
									if (amount > deposit)
									{
										SetColor(12);
										nowPos = { 42,28 }; SetPosition(nowPos);
										cout << "�s�ڤ����A�w��������";

									}
									else
									{
										ptr->players[ptr->run].minusDeposit(amount);
										ptr->players[ptr->run].plusCash(amount);
										SetColor(12);
										nowPos = { 43,28 }; SetPosition(nowPos);
										cout << "                              ";
										nowPos = { 46,28 }; SetPosition(nowPos);
										cout << "���������\ !";
									}
									SetColor(240);
									nowPos = { 50,30 }; SetPosition(nowPos);
									cout << "�T�{";
									game->printPlayer();

									getchar();
								}
								else
								{
									SetColor(12);
									nowPos = { 37,28 }; SetPosition(nowPos);
									cout << "�z�S����J������B�A�w��������";

									SetColor(240);
									nowPos = { 50,30 }; SetPosition(nowPos);
									cout << "�T�{";
									getchar();
								}

								SetColor(7);
								for (int i = 20; i < 32; i++)
								{
									nowPos = { 35, i }; SetPosition(nowPos);
									cout << "                                                ";
								}
								break;
							// �ɴ�
							case 2:

								break;
							// �ٿ�
							case 3:

								break;
							// �d�ݪѲ�
							case 4:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									nowPos = { 38, i }; SetPosition(nowPos);
									cout << "                                               ";
								}

								nowPos = { 60, 20 }; SetPosition(nowPos);
								cout << "����Ѳ�����";
								for (int i = 0; i < game->stock.getStockList().size(); i++)
								{
									nowPos = { 60, 22 + i * 2 }; SetPosition(nowPos);
									cout << game->stock.getStockList()[i].name << " : $ " << game->stock.getStockList()[i].value;
								}

								nowPos = { 34, 20 }; SetPosition(nowPos);
								cout << "�z�������Ѳ�";
								amount = 0;
								for (int i = 0; i < 5; i++)
								{
									if (ptr->players[ptr->run].getOwnStock()[i] > 0)
									{
										nowPos = { 35, 22 + amount * 2 }; SetPosition(nowPos);
										cout << game->stock.getStockList()[i].name << " * " << ptr->players[ptr->run].getOwnStock()[i];
										amount++;
									}
								}
								if (amount == 0)
								{
									nowPos = { 32, 22 }; SetPosition(nowPos);
									cout << "�z�ثe�èS�������Ѳ�";
								}
								SetColor(240);
								nowPos = { 50,32 }; SetPosition(nowPos);
								cout << "�T�{";
								getchar();

								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									nowPos = { 28, i }; SetPosition(nowPos);
									cout << "                                                       ";
								}

								break;

							// �R�J�Ѳ�
							case 5:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									nowPos = { 38, i }; SetPosition(nowPos);
									cout << "                                               ";
								}

								buying = true;
								nowBuy = 0;
								while (buying)
								{
									nowPos = { 43, 20 }; SetPosition(nowPos);
									cout << "�z�����Y���� $ " << ptr->players[ptr->run].getDeposit();

									for (int i = 0; i < game->stock.getStockList().size(); i++)
									{
										nowPos = { 46, 22 + i * 2 }; SetPosition(nowPos);
										cout << game->stock.getStockList()[i].name << " : $ " << game->stock.getStockList()[i].value;
									}
									nowPos = { 50, 32 }; SetPosition(nowPos);
									cout << "���}";

									SetColor(240);
									if (nowBuy < 5)
									{
										nowPos = { 46, 22 + nowBuy * 2 }; SetPosition(nowPos);
										cout << game->stock.getStockList()[nowBuy].name << " : $ " << game->stock.getStockList()[nowBuy].value;
									}
									else if (nowBuy == 5)
									{
										nowPos = { 50, 32 }; SetPosition(nowPos);
										cout << "���}";
									}
									SetColor(7);

									switch (char keyin = _getch())
									{
									case DOWN:
										if (nowBuy < 5)
										{
											nowBuy++;
										}
										break;
									case UP:
										if (nowBuy > 0)
										{
											nowBuy--;
										}
										break;
									case ENTER:

										if (nowBuy == 5)
										{
											buying = false;
										}
										else
										{
											for (int i = 20; i < 34; i++)
											{
												nowPos = { 38, i }; SetPosition(nowPos);
												cout << "                                               ";
											}
											if (ptr->players[ptr->run].getDeposit() >= game->stock.getStockList()[nowBuy].value)
											{
												ptr->players[ptr->run].buyStock(nowBuy, game->stock.getStockList()[nowBuy]);

												SetColor(12);
												nowPos = { 44, 25 }; SetPosition(nowPos);
												cout << "�ʶR "<< game->stock.getStockList()[nowBuy].name << " ���\";
												
											}
											else
											{
												SetColor(12);
												nowPos = { 46, 25 }; SetPosition(nowPos);
												cout << "�z���s�ڤ���";
											}
											SetColor(240);
											nowPos = { 50,28 }; SetPosition(nowPos);
											cout << "�T�{";
											SetColor(7);
											getchar();

											for (int i = 20; i < 34; i++)
											{
												nowPos = { 38, i }; SetPosition(nowPos);
												cout << "                                               ";
											}

										}
										break;
									}

								}

								for (int i = 20; i < 34; i++)
								{
									nowPos = { 28, i }; SetPosition(nowPos);
									cout << "                                                       ";
								}

								break;

							// ��X�Ѳ�
							case 6:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									nowPos = { 38, i }; SetPosition(nowPos);
									cout << "                                               ";
								}

								buying = true;
								nowBuy = 0;
								while (buying)
								{
									nowPos = { 43, 20 }; SetPosition(nowPos);
									cout << "�z�����Y���� $ " << ptr->players[ptr->run].getDeposit();

									for (int i = 0; i < game->stock.getStockList().size(); i++)
									{
										nowPos = { 46, 22 + i * 2 }; SetPosition(nowPos);
										cout << game->stock.getStockList()[i].name << " * " << ptr->players[ptr->run].getOwnStock()[i];
									}
									nowPos = { 50, 32 }; SetPosition(nowPos);
									cout << "���}";


									SetColor(240);
									if (nowBuy < 5)
									{
										nowPos = { 46, 22 + nowBuy * 2 }; SetPosition(nowPos);
										cout << game->stock.getStockList()[nowBuy].name << " * " << ptr->players[ptr->run].getOwnStock()[nowBuy];
									}
									else if (nowBuy == 5)
									{
										nowPos = { 50, 32 }; SetPosition(nowPos);
										cout << "���}";
									}
									SetColor(7);

									switch (char keyin = _getch())
									{
									case DOWN:
										if (nowBuy < 5)
										{
											nowBuy++;
										}
										break;
									case UP:
										if (nowBuy > 0)
										{
											nowBuy--;
										}
										break;
									case ENTER:

										if (nowBuy == 5)
										{
											buying = false;
										}
										else
										{
											for (int i = 20; i < 34; i++)
											{
												nowPos = { 38, i }; SetPosition(nowPos);
												cout << "                                               ";
											}
											if (ptr->players[ptr->run].getOwnStock()[nowBuy] > 0)
											{
												ptr->players[ptr->run].sellStock(nowBuy, game->stock.getStockList()[nowBuy]);
												SetColor(12);
												nowPos = { 44, 25 }; SetPosition(nowPos);
												cout << "��X " << game->stock.getStockList()[nowBuy].name << " ���\";
											}
											else
											{
												SetColor(12);
												nowPos = { 43, 25 }; SetPosition(nowPos);
												cout << "�z�ثe�S���o��Ѳ��i��";
											}
											SetColor(240);
											nowPos = { 50,28 }; SetPosition(nowPos);
											cout << "�T�{";
											SetColor(7);
											getchar();

											for (int i = 20; i < 34; i++)
											{
												nowPos = { 38, i }; SetPosition(nowPos);
												cout << "                                               ";
											}
										}
										break;
									}

								}

								for (int i = 20; i < 34; i++)
								{
									nowPos = { 28, i }; SetPosition(nowPos);
									cout << "                                                       ";
								}
								break;

							// ���}�Ȧ�
							case 7:
								inBank = false;
								break;
							}
							break;
						}
					}

					for (int i = 10; i < 33; i++)
					{
						nowPos = { 30, i }; SetPosition(nowPos);
						cout << "                                                ";
					}
					SetPosition(temp);
				}

				if (input[p] == "�ɯ�")
				{
					House* house = (House*)ptr->map.getMap().at(ptr->players.at(ptr->run).getPosition());
					house->setLevel((house->getLevel()) + 1);
					cout << "\n���ߤɯŦ��\                          \n";
					system("pause");
				}
				if (input[p] == "�ʶR���Ŧa")
				{
					/*"�R�ū�"����@*/
					/*�ݸɴ�Ц�m�]�w*/
					ptr->players.at(ptr->run).buyHouse((House*)ptr->map.getMap().at(ptr->players.at(ptr->run).getPosition()));
					ptr->printUI();
					cout << "\n�����ʶR���\                          \n";
					system("pause");
					cout << "                                                   ";
					ptr->printUI();
				}
				options_flag = false;//������Option�����e
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
						/*�ݸɭ��ֽվ㪺fun()*/
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
							/*�ݸɭ��ֳ]�w*/
							break;
						case 3:
							exit(0);
						}
						break;
					case ESC://�h�^�W�@��椺�e
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
	/*�ݧ�x�~���m�b���T��m�A�ݸɿﶵ�C�W�M���ثe�w�L�X���r*/
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
	/*�ݧ�x�~���m�b���T��m�A�ݸɿﶵ�C�W�M���ثe�w�L�X���r*/
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
