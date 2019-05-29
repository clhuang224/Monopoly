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

    // ��R�B�õo�� �|�^�ǰT��
	static string getFortune(Player* agent);
};

#endif