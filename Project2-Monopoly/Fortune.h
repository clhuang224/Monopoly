#ifndef FORTUNE_H
#define FORTUNE_H
#include "Block.h"
#include <cstdlib>
#include <time.h>

class Fortune : public Block
{
public:
    Fortune(unsigned newPosition);

    // ��R�B�õo�� �|�^�ǰT��
    string getFortune(Player agent);
};

#endif // !FORTUNE_H