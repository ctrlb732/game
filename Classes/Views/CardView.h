#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "cocos2d.h"
#include <vector>
#include <map>  // 新增：包含map头文件

USING_NS_CC;

class CardView : public Layer
{
public:
    static CardView* create();
    virtual bool init() override;
    std::vector<Sprite*> getCardSprites() const;

    // 添加触摸事件处理函数声明
    virtual bool onTouchBegan(Touch* touch, Event* event) override;
    virtual void onTouchEnded(Touch* touch, Event* event) override;

private:
    void createCardSprite(const std::string& filename, const Vec2& position);
    std::vector<Sprite*> _cardSprites;
    Sprite* _selectedSprite; // 存储当前选中的精灵
    std::map<Sprite*, std::string> _spriteToFilename; // 存储精灵和文件名的映射
    std::string getFilenameForSprite(Sprite* sprite); // 获取精灵对应的文件名
    Sprite* _baseSprite; // 基准卡片精灵
    Vec2 _basePosition; // 基准卡片位置
    int extractNumberFromFilename(const std::string& filename); // 从文件名提取数字
    
    // 回退按钮相关
    Sprite* _undoButton; // 回退按钮
    std::map<Sprite*, Vec2> _originalPositions; // 存储精灵移动前的位置
    std::vector<std::pair<Sprite*, Vec2>> _moveHistory; // 移动操作历史栈
    int _currentMaxZOrder; // 新增：跟踪当前最大层级值
    void createUndoButton(); // 创建回退按钮
    void onUndoButtonClicked(Ref* pSender); // 回退按钮点击事件处理
};

#endif // CARDVIEW_H