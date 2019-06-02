#include "Option.h"
#include "Game.h"
#include "Stock.h"
#include "Player.h"
#include "Console.h"
#include <string>

const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;
const int MENU_LEN = 4;
const int OPTION_TOP = 20, OPTION_LEFT = 13, OPTION_WIDTH = 84;
const vector<string> menu = { "�x�s�C��", "���J�s��", "���ֳ]�w", "���}�C��" };
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
            if (options[choosen] == "�Y��l")
            {
                //int position = (game->players.at(game->run).getPosition() + 1);//�T�w���@�B �Ω����
                size_t diceNumber = game->rollTheDice();
                int position = (game->players.at(game->run).getPosition() + diceNumber) % (game->map.getMapSize());
                game->players.at(game->run).setPosition(position);
                game->printUI();

                Option(game, { "�T�w" }, { "�A�Y�X " + to_string(diceNumber) + " �I�C",
                                           "�A�Ө�" + game->map.getMap().at(position)->getName() + "�C" });
                // game->isFinishRound = true;
            }
            if (options[choosen] == "�h�Ȧ�")
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
                while (inBank)
                {
                    SetColor(7); nowPos = { 38,20 }; SetPosition(nowPos);
                    cout << "�w��Ө�Ȧ� !!! �ݭn����A�ȩO ?";

                    int deposit = game->players[game->run].getDeposit();
                    int cash = game->players[game->run].getCash();

                    nowPos = { 48,22 }; SetPosition(nowPos);
                    cout << "�s��";
                    nowPos = { 56,22 }; SetPosition(nowPos);
                    cout << "����";
                    nowPos = { 48,24 }; SetPosition(nowPos);
                    cout << "�ɴ�";
                    nowPos = { 56,24 }; SetPosition(nowPos);
                    cout << "�ٿ�";
                    nowPos = { 48,26 }; SetPosition(nowPos);
                    cout << "�d�ݤ���Ѳ�";
                    nowPos = { 50,28 }; SetPosition(nowPos);
                    cout << "�R�J�Ѳ�";
                    nowPos = { 50,30 }; SetPosition(nowPos);
                    cout << "��X�Ѳ�";
                    nowPos = { 50,32 }; SetPosition(nowPos);
                    cout << "���}�Ȧ�";

                    switch (nowPoint)
                    {
                    case 0:
                        SetColor(240);
                        nowPos = { 48,22 }; SetPosition(nowPos);
                        cout << "�s��";
                        SetColor(7);
                        break;
                    case 1:
                        SetColor(240);
                        nowPos = { 56,22 }; SetPosition(nowPos);
                        cout << "����";
                        SetColor(7);
                        break;
                    case 2:
                        SetColor(240);
                        nowPos = { 48,24 }; SetPosition(nowPos);
                        cout << "�ɴ�";
                        SetColor(7);
                        break;
                    case 3:
                        SetColor(240);
                        nowPos = { 56,24 }; SetPosition(nowPos);
                        cout << "�ٿ�";
                        SetColor(7);
                        break;
                    case 4:
                        SetColor(240);
                        nowPos = { 48,26 }; SetPosition(nowPos);
                        cout << "�d�ݤ���Ѳ�";
                        SetColor(7);
                        break;
                    case 5:
                        SetColor(240);
                        nowPos = { 50,28 }; SetPosition(nowPos);
                        cout << "�R�J�Ѳ�";
                        SetColor(7);
                        break;
                    case 6:
                        SetColor(240);
                        nowPos = { 50,30 }; SetPosition(nowPos);
                        cout << "��X�Ѳ�";
                        SetColor(7);
                        break;
                    case 7:
                        SetColor(240);
                        nowPos = { 50,32 }; SetPosition(nowPos);
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
                            for (int i = 28; i < 40; i++)
                            {
                                nowPos = { 20, i }; SetPosition(nowPos);
                                cout << "                                                           ";
                            }

                            nowPos = { 43,28 }; SetPosition(nowPos);
                            cout << "�z�����Y�{�b�� $ " << game->players[game->run].getDeposit();
                            nowPos = { 43,30 }; SetPosition(nowPos);
                            cout << "�z��e���{�� $ " << game->players[game->run].getCash();

                            nowPos = { 43,32 }; SetPosition(nowPos);
                            cout << "�z�Q�n�s�h�ֿ��O ?";

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
                                    cout << "�{�������A�w�����s��";

                                }
                                else
                                {
                                    game->players[game->run].plusDeposit(amount);
                                    game->players[game->run].minusCash(amount);
                                    SetColor(12);
                                    nowPos = { 46,36 }; SetPosition(nowPos);
                                    cout << "�s�������\ !";
                                }
                                SetColor(240);
                                nowPos = { 50,38 }; SetPosition(nowPos);
                                cout << "�T�{";
                                game->printPlayer();

                                getchar();
                            }
                            else
                            {
                                SetColor(12);
                                nowPos = { 37,36 }; SetPosition(nowPos);
                                cout << "�z�S����J������B�A�w�����s��";
                                bool option = true;
                                int place = 1;

                                SetColor(240);
                                nowPos = { 50,38 }; SetPosition(nowPos);
                                cout << "�T�{";
                                getchar();
                            }

                            SetColor(7);
                            for (int i = 26; i < 40; i++)
                            {
                                nowPos = { 20, i }; SetPosition(nowPos);
                                cout << "                                               ";
                            }

                            break;

                            // �ɴ�
                        case 1:

                            break;
                            // ����
                        case 2:
                            SetColor(7);
                            for (int i = 28; i < 40; i++)
                            {
                                nowPos = { 20, i }; SetPosition(nowPos);
                                cout << "                                                           ";
                            }

                            nowPos = { 43,28 }; SetPosition(nowPos);
                            cout << "�z�����Y�{�b�� $ " << game->players[game->run].getDeposit();
                            nowPos = { 43,30 }; SetPosition(nowPos);
                            cout << "�z��e���{�� $ " << game->players[game->run].getCash();

                            nowPos = { 43,32 }; SetPosition(nowPos);
                            cout << "�z�Q�n����h�ֿ��O ?";

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
                                    cout << "�s�ڤ����A�w��������";

                                }
                                else
                                {
                                    game->players[game->run].minusDeposit(amount);
                                    game->players[game->run].plusCash(amount);
                                    SetColor(12);
                                    nowPos = { 46,36 }; SetPosition(nowPos);
                                    cout << "���������\ !";
                                }
                                SetColor(240);
                                nowPos = { 50,38 }; SetPosition(nowPos);
                                cout << "�T�{";
                                game->printPlayer();

                                getchar();
                            }
                            else
                            {
                                SetColor(12);
                                nowPos = { 37,36 }; SetPosition(nowPos);
                                cout << "�z�S����J������B�A�w��������";
                                bool option = true;
                                int place = 1;

                                SetColor(240);
                                nowPos = { 50,38 }; SetPosition(nowPos);
                                cout << "�T�{";
                                getchar();
                            }

                            SetColor(7);
                            for (int i = 26; i < 40; i++)
                            {
                                nowPos = { 20, i }; SetPosition(nowPos);
                                cout << "                                               ";
                            }
                            break;

                            // �d�ݪѲ�
                        case 3:

                            break;

                            // �R�J�Ѳ�
                        case 4:
                            break;

                            // ��X�Ѳ�
                        case 5:
                            break;

                            // ���}�Ȧ�
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

            if (options[choosen] == "�ɯ�")
            {
                House* house = (House*)game->map.getMap().at(game->players.at(game->run).getPosition());
                house->setLevel((house->getLevel()) + 1);
                Option(game, { "�T�w" }, { "�A�w�N" + house->getName() + "�ɯŨ� " + to_string(house->getLevel() + 1) + " ���C" });
            }
            if (options[choosen] == "�ʶR")
            {
                /*"�R�ū�"����@*/
                /*�ݸɴ�Ц�m�]�w*/
                House* house = (House*)game->map.getMap().at(game->players.at(game->run).getPosition());
                game->players.at(game->run).buyHouse((House*)game->map.getMap().at(game->players.at(game->run).getPosition()));
                game->printUI();
                Option(game,
                       { "�T�w" },
                       { "�A�w��O " + to_string(house->getCostOfOwn()) + " ���R�U" + house->getName() + "�I",
                         "�A�٦� " + to_string(game->players[game->run].getCash()) + " �{���C" });
                game->printUI();
            }
            optionsFlag = false;//������Option�����e
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
                    /*�ݸɭ��ֽվ㪺fun()*/
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
