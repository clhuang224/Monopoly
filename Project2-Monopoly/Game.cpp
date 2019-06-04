#include "Game.h"

const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;

Game::Game(string input)
{
    load(input, false);
}

void Game::save(string filename, bool showFeedback)
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

        // �Ѳ�
        savefile << "stock" << endl;
        for (int i = 0; i < playerAmount; i++)
        {
            savefile << i;
            for (int j = 0; j < stock.getStockList().size(); j++)
            {
                savefile << " " << players.at(i).getOwnStock()[j];
            }
            savefile << endl;
        }

        // �D��
        savefile << "item" << endl;
        for (int i = 0; i < playerAmount; i++)
        {
            savefile << i;
            for (int j = 0; j < players.at(i).getItem().size(); j++)
            {
                savefile << " " << players.at(i).getItem()[j];
            }
            savefile << endl;
        }

        savefile.close();
        if (showFeedback == true)
        {
            Option(this, { "�T�w" }, { "�w�x�s�C���C","�ɮצW�٬� " + filename.substr(7) + " �C" });
        }
    }
    else
    {
        if (showFeedback == true)
        {
            Option(this, { "�T�w" }, { "�x�s�C�����ѡC" });
        }
    }
}

void Game::load(string filename, bool showFeedback)
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
        mapFile.get();
        string playerID, playerPosition, playerMoney;
        int cash, deposit;
        
        // ���a�s�� ��m �� �Фl
        while (getline(mapFile, commandTmp) && commandTmp != "stock")
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
                Player playerTmp(string("Player 0") + to_string(stoi(playerID) + 1), stoi(playerPosition), cash, deposit);
                
                switch (stoi(playerID))
                {
                case 0:
                    playerTmp.setColor(0x2);
                    break;
                case 1:
                    playerTmp.setColor(0x3);
                    break;
                case 2:
                    playerTmp.setColor(0x4);
                    break;
                case 3:
                    playerTmp.setColor(0x5);
                    break;
                }
                players.at(stoi(playerID)) = playerTmp;
                remains = players.size();
                string house;
                unsigned int houseRank;
                //�o���Fmap��house�� �֦��̫��� �H�� �Ыε��šA�٦��W�[player�֦���house�M�椺�e
                while (commandLine >> house >> houseRank)
                {
                    ((House*)(mapContent[stoi(house)]))->setOwner(&players.at(stoi(playerID)));
                    ((House*)(mapContent[stoi(house)]))->setLevel(houseRank);
                    players.at(stoi(playerID)).freeHouse((House*)(mapContent[stoi(house)]));
                }
            }
        
            // �Ѳ�
            int tempStock[5] = { 0 };
            while (getline(mapFile, commandTmp) && commandTmp != "item")
            {
                stringstream commandLine(commandTmp);
                int playerNumber;
                commandLine >> playerNumber;
                for (int i = 0; i < stock.getStockList().size(); i++)
                {
                    commandLine >> tempStock[i];
        }
                players.at(playerNumber).setOwnStock(tempStock, stock.getStockList().size());
            }

            // �D��
            while (getline(mapFile, commandTmp))
            {
                vector<unsigned> tempItem = { 0,0 };
                stringstream commandLine(commandTmp);
                int playerNumber;
                commandLine >> playerNumber;
                for (int i = 0; i < players.at(0).getItem().size(); i++)
                {
                    unsigned temp;
                    commandLine >> temp;
                    tempItem[i] = temp;
                }
                players.at(playerNumber).setItem(tempItem);
            }
        
        map = Map(mapContent, mapName);
        mapFile.close();
        if (showFeedback == true)
        {
            Option(this, { "�T�w" }, { "�wŪ���C���C","�ɮצW�٬� " + filename + " �C" });
        }
    }
    else
    {
		if (showFeedback == true)
		{
			Option(this, { "�T�w" }, { "Ū���C�����ѡC" });
        }
    }
}

void Game::clear()
{
    playerAmount = 0;
    remainingRound = 20;
	remains = 0;
    diceRolled = false;
    roundEnd = false;
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
	updatePlayerUI();

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
    for (int i = 12; i <= 33; i+=7)
    {
        SetPosition({ 88,i });
        cout << "      ";
    }
    SetPosition({ 88, 12 + run * 7 });
    SetColor(0x0B);
    cout << "�����";
    SetColor(0x07);
}

