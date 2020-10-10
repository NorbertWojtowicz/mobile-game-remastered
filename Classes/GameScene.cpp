#include "GameScene.h"
#include <cocos2d.h>

cocos2d::Scene* GameScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = GameScene::create();
	layer->setTag(999);
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
	Sprite* background = Sprite::create("backgrounds/mainBG.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x,
								 visibleSize.height / 2 + origin.y));
	this->addChild(background);
	background->setTag(211);

	//adding shop
	Shop shop = Shop::createShopLayer();
	this->addChild(shop.shopIconsLayer);

	//adding teleport
	Teleport teleport = Teleport::createWithIcon();
	this->addChild(teleport.nodeWithIcon);
	

	return true;
}