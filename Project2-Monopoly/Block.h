#pragma once
class Block
{
public:
    Block(unsigned, unsigned);
    unsigned getType();
    virtual void printSign() = 0;
private:
    unsigned position;
    enum {BANK,PRISON,CHANCE,FORTUNE};
    // 0 銀行 1監獄 2機會 3命運 4~n房子
    // 實際編號看文件再改
    int type;
};

