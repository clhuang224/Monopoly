#ifndef FORTUNE_H
#define FORTUNE_H
#include "Block.h"
#include <cstdlib>
#include <time.h>

class Fortune : public Block
{
public:
    Fortune(unsigned newPosition);

    // 抽命運並發生 會回傳訊息
    string getFortune(Player agent);
};

#endif // !FORTUNE_H