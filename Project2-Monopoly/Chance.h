#ifndef CHANCE_H
#define CHANCE_H
#include "Block.h"
#include <cstdlib>
#include <time.h>

extern class Player;

class Chance : public Block
{
public:
    Chance(unsigned newPosition, vector<unsigned> newPasserby = {});

    // ����|�õo�� �|�^�ǰT��
    static string getChance(Player* agent);
};

#endif