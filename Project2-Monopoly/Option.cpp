#include "Option.h"
#include "Game.h"
#include "Player.h"
#include "Console.h"
#include <string>

const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;
const int MENU_LEN = 4;
const int OPTION_TOP = 20, OPTION_LEFT = 13, OPTION_WIDTH = 84;
const vector<string> menu = { "儲存遊戲","載入存檔","音樂設定","離開遊戲" };
Option::Option(Game* thisGame, vector<string> newOptions, vector<string> newMessages)
{
    game = thisGame;
    options = newOptions;
    messages = newMessages;

    int choosen = 0;
    int choosenInMenu;
		string filename;
    bool optionsFlag = true;
    PrintOption(choosen);
    while (optionsFlag)
		{
			switch (char keyin = _getch())
			{
        case UP:
            choosen = choosen > 0 ? choosen - 1 : options.size() - 1;
            PrintOption(choosen);
				break;
        case DOWN:
            choosen = choosen < options.size() - 1 ? choosen + 1 : 0;
            PrintOption(choosen);
				break;
			case ENTER:
            if (options[choosen] == "擲骰子")
				{
                //int position = (game->players.at(game->run).getPosition() + 1);//固定走一步 用於測試
                size_t diceNumber = game->rollTheDice();
                int position = (game->players.at(game->run).getPosition() + diceNumber) % (game->map.getMapSize());
                game->players.at(game->run).setPosition(position);
                game->printUI();

                Option(game, { "確定" }, { "你擲出 " + to_string(diceNumber) + " 點。",
                                           "你來到" + game->map.getMap().at(position)->getName() + "。" });
                // game->isFinishRound = true;
				}
            if (options[choosen] == "去銀行")
				{
					/*"銀行"的實作*/
					bool inBank = true;

					for (int i = 10; i < 33; i++)
					{
						SetColor(7);
						SetPosition({ 30, i });
						cout << "                                                ";
					}

					position temp = getCursorPosition();
					SetPosition({ 30,11 }); SetColor(14);
					cout << " /$$$$$$$    /$$$$$$     /$$   /$$   /$$   /$$"; SetPosition({ 30,12 });
					cout << "| $$__  $$  / $$__  $$  | $$$  |$$  | $$  /$$"; SetPosition({ 30,13 });
					cout << "| $$  \\ $$  | $$   \\$$  | $$$$ |$$  | $$ /$$"; SetPosition({ 30,14 });
					cout << "| $$$$$$$   | $$$$$$$$  | $$ $$ $$  | $$$$$"; SetPosition({ 30,15 });
					cout << "| $$__  $$  | $$__  $$  | $$  $$$$  | $$  $$"; SetPosition({ 30,16 });
					cout << "| $$  \\ $$  | $$  | $$  | $$\\  $$$  | $$\\  $$"; SetPosition({ 30,17 });
					cout << "| $$$$$$$/  | $$  | $$  | $$ \\  $$  | $$ \\  $$"; SetPosition({ 30,18 });
					cout << "| _______/  |__/  |__/  |__ / \\__/  |__ / \\__/ ";

					int nowPoint = 0;
					int nowBuy = 0;
					bool buying;
					while (inBank)
					{
						SetColor(7); SetPosition({ 38,20 });
						cout << "歡迎來到銀行 !!! 需要什麼服務呢 ?";

						int deposit = thisGame->players[thisGame->run].getDeposit();
						int cash = thisGame->players[thisGame->run].getCash();

						SetPosition({ 46,22 });
						cout << "存款";
						SetPosition({ 54,22 });
						cout << "提款";
						SetPosition({ 46,24 });
						cout << "借款";
						SetPosition({ 54,24 });
						cout << "還錢";
						SetPosition({ 46,26 });
						cout << "查看今日股票";
						SetPosition({ 48,28 });
						cout << "買入股票";
						SetPosition({ 48,30 });
						cout << "賣出股票";
						SetPosition({ 48,32 });
						cout << "離開銀行";

						switch (nowPoint)
						{
						case 0:
							SetColor(240);
							SetPosition({ 46,22 });
							cout << "存款";
							SetColor(7);
							break;
						case 1:
							SetColor(240);
							SetPosition({ 54,22 });
							cout << "提款";
							SetColor(7);
							break;
						case 2:
							SetColor(240);
							SetPosition({ 46,24 });
							cout << "借款";
							SetColor(7);
							break;
						case 3:
							SetColor(240);
							SetPosition({ 54,24 });
							cout << "還錢";
							SetColor(7);
							break;
						case 4:
							SetColor(240);
							SetPosition({ 46,26 });
							cout << "查看今日股票";
							SetColor(7);
							break;
						case 5:
							SetColor(240);
							SetPosition({ 48,28 });
							cout << "買入股票";
							SetColor(7);
							break;
						case 6:
							SetColor(240);
							SetPosition({ 48,30 });
							cout << "賣出股票";
							SetColor(7);
							break;
						case 7:
							SetColor(240);
							SetPosition({ 48,32 });
							cout << "離開銀行";
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
							// 存款
							case 0:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									SetPosition({ 38, i });
									cout << "                                               ";
								}

								SetPosition({ 43,22 });
								cout << "您的戶頭現在有 $ " << thisGame->players[thisGame->run].getDeposit();
								SetPosition({ 43,24 });
								cout << "您當前有現金 $ " << thisGame->players[thisGame->run].getCash();

								SetPosition({ 43,26 });
								cout << "您想要存多少錢呢 ?";

								SetPosition({ 43,28 });
								SetColor(240);
								cout << "                 ";
								SetPosition({ 43,28 });
								getline(cin, temp);
								if (temp != "")
								{
									amount = stoi(temp);
									if (amount > cash)
									{
										SetColor(12);
										SetPosition({ 42,28 });
										cout << "現金不足，已取消存款";

									}
									else
									{
										thisGame->players[thisGame->run].plusDeposit(amount);
										thisGame->players[thisGame->run].minusCash(amount);
										SetColor(12);
										SetPosition({ 43,28 });
										cout << "                              ";
										SetPosition({ 46,28 });
										cout << "存錢錢成功 !";
									}
									SetColor(240);
									SetPosition({ 50,30 });
									cout << "確認";
									game->printPlayer();

									getchar();
								}
								else
								{
									SetColor(12);
									SetPosition({ 37,28 });
									cout << "您沒有輸入任何金額，已取消存款";

									SetColor(240);
									SetPosition({ 50,30 });
									cout << "確認";
									getchar();
								}

								SetColor(7);
								for (int i = 20; i < 32; i++)
								{
									SetPosition({ 35, i });
									cout << "                                                ";
								}

								break;
							// 提款
							case 1:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									SetPosition({ 38, i });
									cout << "                                               ";
								}

								SetPosition({ 43,22 });
								cout << "您的戶頭現在有 $ " << thisGame->players[thisGame->run].getDeposit();
								SetPosition({ 43,24 });
								cout << "您當前有現金 $ " << thisGame->players[thisGame->run].getCash();

								SetPosition({ 43,26 });
								cout << "您想要領多少錢呢 ?";

								SetPosition({ 43,28 });
								SetColor(240);
								cout << "                 ";
								SetPosition({ 43,28 });
								getline(cin, temp);
								if (temp != "")
								{
									amount = stoi(temp);
									if (amount > deposit)
									{
										SetColor(12);
										SetPosition({ 42,28 });
										cout << "存款不足，已取消提款";

									}
									else
									{
										thisGame->players[thisGame->run].minusDeposit(amount);
										thisGame->players[thisGame->run].plusCash(amount);
										SetColor(12);
										SetPosition({ 43,28 });
										cout << "                              ";
										SetPosition({ 46,28 });
										cout << "拿錢錢成功 !";
									}
									SetColor(240);
									SetPosition({ 50,30 });
									cout << "確認";
									game->printPlayer();

									getchar();
								}
								else
								{
									SetColor(12);
									SetPosition({ 37,28 });
									cout << "您沒有輸入任何金額，已取消提款";

									SetColor(240);
									SetPosition({ 50,30 });
									cout << "確認";
									getchar();
								}

								SetColor(7);
								for (int i = 20; i < 32; i++)
								{
									SetPosition({ 35, i });
									cout << "                                                ";
								}
								break;
							// 借款
							case 2:

								break;
							// 還錢
							case 3:

								break;
							// 查看股票
							case 4:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									SetPosition({ 38, i });
									cout << "                                               ";
								}

								SetPosition({ 60, 20 });
								cout << "今日股票價位";
								for (int i = 0; i < game->stock.getStockList().size(); i++)
								{
									SetPosition({ 60, 22 + i * 2 });
									cout << game->stock.getStockList()[i].name << " : $ " << game->stock.getStockList()[i].value;
								}

								SetPosition({ 34, 20 });
								cout << "您持有的股票";
								amount = 0;
								for (int i = 0; i < 5; i++)
								{
									if (thisGame->players[thisGame->run].getOwnStock()[i] > 0)
									{
										SetPosition({ 35, 22 + amount * 2 });
										cout << game->stock.getStockList()[i].name << " * " << thisGame->players[thisGame->run].getOwnStock()[i];
										amount++;
									}
								}
								if (amount == 0)
								{
									SetPosition({ 32, 22 });
									cout << "您目前並沒有持有股票";
								}
								SetColor(240);
								SetPosition({ 50,32 });
								cout << "確認";
								getchar();

								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									SetPosition({ 28, i });
									cout << "                                                       ";
								}

								break;

							// 買入股票
							case 5:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									SetPosition({ 38, i });
									cout << "                                               ";
								}

								buying = true;
								nowBuy = 0;
								while (buying)
								{
									SetPosition({ 43, 20 });
									cout << "您的戶頭中有 $ " << thisGame->players[thisGame->run].getDeposit();

									for (int i = 0; i < game->stock.getStockList().size(); i++)
									{
										SetPosition({ 46, 22 + i * 2 });
										cout << game->stock.getStockList()[i].name << " : $ " << game->stock.getStockList()[i].value;
									}
									SetPosition({ 50, 32 });
									cout << "離開";

									SetColor(240);
									if (nowBuy < 5)
									{
										SetPosition({ 46, 22 + nowBuy * 2 });
										cout << game->stock.getStockList()[nowBuy].name << " : $ " << game->stock.getStockList()[nowBuy].value;
									}
									else if (nowBuy == 5)
									{
										SetPosition({ 50, 32 });
										cout << "離開";
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
												SetPosition({ 38, i });
												cout << "                                               ";
											}
											if (thisGame->players[thisGame->run].getDeposit() >= game->stock.getStockList()[nowBuy].value)
											{
												thisGame->players[thisGame->run].buyStock(nowBuy, game->stock.getStockList()[nowBuy]);

												SetColor(12);
												SetPosition({ 44, 25 });
												cout << "購買 "<< game->stock.getStockList()[nowBuy].name << " 成功";
												
											}
											else
											{
												SetColor(12);
												SetPosition({ 46, 25 });
												cout << "您的存款不足";
											}
											SetColor(240);
											SetPosition({ 50,28 });
											cout << "確認";
											SetColor(7);
											getchar();

											for (int i = 20; i < 34; i++)
											{
												SetPosition({ 38, i });
												cout << "                                               ";
											}

										}
										break;
									}

								}

								for (int i = 20; i < 34; i++)
								{
									SetPosition({ 28, i });
									cout << "                                                       ";
								}

								break;

							// 賣出股票
							case 6:
								SetColor(7);
								for (int i = 20; i < 34; i++)
								{
									SetPosition({ 38, i });
									cout << "                                               ";
								}

								buying = true;
								nowBuy = 0;
								while (buying)
								{
									SetPosition({ 43, 20 });
									cout << "您的戶頭中有 $ " << thisGame->players[thisGame->run].getDeposit();

									for (int i = 0; i < game->stock.getStockList().size(); i++)
									{
										SetPosition({ 46, 22 + i * 2 });
										cout << game->stock.getStockList()[i].name << " * " << thisGame->players[thisGame->run].getOwnStock()[i];
									}
									SetPosition({ 50, 32 });
									cout << "離開";


									SetColor(240);
									if (nowBuy < 5)
									{
										SetPosition({ 46, 22 + nowBuy * 2 });
										cout << game->stock.getStockList()[nowBuy].name << " * " << thisGame->players[thisGame->run].getOwnStock()[nowBuy];
									}
									else if (nowBuy == 5)
									{
										SetPosition({ 50, 32 });
										cout << "離開";
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
												SetPosition({ 38, i });
												cout << "                                               ";
											}
											if (thisGame->players[thisGame->run].getOwnStock()[nowBuy] > 0)
											{
												thisGame->players[thisGame->run].sellStock(nowBuy, game->stock.getStockList()[nowBuy]);
												SetColor(12);
												SetPosition({ 44, 25 });
												cout << "賣出 " << game->stock.getStockList()[nowBuy].name << " 成功";
											}
											else
											{
												SetColor(12);
												SetPosition({ 43, 25 });
												cout << "您目前沒有這支股票可賣";
											}
											SetColor(240);
											SetPosition({ 50,28 });
											cout << "確認";
											SetColor(7);
											getchar();

											for (int i = 20; i < 34; i++)
											{
												SetPosition({ 38, i });
												cout << "                                               ";
											}
										}
										break;
									}

								}

								for (int i = 20; i < 34; i++)
								{
									SetPosition({ 28, i });
									cout << "                                                       ";
								}
								break;

							// 離開銀行
							case 7:
								inBank = false;
								break;
							}
							break;
						}
					}

					for (int i = 10; i < 33; i++)
					{
						SetPosition({ 30, i });
						cout << "                                                ";
					}
					SetPosition(temp);
				}

            if (options[choosen] == "升級")
				{
                House* house = (House*)game->map.getMap().at(game->players.at(game->run).getPosition());
					house->setLevel((house->getLevel()) + 1);
                Option(game, { "確定" }, { "你已將" + house->getName() + "升級到 " + to_string(house->getLevel() + 1) + " 等。" });
				}
            if (options[choosen] == "購買")
				{
					/*"買空屋"的實作*/
					/*待補游標位置設定*/
                House* house = (House*)game->map.getMap().at(game->players.at(game->run).getPosition());
                game->players.at(game->run).buyHouse((House*)game->map.getMap().at(game->players.at(game->run).getPosition()));
                game->printUI();
                Option(game,
                       { "確定" },
                       { "你已花費 " + to_string(house->getCostOfOwn()) + " 元買下" + house->getName() + "！",
                         "你還有 " + to_string(game->players[game->run].getCash()) + " 現金。" });
                game->printUI();
				}
            optionsFlag = false;//停止選擇Option的內容
            clearOption();
				break;
			case ESC:
            clearOption();
            choosenInMenu = 0;
				bool menu_flag = true;
				PrintMenu(0);
				while (menu_flag)
				{
					switch (char keyin_menu = _getch())
					{
                case UP:
                    choosenInMenu = choosenInMenu > 0 ? choosenInMenu - 1 : menu.size()-1;
                    PrintMenu(choosenInMenu);
						break;
                case DOWN:
                    choosenInMenu = choosenInMenu < MENU_LEN - 1 ? choosenInMenu + 1 : 0;
                    PrintMenu(choosenInMenu);
						break;
					case ENTER:
						/*待補音樂調整的fun()*/
                    switch (choosenInMenu)
						{
						case 0:
							cin >> filename;
                        game->save(filename);
							break;
						case 1:
                        cin >> game->newGameName;
                        game->restartFlag = true;
                        game->isFinishRound = false;
							menu_flag = false;
                        optionsFlag = false;
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
            clearOption();
            PrintOption(choosen);
				break;
			}
		}
	}

