#ifndef FORTUNE_H
#define FORTUNE_H
#include "Block.h"
#include "player.h"
#include <cstdlib>
#include <time.h>

class Fortune : public Block
{
public:
    Fortune(unsigned newPosition, vector<unsigned> newPasserby = {});

    // ��R�B�õo�� �|�^�ǰT��
    string getFortune(Player agent);
};

#endif