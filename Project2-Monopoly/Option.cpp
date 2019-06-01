#include "Option.h"
#include "Game.h"
#include "Stock.h"
#include "Player.h"
#include "Console.h"

const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;
const int MENU_LEN = 4;
const vector<string> menu = { "�x�s�C��","���J�s��","���ֳ]�w","���}�C��" };
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
				if (input[p] == "�Y��l")
				{
					//int position = (ptr->players.at(ptr->run).getPosition() + 1);//�T�w���@�B �Ω����
					int position = (ptr->players.at(ptr->run).getPosition() + ptr->rollTheDice()) % (ptr->map.getMapSize());
					ptr->players.at(ptr->run).setPosition(position);
					ptr->printUI();
					cout << "�e�i��" << ptr->map.getMap().at(position)->getName() <<" ��m�G"<< position << "\n";
					system("pause");
					ptr->printUI();
					ptr->is_FinishRound = true;
				}
				if (input[p] == "�Ȧ�")
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
						cout << "�w��Ө�Ȧ� !!! �ݭn����A�ȩO ?";

						nowPos = { 56,30 }; SetPosition(nowPos);
						cout << "�s��";
						nowPos = { 64,30 }; SetPosition(nowPos);
						cout << "����";
						nowPos = { 56,32 }; SetPosition(nowPos);
						cout << "�d�ݤ���Ѳ�";
						nowPos = { 58,34 }; SetPosition(nowPos);
						cout << "�R�J�Ѳ�";
						nowPos = { 58,36 }; SetPosition(nowPos);
						cout << "��X�Ѳ�";
						nowPos = { 58,38 }; SetPosition(nowPos);
						cout << "���}�Ȧ�";

						switch (nowPoint)
						{
						case 0:
							SetColor(240);
							nowPos = { 56,30 }; SetPosition(nowPos);
							cout << "�s��";
							SetColor(7);
							break;
						case 1:
							SetColor(240);
							nowPos = { 64,30 }; SetPosition(nowPos);
							cout << "����";
							SetColor(7);
							break;
						case 2:
							SetColor(240);
							nowPos = { 56,32 }; SetPosition(nowPos);
							cout << "�d�ݤ���Ѳ�";
							SetColor(7);
							break;
						case 3:
							SetColor(240);
							nowPos = { 58,34 }; SetPosition(nowPos);
							cout << "�R�J�Ѳ�";
							SetColor(7);
							break;
						case 4:
							SetColor(240);
							nowPos = { 58,36 }; SetPosition(nowPos);
							cout << "��X�Ѳ�";
							SetColor(7);
							break;
						case 5:
							SetColor(240);
							nowPos = { 58,38 }; SetPosition(nowPos);
							cout << "���}�Ȧ�";
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
							case 0://�s��
								ptr->printUI();
								cout << "�z�{�b���{��" << ptr->players[ptr->run].getCash() << "���A�аݭn�s�J�h�ֿ�?(�̤�0���̦h�`�{��)\n";
								{
									int input;
									bool loop_flag = true;
									position tmp = getCursorPosition();
									while (loop_flag)
									{
										setCursorVisable(true);
										cout << "�s�J�G";
										cin >> input;
										setCursorVisable(false);
										if (input >= 0 && input <= ptr->players[ptr->run].getCash())
										{
											cout << "�s�J���\�I�I";
											ptr->players[ptr->run].setCash(ptr->players[ptr->run].getCash() - input);
											ptr->players[ptr->run].setDeposit(ptr->players[ptr->run].getDeposit() + input);
											loop_flag = false;
										}
										else
										{
											cout << "�s�J���ѡA�Э��s��J�A�����N���~��";
											system("pause>nul");
											SetPosition(tmp);
											cout << "                                                                                                                                    \n";
											cout << "                                                                                                                                    \n";
											SetPosition(tmp);
										}
									}
								}
								break;
							// ����
							case 1:
								ptr->printUI();
								cout << "�z�{�b���s��" << ptr->players[ptr->run].getDeposit() << "���A�аݭn���X�h�ֿ�?(�̤�0���̦h�`�{��)\n";
								{
									int input;
									bool loop_flag = true;
									position tmp = getCursorPosition();
									while (loop_flag)
									{
										setCursorVisable(true);
										cout << "���X�G";
										cin >> input;
										setCursorVisable(false);
										if (input >= 0 && input <= ptr->players[ptr->run].getDeposit())
										{
											cout << "���X���\�I�I";
											ptr->players[ptr->run].setCash(ptr->players[ptr->run].getCash() + input);
											ptr->players[ptr->run].setDeposit(ptr->players[ptr->run].getDeposit() - input);
											loop_flag = false;
										}
										else
										{
											cout << "���X���ѡA�Э��s��J�A�����N���~��";
											system("pause>nul");
											SetPosition(tmp);
											cout << "                                                                                                                                    \n";
											cout << "                                                                                                                                    \n";
											SetPosition(tmp);
										}
									}
								}
								break;

							// �d�ݪѲ�
							case 2:
								break;

							// �R�J�Ѳ�
							case 3:
								break;

							// ��X�Ѳ�
							case 4:
								break;

							// ���}�Ȧ�
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
