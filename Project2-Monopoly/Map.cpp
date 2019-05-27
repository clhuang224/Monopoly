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

void Map::updateMap()
{
	//找出最接近正方形的長和寬，且長 >= 寬
	int length = ceil((float)(mapSize - 4) / 4) + 2;
	int width = (mapSize - length * 2) / 2 + 2;
	//cout << "length: " << length << endl << "width: " << width << endl;
	vector<vector<string>> output(width, vector<string>(length)); //width x length 的二維 vector
	for (int i = 0; i <= width - 1; i++) //初始化 output
	{
		for (int j = 0; j <= length - 1; j++)
		{
			output[i][j] = "XXXXXXXXXXXX\n"
						   "X          X\n"
						   "X          X\n"
						   "X          X\n"
						   "X          X\n"
						   "X          X\n"
						   "X          X\n"
						   "X          X\n"
						   "XXXXXXXXXXXX\n";
		}
	}
	for (int i = 0; i <= width - 1; i++) //左方的 Block
	{
		output[i][0] = map[i]->toString();
	}
	for (int i = 1; i <= length - 1; i++) //下方的 Block
	{
		output[width - 1][i] = map[width - 1 + i]->toString();
	}
	for (int i = 1; i <= width - 1; i++) //右方的 Block
	{
		output[width - 1 - i][length - 1] = map[width - 1 + length - 1 + i]->toString();
	}
	for (int i = 1; i <= length - 2; i++) //上方的 Block
	{
		output[0][length - 1 - i] = map[width - 1 + length - 1 + width - 1 + i]->toString();
	}
	for (int i = 0; i <= width - 1; i++) //印出 output
	{
		for (int j = 0; j <= length - 1; j++)
		{
			setConsoleCursorPosition(13 * j, 9 * i);
			cout << output[i][j];
			//cout << getConsoleCursorPosition().X << " " << getConsoleCursorPosition().Y;
			/*position temp = getCursorPosition();
			temp.y = temp.y - 8;
			SetPosition(temp);*/
		}
		//setConsoleCursorPosition(0, getConsoleCursorPosition().Y + 10);
		//cout << endl;
	}
	//cout << "length: " << length << endl << "width: " << width << endl;
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

vector<Block*> Map::getMap()
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