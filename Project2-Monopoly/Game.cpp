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
				//這邊只改了map部分的房子擁有者id (int)
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
	srand(time(NULL));
	output += (rand() % 6 + 1);
	return output;
}

void Game::printUI()
{
	SetPosition({ 0,0 });
	cout << "----------------------------------------------\n\n";
	//印人
	/*這裡缺一段框框*/
	for (Player i : players)
		i.printPlayer();

	cout << "----------------------------------------------\n";

	//印輪到誰&回合

	cout << "----------------------------------------------\n";

	//印地圖
	/*地圖上的人物id印製建議Map使用函數調用來分開印製，不然每次印這麼多會閃爍*/
	array<int, 4> playerPositions;
	for (int i = 0; i < players.size(); i++)
		playerPositions[i] = players[i].getPosition();
	map.updateMap(playerPositions);

	/*這邊可能缺一個游標位置設置*/
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

	char keyin;
	while (true)
	{
		/*待補print回合數*/
		//cout << " 現在回合：" << MAX_ROUND - remainingRound << '\n';
		
		if (remainingRound > 0)
		{
			for (int correntPlayerID = 0; correntPlayerID < players.size(); correntPlayerID++)//每回合執行(玩家數量)次
			{
				is_FinishRound = false;
				while (!is_FinishRound)//該玩家在這回合的所有操作
				{
					//操作銀行、買股票、骰骰子、Option內置選單鍵
					//骰完骰子就結束回合
					/*option:BANK,STOCK,THROW_DICE*/
					Option(this, correntPlayerID, { "BANK","STOCK","THROW_DICE" });
					/*待補輸出訊息*/
				}
			}
			
			remainingRound--;
		}
		else
		{
			/*print 遊戲結束，誰贏了*/
			/*可以生成一張證書給優勝者???*/
			/*option 離開遊戲*/
		}
	}
}
