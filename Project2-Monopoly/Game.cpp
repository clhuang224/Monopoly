#include "Game.h"

Game::Game(string input)
{
    load(input);
}

void Game::save(string filename)
{
    _mkdir("save");
    filename = "./save/" + filename;
    fstream savefile;
    savefile.open(filename, ios::out | ios::trunc);
    if (savefile.is_open())
    {
        //�Ĥ@��
        savefile << map.getMapName() << " " << remainingRound << " " << playerAmount << "\n";
        //map��
        for (int i = 0; i < map.getMapSize(); i++)
        {
            string id = to_string(i);
            vector<Block*> blocks = map.getMap();
            if (id.size() == 1)id = '0' + id;
            savefile << id << " " << blocks.at(i)->getName() << " " << blocks.at(i)->getType();
            if (blocks.at(i)->getType() == HOUSE)
            {
                House* house = (House*)blocks.at(i);
                vector<unsigned> tolls = house->getTollsList();
                savefile << " " << house->getCostOfOwn() << " " << tolls[0] << " " << tolls[1] << " " << tolls[2] << " " << tolls[3];
            }
            savefile << "\n";
        }
        //playerstate
        savefile << "playerstate " << run << "\n";
        //player��
        for (int i = 0; i < playerAmount; i++)
        {
            string p = to_string(players[i].getPosition());
            if (p.size() == 1)p = '0' + p;
            savefile << i << " " << p << " " << players[i].getCash() << "|" << players[i].getDeposit();
            for (int j = 0; j < players[i].getOwnHouse().size(); j++)
            {
                string tmp = to_string(players[i].getOwnHouse().at(j)->getPosition());
                if (tmp.size() == 1)tmp = '0' + tmp;
                savefile << " " << tmp << " " << players[i].getOwnHouse().at(j)->getLevel();
            }
            savefile << "\n";
        }

        savefile.close();
    }
    else
    {
        /*���Ы�orŪ�����Ѫ��ԭz??*/
        cout << "error";
    }
}

void Game::load(string filename)
{
    clear();

    fstream mapFile("./save/" + filename);
    if (mapFile.is_open())
    {
        string mapName;
        vector<Block*> mapContent;
        array<int, 4> playerPositions = { -1,-1,-1,-1 };//�̦h4�H

        //�ѷ�.txt�Ĥ@�C
        mapFile >> mapName >> remainingRound >> playerAmount;

        players.resize(playerAmount);

        string commandTmp;
        while (mapFile >> commandTmp && commandTmp != "playerstate")
        {
            int position = stoi(commandTmp);
            int blockType;
            string blockName;
            mapFile >> blockName >> blockType;
            if (blockType == START)
            {
                Start *blockTmp = new Start((unsigned int)position);
                mapContent.push_back(blockTmp);
            }
            if (blockType == HOUSE)
            {
                vector<unsigned> price;
                int cost;
                price.resize(4);
                mapFile >> cost >> price[0] >> price[1] >> price[2] >> price[3];
                House *blockTmp = new House((unsigned int)position, blockName, &bank, 0, cost, price, vector<unsigned>());
                mapContent.push_back(blockTmp);
            }
            if (blockType == CHANCE)
            {
                Chance *blockTmp = new Chance((unsigned int)position, vector<unsigned>());
                mapContent.push_back(blockTmp);
            }
            if (blockType == FORTUNE)
            {
                Fortune *blockTmp = new Fortune((unsigned int)position, vector<unsigned>());
                mapContent.push_back(blockTmp);
            }
        }

        mapFile >> run;

        string playerID, playerPosition, playerMoney;
        int cash, deposit;
        while (getline(mapFile, commandTmp))
        {
            if (!commandTmp.empty())
            {
                stringstream commandLine(commandTmp);
                commandLine >> playerID >> playerPosition >> playerMoney;

                //�s�ڳ���
                size_t devidePoint = playerMoney.find_first_of("|", 0);
                if (devidePoint >= playerMoney.size())
                {
                    deposit = 0;
                    cash = stoi(playerMoney);
                }
                else
                {
                    cash = stoi(playerMoney.substr(0, devidePoint));
                    string depositTmp = playerMoney.substr(devidePoint + 1, playerMoney.length() - 1);
                    if (depositTmp.size() == 0)deposit = 0;
                    else deposit = stoi(depositTmp);
                }
                playerPositions[stoi(playerID)] = stoi(playerPosition);
                Player playerTmp(string("Player 0") + playerID, stoi(playerPosition), cash, deposit);

                players.at(stoi(playerID)) = playerTmp;

                string house;
                unsigned int houseRank;
                //�o���Fmap������house�� �֦��̫��� �H�� �Ыε���
                while (commandLine >> house >> houseRank)
                {
                    ((House*)(mapContent[stoi(house)]))->setOwner(&players.at(stoi(playerID)));
                    ((House*)(mapContent[stoi(house)]))->setLevel(houseRank);
                    players.at(stoi(playerID)).freeHouse((House*)(mapContent[stoi(house)]));
                }
            }
        }

        map = Map(mapContent, mapName);
        mapFile.close();
    }
    else
    {
        //report alert?
    }
}

