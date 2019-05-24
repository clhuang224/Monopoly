#ifndef CHANCE_H
#define CHANCE_H
#include "Block.h"
#include <cstdlib>
#include <time.h>

class Chance : public Block
{
public:
    Chance(unsigned newPosition);

    // 抽機會並發生 會回傳訊息
    string getChance(Player agent);
};

#endif // !CHANCE_H