void Option::clearOption()
{
    SetColor(0x07);
    for (int j = OPTION_TOP; j < 27; j++)
    {
        SetPosition({ OPTION_LEFT, j });
        for (int i = 4; i < OPTION_WIDTH - 4; i++)
        {
            cout << " ";
}
    }
}

void Option::PrintOption(int choosen)
{

    for (int i = 0; i < messages.size(); i++)
    {
        SetColor(0x07);
        SetPosition({ OPTION_LEFT + (OPTION_WIDTH - static_cast<int>(messages[i].length())) / 2,
                      OPTION_TOP + i });
        cout << messages[i];
    }
	for (int i = 0; i < options.size(); i++)
	{
		if(i== choosen) SetColor(0x70);
        else SetColor(0x07);
        SetPosition({ OPTION_LEFT + (OPTION_WIDTH - static_cast<int>(options[i].length())) / 2,
                      OPTION_TOP + static_cast<int>(messages.size()) + 1 + 2 * i });
		cout << options[i];
	}
}

void Option::PrintMenu(int choosen)
{
    SetColor(0x07);
	for (int i = 0; i < menu.size(); i++)
	{
		if (i == choosen) SetColor(0x70);
        else SetColor(0x07);
        SetPosition({ OPTION_LEFT + (OPTION_WIDTH - static_cast<int>(menu[i].length())) / 2,
                      OPTION_TOP + i * 2 });
		cout << menu[i];
	}
}
