#include "GameScene.h"
#include "ArtifactView.h"
#include <cocos2d.h>

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	layer->setName("gameNode");
	scene->addChild(layer);
	return scene;
}
bool GameScene::init()
{
	if ( !Node::init() )
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
	Shop *shop = Shop::createShopLayer();
	this->addChild(shop->shopIconsLayer);

	//adding teleport
	Teleport teleport = Teleport::createWithIcon();
	this->addChild(teleport.nodeWithIcon);
	
	this->addArtifactChest();

	return true;
}
void GameScene::addArtifactChest()
{
	auto chest = MenuItemImage::create("artefacts/chest.png", "artefacts/chest.png", CC_CALLBACK_0(GameScene::runArtifactView, this));
	auto chestMenu = Menu::create(chest, NULL);
	chest->setPosition(Vec2(-230, -200));
	this->addChild(chestMenu);
}
void GameScene::runArtifactView()
{
	auto scene = ArtifactView::createScene();
	Director::getInstance()->replaceScene(scene);
}