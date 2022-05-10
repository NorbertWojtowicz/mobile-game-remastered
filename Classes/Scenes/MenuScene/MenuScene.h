#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method
    CREATE_FUNC(MenuScene);

    void switchToGameScene(Ref* pSender);
};

#endif // __MENU_SCENE_H__
