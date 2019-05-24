#include "Fortune.h"

// Intent: 初始化
// Pre: 位置
// Post: 初始化完成
Fortune::Fortune(unsigned newPosition)
    : Block(newPosition, "命運", -1, { "  ◢█◣  ",
                                       "  █  █  ",
                                       "    ◢◤  ",
                                       "    ▅    " })
{
    srand(static_cast<unsigned>(time(NULL)));
}

// Intent: 抽命運
// Pre: 玩家
// Post: 回傳訊息
string Fortune::getFortune(Player agent)
{
    switch ((rand() % 3))
    {
    case 0:
        agent.setPosition(agent.getPosition()-3);
        return "遇上土石流，後退三格";
    case 1:
        // 使用者用圖形介面選格子之類的
        // agent.setPosition(newPosition);
        return "遇到大神帶路，移動至想要的地區";
    case 2:
        // agent.setPosition(randomPosition);
        return "撞上時空門，隨機傳送";
    }
}
