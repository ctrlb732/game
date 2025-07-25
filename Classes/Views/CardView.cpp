#include "CardView.h"
#include "cocos2d.h"

USING_NS_CC;

bool CardView::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 启用触摸事件
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CardView::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // 初始化选中精灵指针
    _selectedSprite = nullptr;
    _baseSprite = nullptr;
    _undoButton = nullptr; // 初始化回退按钮
    _currentMaxZOrder = 3; // 初始化最大层级值，确保高于初始卡片的层级(1)
    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->setPosition(Vec2::ZERO);

    // 创建9张卡片
    createCardSprite("ClubK.png", Vec2(origin.x+20, origin.y+240));
    createCardSprite("Club3.png", Vec2(origin.x+150, origin.y + 240));
    createCardSprite("Club3.png", Vec2(origin.x+40, origin.y + 220));
    createCardSprite("Club3.png", Vec2(origin.x+130, origin.y+220));
    createCardSprite("Diamond3.png", Vec2(origin.x + 60, origin.y + 200));
    createCardSprite("Spade2.png", Vec2(origin.x + 110, origin.y + 200));
    createCardSprite("Club3.png", Vec2(origin.x + 20, origin.y + 100));
    createCardSprite("HeartA.png", Vec2(origin.x + 40, origin.y + 100));
    createCardSprite("Club4.png", Vec2(origin.x + 110, origin.y + 100));
    
    // 创建回退按钮
    createUndoButton();
    // createCardSprite("Club4.png", Vec2(origin.x + 110, origin.y + 100));

    // 设置基准卡片（最上层图片）
    for (auto sprite : _cardSprites)
   {
        Vec2 pos = sprite->getPosition();
        if (pos.x == origin.x + 110 && pos.y == origin.y + 100) 
        {

            _baseSprite = sprite;
            _basePosition = pos;
           
            break;
        }
    }

    return true;
}

void CardView::createCardSprite(const std::string& filename, const Vec2& position)
{
    // 创建精灵
    auto sprite = Sprite::create(filename);
    if (sprite)
    {
        // 设置位置
        sprite->setPosition(position);
        // 添加到当前层
        this->addChild(sprite, 1);
        // 存储精灵
        _cardSprites.push_back(sprite);
        // 存储精灵和文件名的映射关系
        _spriteToFilename[sprite] = filename;
        // 存储精灵的初始位置
        _originalPositions[sprite] = position;
    }
    else
    {
        CCLOG("Error loading image: %s", filename.c_str());
    }
    
}

std::vector<Sprite*> CardView::getCardSprites() const
{
    return _cardSprites;
}

CardView* CardView::create()
{
    CardView* ret = new (std::nothrow) CardView();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// 触摸事件处理函数实现
bool CardView::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 touchLocation = touch->getLocation();

    // 检查触摸位置是否在某个卡片上
    for (auto sprite : _cardSprites)
    {
        if (sprite->getBoundingBox().containsPoint(touchLocation))
        {
            _selectedSprite = sprite;
            // 将选中的卡片移到最上层
           sprite->setLocalZOrder(2);
            return true;
        }
    }
    return false;
}



