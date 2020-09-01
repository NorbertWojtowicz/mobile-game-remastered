#include "GameScene.h"
#include <cocos2d.h>

cocos2d::Scene* GameScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}
bool GameScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	//adding background
	cocos2d::Sprite* background = cocos2d::Sprite::create("backgrounds/mainBG.png");
	background->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x,
										  visibleSize.height / 2 + origin.y));
	this->addChild(background);

	//adding hero

	return true;
}