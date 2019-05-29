#include "Fortune.h"
#include "Player.h"

// Intent: 初始化
// Pre: 位置
// Post: 初始化完成
Fortune::Fortune(unsigned newPosition, vector<unsigned> newPasserby)
    : Block(newPosition, "命運", -1, { "  ◢█◣  ",
                                       "  █  █  ",
                                       "    ◢◤  ",
                                       "    ▅    " }, newPasserby)
{
    srand(static_cast<unsigned>(time(NULL)));
}

Fortune::Fortune(Fortune& another)
    : Block(another.getPosition(), "命運", -1, { "  ◢█◣  ",
                                                 "  █  █  ",
                                                 "    ◢◤  ",
                                                 "    ▅    " }, another.getPasserby())
{
}

Fortune& Fortune::operator=(Fortune another)
{
    setPosition(another.getPosition());
    setName(another.getName());
    setType(another.getType());
    setSign(another.getSign());
    setPasserby(another.getPasserby());

    return (*this);
}

// Intent: 抽命運
// Pre: 玩家
// Post: 回傳訊息
string Fortune::getFortune(Player* agent)
{
    string message;
    switch (rand() % 3)
    {
    case 0:
		/*不確定需不需要補上退後三步的購買空地or收過路費???目前沒有*/
        agent->setPosition(agent->getPosition()-3);
        message = "遇上土石流，後退三格";
        break;
    case 1:
        // 使用者用圖形介面選格子之類的
        //agent->setPosition(newPosition);
        message = "遇到大神帶路，移動至想要的地區";
        break;
    case 2:
        //agent->setPosition(randomPosition);
        message = "撞上時空門，隨機傳送";
        break;
    }
    return message;
}
