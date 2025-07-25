

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "Views/CardView.h"
#include "Controllers/controllers.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.���ļ�������ʱ����ӡ���õĴ�����Ϣ�������Ƿֶδ���
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance�ڡ�init���ϣ�����Ҫ��ʼ������ʵ��
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first������ʼ������
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    auto label = Label::createWithTTF("youxi", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // ����ǩ������Ļ����
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer����ǩ��Ϊ�ӱ�ǩ��ӵ���ͼ��
        this->addChild(label, 1);
    }




       




    auto cardView = CardView::create();
    this->addChild(cardView, 2);

    // ����Controllers
      

    return true;
}








void HelloWorld::menuCloseCallback(Ref* pSender)
{
    // ��ȡ������Ĳ˵���(Club2ͼƬ)
    auto closeItem = static_cast<MenuItemImage*>(pSender);

    // �����ƶ�������1�����ƶ���(300, 300)λ��
    auto moveTo = MoveTo::create(1, Vec2(100, -100));

    // �ò˵���ִ���ƶ�����
    closeItem->runAction(moveTo);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif


    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}