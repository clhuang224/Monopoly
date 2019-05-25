#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Block
{
public:
    Block(unsigned newPosition,
          string newName,
          int newType,
          vector<string> newSign = {},
          vector<unsigned> newPasserby = {});

    // ���o��l����
    // -2���| -1�R�B 0�_�I 1�Фl 2�Ȧ� 3�ʺ� 4��|
    // basemap.txt�̨S��2~4����l ���p�G�n�ۻs�a�ϴN�i�H��
    enum { CHANCE = -2, FORTUNE = -1, START = 0, HOUSE = 1, BANK = 2, PRISON = 3, HOSPITAL = 4 };
    int getType();

    // ���o��l�лx
    vector<string> getSign();

    // �]�w��l�лx
    void setSign(vector<string> newSign);

    // ���o��l�W��
    string getName();

	//�^�Ǿ�Ӯ�l
	string toString();

private:
    unsigned position;
    string name; // �̪��|�Ӧr
    int type;
    vector<string> sign; // 10x4
    vector<unsigned> passerby;

    /*
    ��l�榡�G
     __________
    |          |
    |##########|
    |##########|
    |##########|
    |##########|
    |�d �� �W ��|
    |��|��|��|��|
    |__________|

    */

};

#endif // !BLOCK_H