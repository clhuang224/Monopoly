#ifndef HOUSE_H
#define HOUSE_H

#include "Block.h"
class House :
    public Block
{
public:
    House(unsigned newPosition,
          string newName,
          unsigned newLevel = 0,
		  unsigned cost=0,
          vector<unsigned> newPriceList = {0,0,0,0},
          vector<unsigned> newPasserby = {},
          int newOwner = -1);

    // ���o��U����
    unsigned getLevel();

	// ���o��U����
	unsigned getPrice();

	// �]�w���� sign�]�|�H������
    void setLevel(unsigned newLevel);

	//�]�w�֦���
	void setOwner(int playerID);
private:
    unsigned level;
	//��l����S�ݨ���� �ۤv�[�W by���i
	unsigned cost_of_own;
    vector<unsigned> tollsList;
    int owner;
};

#endif // !HOUSE_H

