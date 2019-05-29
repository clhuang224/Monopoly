#include "Game.h"

const int MAX_ROUND = 20;

//目的：讀取資料檔並建構地圖、玩家
Game::Game(string loadMapFile)
{
	fstream mapFile(loadMapFile);
	if(mapFile.is_open())
	{
		string mapName;
		vector<Block*> mapContent;
		array<int, 4> playerPositions = { -1,-1,-1,-1 };//最多4人

		//參照.txt第一列
		mapFile >> mapName >> remainingRound >> playerAmount;
		
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

		string playerID;
		int playerPosition, playerCash;
		while (getline(mapFile, commandTmp))
		{
			if (!commandTmp.empty())
			{
				stringstream commandLine(commandTmp);
				commandLine >> playerID >> playerPosition >> playerCash;
				playerPositions[stoi(playerID)] = playerPosition;
				//player這邊要給名子有點怪，需要再改
				Player playerTmp("Player"+playerID, playerPosition, playerCash);
				players.push_back(playerTmp);

				string house;
				unsigned int houseRank;
				//這邊改了map部分內house的 擁有者指標 以及 房屋等級
				while (commandLine >> house >> houseRank)
				{
					((House*)(mapContent[stoi(house)]))->setOwner(&players.back());
					((House*)(mapContent[stoi(house)]))->setLevel(houseRank);
				}
			}
		}
		Map mapTmp(mapContent, mapName);
		map = mapTmp;
	}
	else
	{
		//report alert?
	}
}
Game::~Game()
{
}

size_t Game::rollTheDice()
{
	size_t output = 0;
	srand((unsigned)time(NULL));
	output += (rand() % 6 + 1);
	return output;
}

void Game::printUI()
{
	SetPosition({ 0,0 });
	cout << "----------------------------------------------\n\n";
	//印人
	/*這裡待再監察*/
	for (Player i : players)
		i.printPlayer();

	cout << "----------------------------------------------\n";

	//待補印輪到誰&回合
	cout << "輪到："<<run << "            剩餘" << remainingRound<<"回合\n";

	cout << "----------------------------------------------\n";

	//印地圖
	/*地圖上的人物id印製建議Map使用函數調用來分開印製，不然每次印這麼多會閃爍*/
	array<int, 4> playerPositions;
	for (int i = 0; i < players.size(); i++)
		playerPositions[i] = players[i].getPosition();
	map.updateMap(playerPositions);

	/*這邊或map結尾可能缺一個游標位置設置，暫時用換行代替*/
	cout << "\n----------------------------------------------\n";
}

vector<Player> Game::getPlayers()
{
	return players;
}

void Game::runGame()
{
	setCursorVisable(false);
	printUI();

	while (true)
	{
		/*待補print回合數*/
		//cout << " 現在回合：" << MAX_ROUND - remainingRound << '\n';
		
		if (remainingRound > 0)
		{
			for (; run < players.size(); run++)//每回合執行(玩家數量)次
			{
				is_FinishRound = false;
				while (!is_FinishRound)//該玩家在這回合的所有操作
				{
					//操作銀行、買股票、骰骰子、Option內置選單鍵
					//骰完骰子就不可以再操作銀行、買股票
					/*option:BANK,STOCK,THROW_DICE*/
					Option(this, { "BANK","STOCK","THROW_DICE" });
					/*待補輸出訊息*/

					//丟骰子後，執行新位置上的效果
					if (is_FinishRound)
					{
						Block* block = map.getMap().at(players[run].getPosition());//讀取此玩家位置上的block指標
						if (block->getType() == HOUSE)
						{
							House* house = (House*)block;
							if (house->getOwner() == &bank)
							{
								cout << "這片土地尚未被圈佔，此地價格為" << house->getCostOfOwn()<<"\n";
								Option(this, { "BUY_FROM_BANK","NOT_BUY_FROM_BANK" });
								/*待補完整的輸出訊息*/

							}
							else if (house->getOwner() == &players[run])
							{
								cout << "這片土地是你的\n，目前房屋等級為" << house->getLevel() << "\n";
								Option(this, { "UPGRADE","KEEPNOW" });
							}
							else if (house->getOwner() != &players[run])
							{
								/*這邊好像有bug，會出現house->getOwner()->getName()=""*/
								cout << "這片土地屬於"<< house->getOwner()->getName()<<"，過路費為" << house->getPrice() << "\n";
								players[run].minusCash(house->getPrice());//現金交過路費
								house->getOwner()->setDeposit(house->getOwner()->getDeposit() + house->getPrice());//過路費存進銀行
								/*待補完整的輸出訊息*/
								cout << "\n";
								system("pause");
								printUI();
							}
							else
							{
								cout << "OH NO!";
								system("pause");
							}
						}
						if (block->getType() == CHANCE)
						{
							string message = Chance::getChance(&players[run]);
							printUI();
							cout << message << "\n";
							system("pause");
							printUI();
						}
						if (block->getType() == FORTUNE)
						{
							string message = Fortune::getFortune(&players[run]);
							printUI();
							cout << message << "\n";
							system("pause");
							printUI();
						}
					}
				}
			}
			
			remainingRound--;
			run = 0;
		}
		else
		{
			/*print 遊戲結束，誰贏了*/
			/*可以生成一張證書給優勝者???*/
			/*option 離開遊戲*/
		}
	}
}
