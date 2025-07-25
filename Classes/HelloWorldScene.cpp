

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "Views/CardView.h"
#include "Controllers/controllers.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.当文件不存在时，打印有用的错误消息，而不是分段错误。
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance在“init”上，您需要初始化您的实例
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first超级初始化优先
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
        // 将标签放在屏幕中央
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer将标签作为子标签添加到此图层
        this->addChild(label, 1);
    }




       




    auto cardView = CardView::create();
    this->addChild(cardView, 2);

    // 创建Controllers
      

    return true;
}








void HelloWorld::menuCloseCallback(Ref* pSender)
{
    // 获取被点击的菜单项(Club2图片)
    auto closeItem = static_cast<MenuItemImage*>(pSender);

    // 创建移动动作，1秒内移动到(300, 300)位置
    auto moveTo = MoveTo::create(1, Vec2(100, -100));

    // 让菜单项执行移动动作
    closeItem->runAction(moveTo);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif


    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}