

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback选择器回调
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually手动实现“静态create（）”方法
   CREATE_FUNC(HelloWorld);

private:
    // 添加Menu成员变量
    cocos2d::Menu* _menu;
};

#endif // __HELLOWORLD_SCENE_H__
