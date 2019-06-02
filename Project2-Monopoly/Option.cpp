#include "Option.h"
#include "Game.h"
#include "Stock.h"
#include "Player.h"
#include "Console.h"
#include <string>

const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;
const int MENU_LEN = 4;
const int OPTION_TOP = 20, OPTION_LEFT = 13, OPTION_WIDTH = 84;
const vector<string> menu = { "儲存遊戲", "載入存檔", "音樂設定", "離開遊戲" };
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
                while (inBank)
                {
                    SetColor(7); nowPos = { 38,20 }; SetPosition(nowPos);
                    cout << "歡迎來到銀行 !!! 需要什麼服務呢 ?";

                    int deposit = game->players[game->run].getDeposit();
                    int cash = game->players[game->run].getCash();

                    nowPos = { 48,22 }; SetPosition(nowPos);
                    cout << "存款";
                    nowPos = { 56,22 }; SetPosition(nowPos);
                    cout << "提款";
                    nowPos = { 48,24 }; SetPosition(nowPos);
                    cout << "借款";
                    nowPos = { 56,24 }; SetPosition(nowPos);
                    cout << "還錢";
                    nowPos = { 48,26 }; SetPosition(nowPos);
                    cout << "查看今日股票";
                    nowPos = { 50,28 }; SetPosition(nowPos);
                    cout << "買入股票";
                    nowPos = { 50,30 }; SetPosition(nowPos);
                    cout << "賣出股票";
                    nowPos = { 50,32 }; SetPosition(nowPos);
                    cout << "離開銀行";

                    switch (nowPoint)
                    {
                    case 0:
                        SetColor(240);
                        nowPos = { 48,22 }; SetPosition(nowPos);
                        cout << "存款";
                        SetColor(7);
                        break;
                    case 1:
                        SetColor(240);
                        nowPos = { 56,22 }; SetPosition(nowPos);
                        cout << "提款";
                        SetColor(7);
                        break;
                    case 2:
                        SetColor(240);
                        nowPos = { 48,24 }; SetPosition(nowPos);
                        cout << "借款";
                        SetColor(7);
                        break;
                    case 3:
                        SetColor(240);
                        nowPos = { 56,24 }; SetPosition(nowPos);
                        cout << "還錢";
                        SetColor(7);
                        break;
                    case 4:
                        SetColor(240);
                        nowPos = { 48,26 }; SetPosition(nowPos);
                        cout << "查看今日股票";
                        SetColor(7);
                        break;
                    case 5:
                        SetColor(240);
                        nowPos = { 50,28 }; SetPosition(nowPos);
                        cout << "買入股票";
                        SetColor(7);
                        break;
                    case 6:
                        SetColor(240);
                        nowPos = { 50,30 }; SetPosition(nowPos);
                        cout << "賣出股票";
                        SetColor(7);
                        break;
                    case 7:
                        SetColor(240);
                        nowPos = { 50,32 }; SetPosition(nowPos);
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
                            for (int i = 28; i < 40; i++)
                            {
                                nowPos = { 20, i }; SetPosition(nowPos);
                                cout << "                                                           ";
                            }

                            nowPos = { 43,28 }; SetPosition(nowPos);
                            cout << "您的戶頭現在有 $ " << game->players[game->run].getDeposit();
                            nowPos = { 43,30 }; SetPosition(nowPos);
                            cout << "您當前有現金 $ " << game->players[game->run].getCash();

                            nowPos = { 43,32 }; SetPosition(nowPos);
                            cout << "您想要存多少錢呢 ?";

                            nowPos = { 43,34 }; SetPosition(nowPos);
                            SetColor(240);
                            cout << "                 ";
                            nowPos = { 43,34 }; SetPosition(nowPos);
                            getline(cin, temp);
                            if (temp != "")
                            {
                                amount = stoi(temp);
                                if (amount > cash)
                                {
                                    SetColor(12);
                                    nowPos = { 42,36 }; SetPosition(nowPos);
                                    cout << "現金不足，已取消存款";

                                }
                                else
                                {
                                    game->players[game->run].plusDeposit(amount);
                                    game->players[game->run].minusCash(amount);
                                    SetColor(12);
                                    nowPos = { 46,36 }; SetPosition(nowPos);
                                    cout << "存錢錢成功 !";
                                }
                                SetColor(240);
                                nowPos = { 50,38 }; SetPosition(nowPos);
                                cout << "確認";
                                game->printPlayer();

                                getchar();
                            }
                            else
                            {
                                SetColor(12);
                                nowPos = { 37,36 }; SetPosition(nowPos);
                                cout << "您沒有輸入任何金額，已取消存款";
                                bool option = true;
                                int place = 1;

                                SetColor(240);
                                nowPos = { 50,38 }; SetPosition(nowPos);
                                cout << "確認";
                                getchar();
                            }

                            SetColor(7);
                            for (int i = 26; i < 40; i++)
                            {
                                nowPos = { 20, i }; SetPosition(nowPos);
                                cout << "                                               ";
                            }

                            break;

                            // 借款
                        case 1:

                            break;
                            // 提款
                        case 2:
                            SetColor(7);
                            for (int i = 28; i < 40; i++)
                            {
                                nowPos = { 20, i }; SetPosition(nowPos);
                                cout << "                                                           ";
                            }

                            nowPos = { 43,28 }; SetPosition(nowPos);
                            cout << "您的戶頭現在有 $ " << game->players[game->run].getDeposit();
                            nowPos = { 43,30 }; SetPosition(nowPos);
                            cout << "您當前有現金 $ " << game->players[game->run].getCash();

                            nowPos = { 43,32 }; SetPosition(nowPos);
                            cout << "您想要提領多少錢呢 ?";

                            nowPos = { 43,34 }; SetPosition(nowPos);
                            SetColor(240);
                            cout << "                 ";
                            nowPos = { 43,34 }; SetPosition(nowPos);
                            getline(cin, temp);
                            if (temp != "")
                            {
                                amount = stoi(temp);
                                if (amount > cash)
                                {
                                    SetColor(12);
                                    nowPos = { 42,36 }; SetPosition(nowPos);
                                    cout << "存款不足，已取消提款";

                                }
                                else
                                {
                                    game->players[game->run].minusDeposit(amount);
                                    game->players[game->run].plusCash(amount);
                                    SetColor(12);
                                    nowPos = { 46,36 }; SetPosition(nowPos);
                                    cout << "拿錢錢成功 !";
                                }
                                SetColor(240);
                                nowPos = { 50,38 }; SetPosition(nowPos);
                                cout << "確認";
                                game->printPlayer();

                                getchar();
                            }
                            else
                            {
                                SetColor(12);
                                nowPos = { 37,36 }; SetPosition(nowPos);
                                cout << "您沒有輸入任何金額，已取消提款";
                                bool option = true;
                                int place = 1;

                                SetColor(240);
                                nowPos = { 50,38 }; SetPosition(nowPos);
                                cout << "確認";
                                getchar();
                            }

                            SetColor(7);
                            for (int i = 26; i < 40; i++)
                            {
                                nowPos = { 20, i }; SetPosition(nowPos);
                                cout << "                                               ";
                            }
                            break;

                            // 查看股票
                        case 3:

                            break;

                            // 買入股票
                        case 4:
                            break;

                            // 賣出股票
                        case 5:
                            break;

                            // 離開銀行
                        case 6:
                            inBank = false;
                            break;
                        }
                        break;
                    }
                }

                for (int i = 17; i < 40; i++)
                {
                    nowPos = { 30, i }; SetPosition(nowPos);
                    cout << "                                               ";
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
        if (i == choosen) SetColor(0x70);
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
