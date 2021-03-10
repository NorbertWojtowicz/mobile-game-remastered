#include "EnemyHero.h"
#include "LevelScene.h"
void EnemyHero::setName(std::string name)
{
	this->name = name;
}
std::string EnemyHero::getName()
{
	return name;
}
void EnemyHero::setSprite(std::string nameOfHero)
{
	sprite = Sprite::create("heroes/" + nameOfHero + "/" + nameOfHero + "Sprite.png");
	sprite->setPosition(Vec2(320, 570));
}
void EnemyHero::initAnimates()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/" + name + "/" + name + "FirstSpellAnimate.plist");
	for (int i = 0; i <= firstSpellNumberOfFrames; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName(name + num + ".png"));
	}
	auto firstSpellAnimation = Animation::createWithSpriteFrames(frames, firstSpellFrameDuration);
	firstSpellAnimate = Animate::create(firstSpellAnimation);
	cache->destroyInstance();
}
void EnemyHero::updateFirstSpellTime(float dt)
{
	firstSpellCooldown -= dt;
	cocos2d::log("Actual time2 is: %d", firstSpellCooldown);
	if (firstSpellCooldown <= 0)
	{
		firstSpellCooldown = firstSpellCooldownConst + firstSpellAnimate->getDuration();
	}
}
void EnemyHero::initWalkAnimate()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/" + name + "/" + name + "WalkAnimate.plist");
	for (int i = 0; i <= walkNumberOfFrames; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName(name + num + ".png"));
	}
	auto walkAnimation = Animation::createWithSpriteFrames(frames, walkFrameDuration);
	walkAnimate = Animate::create(walkAnimation);
	cache->destroyInstance();
}
void EnemyHero::runWalkAnimate()
{
	initWalkAnimate();
	sprite->runAction(RepeatForever::create(walkAnimate))->setTag(1);
}
void EnemyHero::stopWalkAnimate()
{
	sprite->stopActionByTag(1);
}
void EnemyHero::dealDamageToAllyHero()
{
	oponent->health -= strength;
	updateAllyHeroHpBar(oponent->health);
	if (oponent->health <= 0)
		finishBattleWithLose();
}
void EnemyHero::updateAllyHeroHpBar(short health)
{
	std::stringstream ss;
	ss << health << "/" << oponent->constHealth;
	std::string healthStr = ss.str();
	oponent->hpLabel->setString(healthStr);
	double remainingHealthInPercent = ((double)health / oponent->constHealth) * 100;
	oponent->hpBar->setPercent(remainingHealthInPercent);
}
void EnemyHero::initAllyHero(AllyHero* hero)
{
	oponent = hero;
}
void EnemyHero::finishBattleWithLose()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
	addLosePopupToScene(scene);
}
void EnemyHero::addLosePopupToScene(Scene* scene)
{
	auto popupSprite = Sprite::create("popups/lost.png");
	popupSprite->setPosition(Vec2(320, 550));
	scene->addChild(popupSprite);
	auto okBtn = MenuItemImage::create("buttons/okBtn.png", "buttons/pressedOkBtn.png", CC_CALLBACK_0(EnemyHero::removeLosePopupFromScene, this, scene));
	okBtn->setPosition(Vec2(0, -300));
	auto menu = Menu::create(okBtn, NULL);
	menu->setName("menu");
	popupSprite->setName("popup");
	scene->addChild(menu);
}
void EnemyHero::removeLosePopupFromScene(Scene* scene)
{
	scene->removeChildByName("popup");
	scene->removeChildByName("menu");
}