#pragma once
class Block
{
public:
    Block(unsigned, unsigned);
    unsigned getType();
    virtual void printSign() = 0;
	string toString();
	/*toString() �榡: 
	 _ _ _ _ 
	|�d�ҦW��|
	|1|2|3|4|
	| _ _ _ |
	*/
private:
    unsigned position;
    enum {BANK,PRISON,CHANCE,FORTUNE};
    // 0 �Ȧ� 1�ʺ� 2���| 3�R�B 4~n�Фl
    // ��ڽs���ݤ��A��
    int type;
};