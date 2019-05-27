#include "Game.h"


Game::Game(string loadMapFile)
{
	fstream mapFile(loadMapFile);
	if(mapFile.is_open())
	{
		string mapName;
		vector<Block&> mapContent;
		array<int, 4> playerPositions;

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
				Start &blockTmp = *(new Start((unsigned int)position));
				mapContent.push_back(blockTmp);
			}
			if (blockType == HOUSE)
			{
				vector<unsigned> price;
				int cost;
				price.resize(4);
				mapFile >> cost >> price[0] >> price[1] >> price[2] >> price[3];
				House &blockTmp = *(new House((unsigned int)position, blockName, 0, cost, price, vector<unsigned>(), -1));
				mapContent.push_back(blockTmp);
			}
			if (blockType == CHANCE)
			{
				Chance &blockTmp = *(new Chance((unsigned int)position, vector<unsigned>()));
				mapContent.push_back(blockTmp);
			}
			if (blockType == FORTUNE)
			{
				Fortune &blockTmp = *(new Fortune((unsigned int)position, vector<unsigned>()));
				mapContent.push_back(blockTmp);
			}
		}
		
		mapFile >> run;

		int playerID, playerPosition, playerCash;
		while (getline(cin, commandTmp))
		{
			if (!commandTmp.empty())
			{
				stringstream commandLine(commandTmp);
				commandLine >> playerID >> playerPosition >> playerCash;
				playerPositions[playerID] = playerPosition;
				//player這邊要給名子有點怪，這邊先用id轉，需要再改
				Player playerTmp(to_string(playerID), playerPosition, playerCash);
				string house;
				int houseRank;
				//這邊只改了map部分的房子擁有者id (int)
				while (commandLine >> house >> houseRank)
				{
					mapContent[stoi(house)].setOwner();
					mapContent[stoi(house)].setLevel(houseRank);
					playerTmp.setOwnHouse(mapContent)
				}
			}
		}
		Map mapTmp(mapContent, playerPositions, mapName);
		//待補Map複製建構子
		//map = mapTmp;
	}
	else
	{
		//report alert?
	}
}
Game::~Game()
{
}

size_t Game::rollTheDice(size_t amount)
{
	size_t output = 0;
	srand(time(NULL));
	for (int i = 0; i < amount; i++)output += (rand() % 6 + 1);
	return output;
}

void Game::printUI()
{
}
