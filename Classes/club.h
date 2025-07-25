
#ifndef _club_H_
#define _club_H_

#include "cocos2d.h"

USING_NS_CC;

class MoveImage : public Scene {
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MoveImage);

    void menuItemCallback(Ref* sender);
};

#endif // _club_H_
