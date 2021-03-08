#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto playItem = MenuItemImage::create(
                                           "buttons/playBtn.png",
                                           "buttons/pressedPlayBtn.png",
                                           CC_CALLBACK_1(MenuScene::switchToGameScene, this));

    if (playItem == nullptr ||
        playItem->getContentSize().width <= 0 ||
        playItem->getContentSize().height <= 0)
    {
        problemLoading("'playBtn.png.png' and 'pressedPlayBtn.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/2;
        float y = origin.y + visibleSize.height/2 + 100;
        playItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add a label shows "League of Adventures"
    // create and initialize a label
    auto label = Label::createWithTTF("League Of Adventures", "fonts/Marker Felt.ttf", 32);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - 240));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add background sprite"
    auto sprite = Sprite::create("backgrounds/startBg.png");
    if (sprite == nullptr)
    {
        problemLoading("'startBg.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                 visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite);
    }
    return true;
}

void MenuScene::switchToGameScene(Ref* pSender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