void Game::clear()
{
    playerAmount = 0;
    remainingRound = 20;
    isFinishRound = false;
    players.clear();
    lose = { false,false,false,false };
    run = 0;
    map = Map();
    bank = Player();
}

void Game::printUI()
{
    SetPosition({ 0,0 });
    SetColor(0x07);

    //�L�a��
    /*�a�ϤW���H��id�L�s��ĳMap�ϥΨ�ƽեΨӤ��}�L�s�A���M�C���L�o��h�|�{�{*/
    array<int, 4> playerPositions;
    for (int i = 0; i < players.size(); i++)
    {
        playerPositions[i] = players[i].getPosition();
    }
    map.updateMap(playerPositions);

    // �L�����T
    printPlayer();

    // �L�Ѿl�^�X�ơB���쪺���a
    SetPosition({ 40,34 });
    SetColor(0x07);
    cout << "�٦� ";
    SetColor(0x0B);
    cout << remainingRound;
    SetColor(0x07);
    cout << " �^�X�A���� ";
    SetColor(0x0B);
    cout << players[run].getName();
    SetColor(0x07);
    cout << " �C";

    // �L���a�Ҧb��m
    SetPosition({ 44,35 });
    SetColor(0x0B);
    cout << players[run].getName();
    SetColor(0x07);
    cout << " �b ";
    SetColor(0x0B);
    string currentPositionName = map.getMap().at(players[run].getPosition())->getName();
    for (unsigned i = 0; i < currentPositionName.length(); i++)
    {
        if (currentPositionName[i] != ' ')
        {
            cout << currentPositionName[i];
        }
    }
    SetColor(0x07);
    cout << " �C";

    // �L����֪��b�Y
    SetPosition({ 90, 12 + run * 7 });
    SetColor(0x0B);
    cout << "��";
    SetColor(0x07);
}

