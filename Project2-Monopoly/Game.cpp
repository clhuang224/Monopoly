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
        //第一行
        savefile << map.getMapName() << " " << remainingRound << " " << playerAmount << "\n";
        //map區
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
        //player區
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
        /*文件創建or讀取失敗的敘述??*/
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
        array<int, 4> playerPositions = { -1,-1,-1,-1 };//最多4人

        //參照.txt第一列
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

                //存款部分
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
                //這邊改了map部分內house的 擁有者指標 以及 房屋等級
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

    //印地圖
    /*地圖上的人物id印製建議Map使用函數調用來分開印製，不然每次印這麼多會閃爍*/
    array<int, 4> playerPositions;
    for (int i = 0; i < players.size(); i++)
    {
        playerPositions[i] = players[i].getPosition();
    }
    map.updateMap(playerPositions);

    // 印角色資訊
    printPlayer();

    // 印剩餘回合數、輪到的玩家
    SetPosition({ 40,34 });
    SetColor(0x07);
    cout << "還有 ";
    SetColor(0x0B);
    cout << remainingRound;
    SetColor(0x07);
    cout << " 回合，輪到 ";
    SetColor(0x0B);
    cout << players[run].getName();
    SetColor(0x07);
    cout << " 。";

    // 印玩家所在位置
    SetPosition({ 44,35 });
    SetColor(0x0B);
    cout << players[run].getName();
    SetColor(0x07);
    cout << " 在 ";
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
    cout << " 。";

    // 印輪到誰的箭頭
    SetPosition({ 90, 12 + run * 7 });
    SetColor(0x0B);
    cout << "→";
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
            for (; run < players.size() && !restartFlag; run++)//每回合執行(玩家數量)次
            {
                if (lose[run])continue;//跳過輸家回合

                printUI();
                isFinishRound = false;

                while (!isFinishRound && !restartFlag)//該玩家在這回合的所有操作
                {
                    //操作銀行、買股票、骰骰子、Option內置選單鍵
                    //骰完骰子就不可以再操作銀行、買股票
                    Option(this, { "擲骰子","去銀行" });

                    //丟骰子後，執行新位置上的效果
                    while (isFinishRound == false)
                    {
                        //讀取此玩家位置上的block指標
                        Block* block = map.getMap().at(players[run].getPosition());
                        if (block->getType() == HOUSE)
                        {
                            House* house = (House*)block;
                            if (house->getOwner() == &bank)
                            {

                                Option(this,
                                       { "購買","不購買" },
                                       { house->getName() + "待售中，只要" + to_string(house->getCostOfOwn()) + "元！" });
                            }
                            else if (house->getOwner() == &players[run])
                            {
                                Option(this,
                                       { "確定" },
                                       { "這片土地是你的，目前房屋等級為" + to_string(house->getLevel()) + "級。" });

                                if (house->getLevel() < 3)
                                {
                                    Option(this,
                                           { "升級","不升級" },
                                           { "升級要花" + to_string(house->getPrice()) + "元，是否升級？" });
                                }
                                else
                                {
                                    Option(this, { "確定" }, { "你的" + house->getName() + "已經是最高級了！" });
                                }
                            }
                            else if (house->getOwner() != &players[run])
                            {
                                players[run].minusCash(house->getPrice());//現金交過路費
                                house->getOwner()->setDeposit(house->getOwner()->getDeposit() + house->getPrice());//過路費存進銀行
                                /*待補完整的輸出訊息*/
                                Option(this,
                                       { "確定" },
                                       { house->getName() + "屬於" + house->getOwner()->getName() + "。",
                                         "你支付過路費" + to_string(house->getPrice()) + "元。",
                                         "你還有" + to_string(players[run].getCash()) + "現金。" });
                                printUI();
                            }
                            isFinishRound = true;
                        }
                        else if (block->getType() == CHANCE)
                        {
                            Option(this, { "確定" }, { Chance::getChance(&players[run]) });
                            printUI();
                            break;
                        }
                        else if (block->getType() == FORTUNE)
                        {
                            Option(this, { "確定" }, { Fortune::getFortune(&players[run]) });
                            printUI();
                        }
                    }
                }
                //破產宣告
                if (players[run].getCash() < 0)
                {
                    players[run].setCash(-1);
                    lose[run] = true;
                    Option(this, { "確定" }, { players[run].getName() + "已破產！！" });
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
            /*print 遊戲結束，誰贏了*/
            /*可以生成一張證書給優勝者???*/
            /*option 離開遊戲*/
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