void Game::runGame()
{
    printUI();
	printPlayer();

    while (continueGame)
    {
        if (remainingRound > 0 && 
            ((playerAmount > 1 && remains > 1) || // �h�H�Ҧ��G�j��@�H�٨S����~��
            (playerAmount == 1 && remains == 0)))  // ��H�Ҧ�
        {
            for (; run < players.size() && //�C�^�X����(���a�ƶq)��
                   !restartFlag &&
                   ((playerAmount > 1 && remains > 1) || (playerAmount == 1 && remains > 0)); run++)
            {
                if (lose[run])continue;//���L��a�^�X

                printUI();
				players[run].update();
                diceRolled = false;
                roundEnd = false;

                while (!diceRolled && !restartFlag)//�Ӫ��a�b�o�^�X���Ҧ��ާ@
                {
                    //�ާ@�Ȧ�B�R�Ѳ��B���l�BOption���m�����
                    //�맹��l�N���i�H�A�ާ@�Ȧ�B�R�Ѳ�
                    Option(this, { "�Y��l","�ϥιD��","�i�J�Ȧ�","�뭰" });

                    //���l��A����s��m�W���ĪG
                    if (diceRolled)
                    {
                        while (roundEnd == false)
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
                                           { "�o���g�a�O�A���A�ثe�Ыε��Ŭ�" + to_string(house->getLevel() + 1) + "�šC" });

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
                                    Option(this,
                                           { "�T�w" },
                                           { house->getName() + "�ݩ� " + house->getOwner()->getName() + " �C",
                                             "�A��I�L���O " + to_string(house->getPrice()) + " ���� " + house->getOwner()->getName() + " �C" });
                                    printUI();
                                }
                                diceRolled = true;
                                roundEnd = true;
                            }
                            else if (block->getType() == CHANCE)
                            {
                                Option(this, { "�T�w" }, { Chance::getChance(&players[run]) });
                                printUI();
                                break;
                            }
                            else if (block->getType() == FORTUNE)
                            {
                                Fortune::getFortune(this);
                            }
                            else if (block->getType() == START)
                            {
                                unsigned newItem = rand() % 2;
                                string itemName;
                                switch (newItem)
                                {
                                case 0:
                                    itemName = "������l";
                                    break;
                                case 1:
                                    itemName = "����";
                                    break;
                                }
                                vector<unsigned> tempItem = players[run].getItem();
                                tempItem[newItem]++;
                                players[run].setItem(tempItem);
                                Option(this, { "�T�w" }, { "�w�﮳��_�I���y�G" + itemName + "�C" });
                                roundEnd = true;
                            }
                        }
                        
                    }
                }
                //�}���ŧi
                if (players[run].getCash() < 0)
                {
                    players[run].setCash(-1);
                    lose[run] = true;
                    remains--;
                    Option(this, { "�T�w" }, { players[run].getName() + "�w�}���I�I" });
                    printUI();
                }
            }

            remainingRound--;
            run = 0;
            stock.valueChange();

            if (restartFlag)
            {
                restartFlag = false;
                load(newGameName);
                newGameName.clear();
            }
        }
        else
        {
            // �h�H
            if (playerAmount > 1)
            {
                // �ѤU���a���
                if (remains == 1)
                {
                    for (int i = 0; i < lose.size(); i++)
                    {
                        if (lose[i] == false)
                        {
                            /*�i�H�ͦ��@�i�Үѵ��u�Ӫ�???*/
                            Option(this,
                                   { "���s�}�l","���}�C��" },
                                   { players[i].getName() + "��ӡI", "�n���s�}�l�@���C���ܡH"
                                   });
                            break;
                        }
                    }
                }
                // �Ѿl�����]�{���Ϧs�ڡ^�̦h�����
                // ���Ҽ{���ⱡ��
                else
                {
                    Player winner = players.at(0);
                    for (int i = 1; i < players.size(); i++)
                    {
                        if (players.at(i).getCash() + players.at(i).getDeposit() > winner.getCash() + winner.getDeposit())
                        {
                            winner = players.at(i);
                        }
                    }
                    Option(this,
                           { "���s�}�l","�����C��" },
                           { winner.getName() + "��ӡI", "�n���s�}�l�@���C���ܡH"
                           });
                }
                
            }
            // ��H
            else if (playerAmount == 1)
            {
                if (remainingRound == 0)
                {
                    Option(this,
                           { "���s�}�l","�����C��" },
                           { "�A���w���L���@�͡C", "�n���s�}�l�@���C���ܡH"
                           });
                }
                else if (remains == 0)
                {
                    Option(this,
                           { "���s�}�l","�����C��" },
                           { "�@�ӤH�]��}���u�O�n�δΡI", "�n���s�}�l�@���C���ܡH"
                           });
                }
                
            }
        }
    }
}

