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
	//找出最接近正方形的長和寬，且長 >= 寬
	int length = ceil((float)(mapSize - 4) / 4) + 2;
	int width = (mapSize - length * 2) / 2 + 2;
	vector<vector<string>> output(width, vector<string>(length)); //width x length 的二維 vector
	for (int i = 0; i <= width - 1; i++) //初始化 output
	{
		for (int j = 0; j <= length - 1; j++)
		{
			output[i][j] = "            \n"
						   "            \n"
						   "            \n"
						   "            \n"
						   "            \n"
						   "            \n"
						   "            \n"
						   "            \n"
						   "            ";
		}
	}
	for (int i = 0; i <= width - 1; i++) //左方的 Block
	{
		output[i][0] = map[i].toString();
	}
	for (int i = 0; i <= length - 1; i++) //下方的 Block
	{
		output[width - 1][i] = map[width + i].toString();
	}
	for (int i = 0; i <= width - 1; i++) //右方的 Block
	{
		output[width - 1 - i][length - 1] = map[width + length + i].toString();
	}
	for (int i = 0; i <= length - 2; i++) //上方的 Block
	{
		output[length - 1 - i][0] = map[width + length + width + i].toString();
	}
	for (int i = 0; i <= width - 1; i++) //印出 output
	{
		for (int j = 0; j <= length - 1; j++)
		{
			cout << output[i][j];
			setConsoleCursorPosition(getConsoleCursorPosition().X, getConsoleCursorPosition().Y - 8);
		}
		cout << endl;
	}
}

void Map::setConsoleCursorPosition(int x, int y)
{
	COORD coordinates = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

COORD Map::getConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
	return cbsi.dwCursorPosition;
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