void Game::runGame()
{
    setCursorVisable(false);
    printUI();

    while (true)
    {
        if (remainingRound > 0)
        {
            for (; run < players.size() && !restartFlag; run++)//�C�^�X����(���a�ƶq)��
            {
                if (lose[run])continue;//���L��a�^�X

                printUI();
                isFinishRound = false;

                while (!isFinishRound && !restartFlag)//�Ӫ��a�b�o�^�X���Ҧ��ާ@
                {
                    //�ާ@�Ȧ�B�R�Ѳ��B���l�BOption���m�����
                    //�맹��l�N���i�H�A�ާ@�Ȧ�B�R�Ѳ�
                    Option(this, { "�Y��l","�h�Ȧ�" });

                    //���l��A����s��m�W���ĪG
                    while (isFinishRound == false)
                    {
                        //Ū�������a��m�W��block����
                        Block* block = map.getMap().at(players[run].getPosition());
                        if (block->getType() == HOUSE)
                        {
                            House* house = (House*)block;
                            if (house->getOwner() == &bank)
                            {

                                Option(this,
                                       { "�ʶR","���ʶR" },
                                       { house->getName() + "�ݰ⤤�A�u�n" + to_string(house->getCostOfOwn()) + "���I" });
                            }
                            else if (house->getOwner() == &players[run])
                            {
                                Option(this,
                                       { "�T�w" },
                                       { "�o���g�a�O�A���A�ثe�Ыε��Ŭ�" + to_string(house->getLevel()) + "�šC" });

                                if (house->getLevel() < 3)
                                {
                                    Option(this,
                                           { "�ɯ�","���ɯ�" },
                                           { "�ɯŭn��" + to_string(house->getPrice()) + "���A�O�_�ɯšH" });
                                }
                                else
                                {
                                    Option(this, { "�T�w" }, { "�A��" + house->getName() + "�w�g�O�̰��ŤF�I" });
                                }
                            }
                            else if (house->getOwner() != &players[run])
                            {
                                players[run].minusCash(house->getPrice());//�{����L���O
                                house->getOwner()->setDeposit(house->getOwner()->getDeposit() + house->getPrice());//�L���O�s�i�Ȧ�
                                /*�ݸɧ��㪺��X�T��*/
                                Option(this,
                                       { "�T�w" },
                                       { house->getName() + "�ݩ�" + house->getOwner()->getName() + "�C",
                                         "�A��I�L���O" + to_string(house->getPrice()) + "���C",
                                         "�A�٦�" + to_string(players[run].getCash()) + "�{���C" });
                                printUI();
                            }
                            isFinishRound = true;
                        }
                        else if (block->getType() == CHANCE)
                        {
                            Option(this, { "�T�w" }, { Chance::getChance(&players[run]) });
                            printUI();
                            break;
                        }
                        else if (block->getType() == FORTUNE)
                        {
                            Option(this, { "�T�w" }, { Fortune::getFortune(&players[run]) });
                            printUI();
                        }
                    }
                }
                //�}���ŧi
                if (players[run].getCash() < 0)
                {
                    players[run].setCash(-1);
                    lose[run] = true;
                    Option(this, { "�T�w" }, { players[run].getName() + "�w�}���I�I" });
                    printUI();
                }
            }

            remainingRound--;
            run = 0;

            if (restartFlag)
            {
                restartFlag = false;
                load(newGameName);
                newGameName.clear();
            }
        }
        else
        {
            /*print �C�������A��Ĺ�F*/
            /*�i�H�ͦ��@�i�Үѵ��u�Ӫ�???*/
            /*option ���}�C��*/
        }
    }
}

size_t Game::rollTheDice()
{
    size_t output = 0;
    srand((unsigned)time(NULL));
    output += (rand() % 6 + 1);
    return output;
}

vector<Player> &Game::getPlayers()
{
    return players;
}

void Game::printPlayer()
{
    position temp = getCursorPosition();
    position usePos;

    SetColor(7);
    for (int i = 0; i < 28; i++)
    {
        usePos = { 95, 9 + i }; SetPosition(usePos);
        cout << "|                  |";
    }

    for (int i = 0; i < players.size(); i++)
    {
        usePos = { 96, 8 + i * 7 }; SetPosition(usePos);
        cout << "__________________";

        SetColor(players[i].getColor());
        usePos = { 100, 11 + i * 7 }; SetPosition(usePos);
        cout << players[i].getName();
        SetColor(7);

        usePos = { 101, 13 + i * 7 }; SetPosition(usePos);
        cout << "$ " << players[i].getCash();

        usePos = { 96, 15 + i * 7 }; SetPosition(usePos);
        cout << "__________________";
    }
    SetColor(7);
    SetPosition(temp);
}