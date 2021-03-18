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
	// Adding Background
	Sprite* background = Sprite::create("backgrounds/mainBG.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x,
								 visibleSize.height / 2 + origin.y));
	this->addChild(background);
	background->setTag(211);

	//Adding already picked hero
	addPickedHero();

	// Adding Shop
	Shop *shop = Shop::createShopLayer();
	this->addChild(shop->shopIconsLayer);

	// Adding Teleport
	Teleport teleport = Teleport::createWithIcon();
	this->addChild(teleport.nodeWithIcon);
	
	// Adding ArtifactView
	ArtifactView* artifactView = ArtifactView::createWithChest();
	this->addChild(artifactView->node);

	return true;
}
void GameScene::addPickedHero()
{
	int numberOfHero = UserDefault::getInstance()->getIntegerForKey("allyHeroId");
	if ((numberOfHero == 0) && (UserDefault::getInstance()->getIntegerForKey("ryze") != 1))
		return;
	auto heroStr = heroes[numberOfHero + 1];
	auto heroSprite = Sprite::create("heroes/" + heroStr + "/bodySprite.png");
	heroSprite->setTag(1212);
	heroSprite->setPosition(Vec2(320, 920));
	this->addChild(heroSprite);
}