size_t Game::rollTheDice()
{
    size_t output = 0;
    srand((unsigned)time(NULL));
    output += (rand() % 6 + 1);

    position temp = getCursorPosition();

    SetPosition({ 48,18 });
    cout << " ___________ ";
    SetPosition({ 48,19 });
    cout << "|           |";
    SetPosition({ 48,20 });
    cout << "|           |";
    SetPosition({ 48,21 });
    cout << "|           |";
    SetPosition({ 48,22 });
    cout << "|           |";
    SetPosition({ 48,23 });
    cout << "|           |";
    SetPosition({ 48,24 });
    cout << "|           |";
    SetPosition({ 48,25 });
    cout << "|___________|";

    for (int i = 6; i > 0; i--)
    {
        for (int j = 19; j < 25; j++)
        {
            SetPosition({ 49,j });
            cout << "          ";
        }
        switch (rand() % 6)
        {
        case 0:
            SetPosition({ 48,22 });
            cout << "|    �i     |";
            break;
        case 1:
            SetPosition({ 48,20 });
            cout << "|  �i       |";
            SetPosition({ 48,24 });
            cout << "|       �i  |";
            break;
        case 2:
            SetPosition({ 48,20 });
            cout << "|    �i     |";
            SetPosition({ 48,22 });
            cout << "|    �i     |";
            SetPosition({ 48,24 });
            cout << "|    �i     |";
            break;
        case 3:
            SetPosition({ 48,20 });
            cout << "|  �i   �i  |";
            SetPosition({ 48,24 });
            cout << "|  �i   �i  |";
            break;
        case 4:
            SetPosition({ 48,20 });
            cout << "|  �i   �i  |";
            SetPosition({ 48,22 });
            cout << "|    �i     |";
            SetPosition({ 48,24 });
            cout << "|  �i   �i  |";
            break;
        case 5:
            SetPosition({ 48,20 });
            cout << "|  �i   �i  |";
            SetPosition({ 48,22 });
            cout << "|  �i   �i  |";
            SetPosition({ 48,24 });
            cout << "|  �i   �i  |";
            break;
        }
        Sleep(i * 100);
    }

    switch (output - 1)
    {
    case 0:
        SetPosition({ 48,22 });
        cout << "|    �i     |";
        break;
    case 1:
        SetPosition({ 48,20 });
        cout << "|  �i       |";
        SetPosition({ 48,24 });
        cout << "|       �i  |";
        break;
    case 2:
        SetPosition({ 48,20 });
        cout << "|    �i     |";
        SetPosition({ 48,22 });
        cout << "|    �i     |";
        SetPosition({ 48,24 });
        cout << "|    �i     |";
        break;
    case 3:
        SetPosition({ 48,20 });
        cout << "|  �i   �i  |";
        SetPosition({ 48,24 });
        cout << "|  �i   �i  |";
        break;
    case 4:
        SetPosition({ 48,20 });
        cout << "|  �i   �i  |";
        SetPosition({ 48,22 });
        cout << "|    �i     |";
        SetPosition({ 48,24 });
        cout << "|  �i   �i  |";
        break;
    case 5:
        SetPosition({ 48,20 });
        cout << "|  �i   �i  |";
        SetPosition({ 48,22 });
        cout << "|  �i   �i  |";
        SetPosition({ 48,24 });
        cout << "|  �i   �i  |";
        break;
    }
    Sleep(1000);
    SetPosition(temp);
    return output;
}

vector<Player> &Game::getPlayers()
{
    return players;
}

void Game::printPlayer()
{
    position temp = getCursorPosition();

	
	SetColor(7);
	for (int i = 0; i < 28; i++)
	{
		SetPosition({ 95, 9 + i });
		cout << "|                  |";
	}

	for (int i = 0; i < players.size(); i++)
	{
		if (lose[i] == false)
		{
			SetColor(players[i].getColor());
			SetPosition({ 100, 11 + i * 7 });
			cout << players[i].getName();
			SetColor(7);

			SetPosition({ 101, 13 + i * 7 });
			cout << "$ " << players[i].getCash();


			SetPosition({ 96, 15 + i * 7 });
			cout << "__________________";
		}
		else
		{
			SetColor(128);
			for (int j = 0; j < 7; j++)
			{
				SetPosition({ 96, (7 * i + 9) + j });
				cout << "                  ";
				
			}
			SetPosition({ 100, 11 + i * 7 });
			cout << players[i].getName();
			SetPosition({ 101, 13 + i * 7 });
			cout << "�w�}��:(";
			SetColor(7);
		}
	}
	
    SetColor(7);
    SetPosition(temp);
}

void Game::updatePlayerUI()
{
	position temp = getCursorPosition();
	SetColor(7);
	for (int i = 0; i < players.size(); i++)
	{
		if (lose[i] == false)
		{
			SetPosition({ 103, 13 + i * 7 });
			cout << "                ";
			SetPosition({ 103, 13 + i * 7 });
			cout << players[i].getCash();
		}
		else
		{
			SetColor(128);
			for (int j = 0; j < 7; j++)
			{
				SetPosition({ 96, (7 * i + 9) + j });
				cout << "                  ";
			}
			SetPosition({ 100, 11 + i * 7 });
			cout << players[i].getName();
			SetPosition({ 101, 13 + i * 7 });
			cout << "�w�}��:(";
			SetColor(7);
		}
	}


	SetPosition(temp);
}



int Game::getRun()
{
    return run;
}

Map* Game::getMap()
{
    return &map;
}

void Game::endGame()
{
    continueGame = false;
}