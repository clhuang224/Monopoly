#ifndef CHANCE_H
#define CHANCE_H
#include "Block.h"
#include "Player.h"
#include <cstdlib>
#include <time.h>

class Chance : public Block
{
public:
    Chance(unsigned newPosition, vector<unsigned> newPasserby = {});

    // ����|�õo�� �|�^�ǰT��
    string getChance(Player agent);
};

#endif