void CardView::onTouchEnded(Touch* touch, Event* event)
{
    // 获取触摸位置
    Vec2 touchLocation = touch->getLocation();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 检查触摸的y坐标是否为origin.y + 100
    if (abs(touchLocation.y - (origin.y + 100)) < 10)
    {
        if (_selectedSprite)
        {
            // 记录移动前的位置到历史栈
            _moveHistory.push_back(std::make_pair(_selectedSprite, _selectedSprite->getPosition()));
            
            // 移动精灵到新位置
            auto move = MoveTo::create(0.5, Vec2(origin.x + 110, origin.y + 100));
            _selectedSprite->runAction(move);

            Sprite* tempSelectedSprite1 = _selectedSprite;
           // _baseSprite->setLocalZOrder(1);
            _baseSprite = tempSelectedSprite1;
            _currentMaxZOrder++;
            _baseSprite->setLocalZOrder(_currentMaxZOrder); // 使用递增的层级值
        }
    }
    else if (_selectedSprite && _baseSprite && _selectedSprite != _baseSprite)
    {
        // 获取选中卡片和基准卡片的文件名
        std::string selectedFilename = getFilenameForSprite(_selectedSprite);
        std::string baseFilename = getFilenameForSprite(_baseSprite);

        // 提取文件名中的数字
        int selectedNum = extractNumberFromFilename(selectedFilename);
        int baseNum = extractNumberFromFilename(baseFilename);

        // 检查数字是否相差1
        if (abs(selectedNum - baseNum) == 1)
        {
            // 记录移动前的位置到历史栈
            _moveHistory.push_back(std::make_pair(_selectedSprite, _selectedSprite->getPosition()));
            
            // 保存当前选中的精灵指针
            Sprite* tempSelectedSprite = _selectedSprite;

            Vec2 origin1 = Director::getInstance()->getVisibleOrigin();
            
            // 数字相差1，移动到基准卡片位置
            auto move = MoveTo::create(0.5, Vec2(origin1.x + 110, origin1.y + 100));
            // 创建回调函数，在移动完成后将该卡片设为基准卡片
            auto callFunc = CallFunc::create([this, tempSelectedSprite]() 
                {
                // 将原基准卡片层级降低
                //_baseSprite->setLocalZOrder(1);
                // 更新基准卡片指针
                _baseSprite = tempSelectedSprite;
                // 确保新基准卡片在最上层
                _currentMaxZOrder++;
                _baseSprite->setLocalZOrder(_currentMaxZOrder); // 使用递增的层级值
            
            });
            // 按顺序执行移动和回调
            _selectedSprite->runAction(Sequence::create(move, callFunc, nullptr));
        }
    
        _selectedSprite = nullptr;
    }
    // 如果不满足上述条件，重置选中精灵
    else
    {
        _selectedSprite = nullptr;
    }
}
std::string CardView::getFilenameForSprite(Sprite* sprite)
{
    auto it = _spriteToFilename.find(sprite);
    if (it != _spriteToFilename.end())
    {
        return it->second;
    }
    return"";
}

// 从文件名中提取数字
int CardView::extractNumberFromFilename(const std::string& filename) {

    // 处理特殊字符（A, J, Q, K）
    if (filename.find('A') != std::string::npos) return 1;
    if (filename.find('J') != std::string::npos) return 11;
    if (filename.find('Q') != std::string::npos) return 12;
    if (filename.find('K') != std::string::npos) return 13;

    size_t start = filename.find_first_of("0123456789");
    size_t end = filename.find_last_of("0123456789");
    if (start != std::string::npos && end != std::string::npos && start <= end) {
        std::string numStr = filename.substr(start, end - start + 1);
        return std::stoi(numStr);
    }
    return -1; // 无法提取数字
}

// 创建回退按钮
void CardView::createUndoButton()
{
    // 创建回退按钮（使用CloseNormal.png作为图标）
    _undoButton = Sprite::create("CloseNormal.png");
    if (_undoButton)
    {
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Size visibleSize = Director::getInstance()->getVisibleSize();
        
        // 设置按钮位置（右上角）
        _undoButton->setPosition(Vec2(origin.x + 130, origin.y + 50));
        this->addChild(_undoButton, 4); // 确保按钮在最上层
        
        // 添加点击事件
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [this](Touch* touch, Event* event) {
            if (_undoButton->getBoundingBox().containsPoint(touch->getLocation())) {
                onUndoButtonClicked(nullptr);
                return true;
            }
            return false;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _undoButton);
    }
}

//回退按钮点击事件处理
void CardView::onUndoButtonClicked(Ref* pSender)
{
    // 检查历史栈是否为空
    if (_moveHistory.empty())
    {
        return; // 没有可回退的操作
    }
    
    // 弹出最后一次操作
    auto lastMove = _moveHistory.back();
    _moveHistory.pop_back();
    
    Sprite* sprite = lastMove.first;
    Vec2 previousPos = lastMove.second;
    
    // 将精灵移回之前的位置
    auto move = MoveTo::create(0.5, previousPos);
    sprite->runAction(move);
    
    // 如果这个精灵是基准卡片，需要更新基准卡片
    if (sprite == _baseSprite)
    {
        // 将原基准卡片层级降低
        sprite->setLocalZOrder(1);
        
        // 重置基准卡片
        _baseSprite = nullptr;
        
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 targetPos = Vec2(origin.x + 110, origin.y + 100);
        
        // 重新寻找位于目标位置的基准卡片
        for (auto s : _cardSprites)
        {
            Vec2 pos = s->getPosition();
            if (abs(pos.x - targetPos.x) < 10 && abs(pos.y - targetPos.y) < 10 && s != sprite)
            {
                _baseSprite = s;
                _baseSprite->setLocalZOrder(3);
                break;
            }
        }
    }
}

