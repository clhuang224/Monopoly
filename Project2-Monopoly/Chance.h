#ifndef CHANCE_H
#define CHANCE_H
#include "Block.h"
#include <cstdlib>
#include <time.h>

class Chance : public Block
{
public:
    Chance(unsigned newPosition);

    // ����|�õo�� �|�^�ǰT��
    string getChance(Player agent);
};

#endif // !CHANCE_H