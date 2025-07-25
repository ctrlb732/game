
#include "club.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;


Scene* MoveImage::createScene() {
    return MoveImage::create();
}

bool MoveImage::init() {
    if (!Scene::init()) {
        return false;
    }

    // 创建MenuItemImage
    auto menuItem = MenuItemImage::create(
        "Club2.png",
        "Club2.png",
        CC_CALLBACK_1(MoveImage::menuItemCallback, this)
    );

    menuItem->setPosition(Vec2(100, 100));

    // 创建Menu并添加MenuItem
    auto menu = Menu::create(menuItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void MoveImage::menuItemCallback(Ref* sender) {
    auto menuItem = static_cast<MenuItemImage*>(sender);

    // 创建移动到目标位置的动作
    auto moveTo = MoveTo::create(1.0f, Vec2(300, 300));

    // 添加缓动效果
    auto easeAction = EaseInOut::create(moveTo, 2.0f);

    // 执行动作
    menuItem->runAction(easeAction);
   
}