#include "Map.h"

Map::Map()
{

}

Map::Map(vector<Block> mapContent, array<int, 4> playerPositionsInput)
{
	for (int i = 0; i <= mapContent.size() - 1; i++)
	{
		map.push_back(mapContent[i]);
	}
	playerPositions = playerPositionsInput;
	mapSize = mapContent.size();
}

Map::~Map()
{

}

void Map::updateMap()
{
	int length = ceil((float)(mapSize - 4) / 4) + 2;
	int width = (mapSize - length * 2) / 2 + 2;
	vector<vector<string>> output(width, vector<string>(length)); //width x length ���G�� vector
	for (int i = 0; i <= width - 1; i++) //���誺��
	{
		output[i][0] = map[i].toString();
	}
	for (int i = 0; i <= length - 1; i++) //�U�誺��
	{
		output[width - 1][i] = map[width + i].toString();
	}
	for (int i = 0; i <= width - 1; i++) //�k�誺��
	{
		output[width - 1 - i][length - 1] = map[width + length + i].toString();
	}
	for (int i = 0; i <= length - 2; i++) //�W�誺��
	{
		output[length - 1 - i][0] = map[width + length + width + i].toString();
	}
	for (int i = 0; i <= width - 1; i++) //�L�X output
	{
		for (int j = 0; j <= length - 1; j++)
		{
			cout << output[i][j];
		}
		cout << endl;
	}
}

void Map::setCertainPlayerPosition(int playerID, int newPosition)
{
	if (playerID < 0 || playerID > 3)
	{
		cout << "Invalid playerID" << endl;
		return;
	}
	else if (newPosition < 0 || newPosition > mapSize - 1)
	{
		cout << "Invalid newPosition" << endl;
		return;
	}
	else
	{
		playerPositions[playerID] = newPosition;
	}
}

int Map::getCertainPlayerPosition(int playerID)
{
	if (playerID < 0 || playerID > 3)
	{
		cout << "Invalid playerID" << endl;
		return -1;
	}
	else
	{
		return playerPositions[playerID];
	}
}

int Map::getMapSize()
{
	return mapSize;
}