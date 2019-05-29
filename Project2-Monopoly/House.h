#ifndef HOUSE_H
#define HOUSE_H
#include "Block.h"

extern class Player;

class House :
    public Block
{
public:
    House(unsigned newPosition,
          string newName,
		  Player* newOwner,
		  unsigned newLevel = 0,
		  unsigned cost=0,
          vector<unsigned> newPriceList = {0,0,0,0},
          vector<unsigned> newPasserby = {}
          );

    // ���o��U����
    unsigned getLevel();

	// ���o��U����
	unsigned getPrice();

	//���o�ʶR�Ŧa������
	unsigned getCostOfOwn();

	//���o�֦���
	Player* getOwner();

	// �]�w���� sign�]�|�H������
    void setLevel(unsigned newLevel);

	//�]�w�֦���
	void setOwner(Player*);

	//���o���O�M�� �g�ɥ�
	vector<unsigned> getTollsList();
private:
    unsigned level;
	//��l����S�ݨ���� �ۤv�[�W by���i
	unsigned cost_of_own;
    vector<unsigned> tollsList;
	Player* owner;
};

#endif

