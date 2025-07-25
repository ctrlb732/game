

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callbackѡ�����ص�
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually�ֶ�ʵ�֡���̬create����������
   CREATE_FUNC(HelloWorld);

private:
    // ���Menu��Ա����
    cocos2d::Menu* _menu;
};

#endif // __HELLOWORLD_SCENE_H__
