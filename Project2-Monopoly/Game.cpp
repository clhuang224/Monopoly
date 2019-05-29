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
				//�o���Fmap������house�� �֦��̫��� �H�� �Ыε���
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
	//�L�H
	/*�o�̫ݦA�ʹ�*/
	for (Player i : players)
		i.printPlayer();

	cout << "----------------------------------------------\n";

	//�ݸɦL�����&�^�X
	cout << "����G"<<run << "            �Ѿl" << remainingRound<<"�^�X\n";

	cout << "----------------------------------------------\n";

	//�L�a��
	/*�a�ϤW���H��id�L�s��ĳMap�ϥΨ�ƽեΨӤ��}�L�s�A���M�C���L�o��h�|�{�{*/
	array<int, 4> playerPositions;
	for (int i = 0; i < players.size(); i++)
		playerPositions[i] = players[i].getPosition();
	map.updateMap(playerPositions);

	/*�o���map�����i��ʤ@�Ӵ�Ц�m�]�m�A�Ȯɥδ���N��*/
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
		/*�ݸ�print�^�X��*/
		//cout << " �{�b�^�X�G" << MAX_ROUND - remainingRound << '\n';
		
		if (remainingRound > 0)
		{
			for (; run < players.size(); run++)//�C�^�X����(���a�ƶq)��
			{
				is_FinishRound = false;
				while (!is_FinishRound)//�Ӫ��a�b�o�^�X���Ҧ��ާ@
				{
					//�ާ@�Ȧ�B�R�Ѳ��B���l�BOption���m�����
					//�맹��l�N���i�H�A�ާ@�Ȧ�B�R�Ѳ�
					/*option:BANK,STOCK,THROW_DICE*/
					Option(this, { "BANK","STOCK","THROW_DICE" });
					/*�ݸɿ�X�T��*/

					//���l��A����s��m�W���ĪG
					if (is_FinishRound)
					{
						Block* block = map.getMap().at(players[run].getPosition());//Ū�������a��m�W��block����
						if (block->getType() == HOUSE)
						{
							House* house = (House*)block;
							if (house->getOwner() == &bank)
							{
								cout << "�o���g�a�|���Q����A���a���欰" << house->getCostOfOwn()<<"\n";
								Option(this, { "BUY_FROM_BANK","NOT_BUY_FROM_BANK" });
								/*�ݸɧ��㪺��X�T��*/

							}
							else if (house->getOwner() == &players[run])
							{
								cout << "�o���g�a�O�A��\n�A�ثe�Ыε��Ŭ�" << house->getLevel() << "\n";
								Option(this, { "UPGRADE","KEEPNOW" });
							}
							else if (house->getOwner() != &players[run])
							{
								/*�o��n����bug�A�|�X�{house->getOwner()->getName()=""*/
								cout << "�o���g�a�ݩ�"<< house->getOwner()->getName()<<"�A�L���O��" << house->getPrice() << "\n";
								players[run].minusCash(house->getPrice());//�{����L���O
								house->getOwner()->setDeposit(house->getOwner()->getDeposit() + house->getPrice());//�L���O�s�i�Ȧ�
								/*�ݸɧ��㪺��X�T��*/
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
			/*print �C�������A��Ĺ�F*/
			/*�i�H�ͦ��@�i�Үѵ��u�Ӫ�???*/
			/*option ���}�C��*/
		}
	}
}
