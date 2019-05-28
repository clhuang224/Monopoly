#include "Game.h"

const int MAX_ROUND = 20;

//�ت��GŪ������ɨëغc�a�ϡB���a
Game::Game(string loadMapFile)
{
	fstream mapFile(loadMapFile);
	if(mapFile.is_open())
	{
		string mapName;
		vector<Block*> mapContent;
		array<int, 4> playerPositions = { -1,-1,-1,-1 };//�̦h4�H

		//�ѷ�.txt�Ĥ@�C
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
				//player�o��n���W�l���I�ǡA�ݭn�A��
				Player playerTmp("Player"+playerID, playerPosition, playerCash);
				players.push_back(playerTmp);
				string house;
				unsigned int houseRank;
				//�o��u��Fmap�������Фl�֦���id (int)
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
	//�L�H
	/*�o�̯ʤ@�q�خ�*/
	for (Player i : players)
		i.printPlayer();

	cout << "----------------------------------------------\n";

	//�L�����&�^�X

	cout << "----------------------------------------------\n";

	//�L�a��
	/*�a�ϤW���H��id�L�s��ĳMap�ϥΨ�ƽեΨӤ��}�L�s�A���M�C���L�o��h�|�{�{*/
	array<int, 4> playerPositions;
	for (int i = 0; i < players.size(); i++)
		playerPositions[i] = players[i].getPosition();
	map.updateMap(playerPositions);

	/*�o��i��ʤ@�Ӵ�Ц�m�]�m*/
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
		/*�ݸ�print�^�X��*/
		//cout << " �{�b�^�X�G" << MAX_ROUND - remainingRound << '\n';
		
		if (remainingRound > 0)
		{
			for (int correntPlayerID = 0; correntPlayerID < players.size(); correntPlayerID++)//�C�^�X����(���a�ƶq)��
			{
				is_FinishRound = false;
				while (!is_FinishRound)//�Ӫ��a�b�o�^�X���Ҧ��ާ@
				{
					//�ާ@�Ȧ�B�R�Ѳ��B���l�BOption���m�����
					//�맹��l�N�����^�X
					/*option:BANK,STOCK,THROW_DICE*/
					Option(this, correntPlayerID, { "BANK","STOCK","THROW_DICE" });
					/*�ݸɿ�X�T��*/
				}
			}
			
			remainingRound--;
		}
		else
		{
			/*print �C�������A��Ĺ�F*/
			/*�i�H�ͦ��@�i�Үѵ��u�Ӫ�???*/
			/*option ���}�C��*/
		}
	}
}
