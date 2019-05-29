#include "Map.h"

Map::Map()
{

}

Map::Map(const Map& m)
{
	map = m.map;
	mapSize = m.mapSize;
	mapName = m.mapName;
}

Map::Map(vector<Block*> mapContent, string name)
{
	map = mapContent;
	mapSize = mapContent.size();
	mapName = name;
}

Map::~Map()
{

}

void Map::operator=(Map rhs)
{
	map = rhs.getMap();
	mapSize = rhs.getMapSize();
	mapName = rhs.getMapName();
}

void Map::updateMap(array<int, 4> playerPositions)
{
	//找出最接近正方形的長和寬，且長 >= 寬
	int length;
	if (mapSize >= 24)
	{
		length = 11;
	}
	else
	{
		length = ceil((float)(mapSize - 4) / 4) + 2;
	}
	int width = (mapSize - length * 2) / 2 + 2;
	//cout << "length: " << length << endl << "width: " << width << endl;
	vector<vector<string>> output(width, vector<string>(length)); //width x length 的二維 vector
	for (int i = 0; i <= width - 1; i++) //初始化 output
	{
		for (int j = 0; j <= length - 1; j++)
		{
			output[i][j] = "            "
						   "            "
						   "            "
						   "            "
						   "            "
						   "            "
						   "            "
						   "            "
						   "            ";
		}
	}
	for (int i = 0; i <= map.size() - 1; i++) //重置玩家位置
	{
		map[i]->setOutput(-1);
	}

	//插入玩家位置
	map[playerPositions[0]]->setOutput(1);
	map[playerPositions[1]]->setOutput(2);
	map[playerPositions[2]]->setOutput(3);
	map[playerPositions[3]]->setOutput(4);

	for (int i = 0; i <= width - 1; i++) //左方的 Block
	{
		output[i][0] = map[i]->getOutput();
	}
	for (int i = 1; i <= length - 1; i++) //下方的 Block
	{
		output[width - 1][i] = map[width - 1 + i]->getOutput();
	}
	for (int i = 1; i <= width - 1; i++) //右方的 Block
	{
		output[width - 1 - i][length - 1] = map[width - 1 + length - 1 + i]->getOutput();
	}
	for (int i = 1; i <= length - 2; i++) //上方的 Block
	{
		output[0][length - 1 - i] = map[width - 1 + length - 1 + width - 1 + i]->getOutput();
	}
	for (int i = 0; i <= width - 1; i++) //印出 output
	{
		for (int j = 0; j <= length - 1; j++)
		{
			for (int k = 0; k <= 8; k++) //一個 Block
			{
				for (int l = 0; l <= 11; l++)
				{
					cout << output[i][j][12 * k + l];
				}
				setConsoleCursorPosition(getConsoleCursorPosition().X - 12, getConsoleCursorPosition().Y + 1);
			}
			setConsoleCursorPosition(getConsoleCursorPosition().X + 12, getConsoleCursorPosition().Y - 9);
		}
		setConsoleCursorPosition(0, getConsoleCursorPosition().Y + 9);
	}
}

void Map::setConsoleCursorPosition(int x, int y)
{
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

COORD Map::getConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
	return cbsi.dwCursorPosition;
}

vector<Block*> &Map::getMap()
{
	return map;
}

void Map::setMapSize(int mapSizeInput)
{
	mapSize = mapSizeInput;
}

int Map::getMapSize()
{
	return mapSize;
}

void Map::setMapName(string mapNameInput)
{
	mapName = mapNameInput;
}

string Map::getMapName()
{
	return mapName;
}