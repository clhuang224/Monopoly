#ifndef FORTUNE_H
#define FORTUNE_H
#include "Block.h"
#include <cstdlib>
#include <time.h>

extern class Player;

class Fortune : public Block
{
public:
    Fortune(unsigned newPosition, vector<unsigned> newPasserby = {});

    // 抽命運並發生 會回傳訊息
	static string getFortune(Player* agent);
};

#endif