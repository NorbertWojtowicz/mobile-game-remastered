#include "teleport.h"


Teleport Teleport::createWithIcon()
{
	Teleport tp = Teleport();
	tp.buildTeleportIconNode();
	return tp;
}
Animate* Teleport::createTeleportAnimate()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("teleport/tp.plist");
	for (int i = 0; i <= 3; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName("tp" + num + ".png"));
	}
	Animation* teleportAnimation = Animation::createWithSpriteFrames(frames, 0.1f);
	Animate* teleportAnimate = Animate::create(teleportAnimation);
	return teleportAnimate;
}
void Teleport::buildTeleportIconNode()
{
	this->nodeWithIcon = Node::create();
	MenuItemImage* teleportIconButton = MenuItemImage::create("teleport/0.png", "teleport/1.png", CC_CALLBACK_0(Teleport::openMap, this));
	auto teleportIconSpriteForAnimation = Sprite::create("teleport/0.png");
	teleportIconSpriteForAnimation->setPosition(Vec2(535, 270));
	teleportIconSpriteForAnimation->setScale(0.7);
	teleportIconButton->setPosition(Vec2(215, -300));
	teleportIconButton->setScale(0.7);
	Menu* teleportIconMenu = Menu::create(teleportIconButton, NULL);
	this->nodeWithIcon->addChild(teleportIconMenu, 1);
	this->nodeWithIcon->addChild(teleportIconSpriteForAnimation, 0);
	teleportIconMenu->setOpacity(0);
	teleportIconSpriteForAnimation->runAction(RepeatForever::create(this->createTeleportAnimate()));
}
void Teleport::openMap()
{
	pushWorldMapScene();
}
void Teleport::pushWorldMapScene()
{
	auto worldMapScene = WorldMap::createScene();
	Director::getInstance()->pushScene(worldMapScene);
}