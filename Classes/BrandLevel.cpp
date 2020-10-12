#include "BrandLevel.h"
Scene* BrandLevel::createScene()
{
	auto scene = Scene::create();
	auto node = BrandLevel::create();
	scene->addChild(node);
	return scene;
}
bool BrandLevel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->addEssentialElements();
	return true;
}
void BrandLevel::addEssentialElements()
{
	addBackground("backgrounds/firstSceneBG.png");
	addHeroFace("combatScene/hudRyze.png");
	addHud();
}
void BrandLevel::addBackground(std::string backgroundFilePath)
{
	auto background = Sprite::create(backgroundFilePath);
	background->setPosition(Vec2(320, 650));
	addChild(background);
}
void BrandLevel::addHeroFace(std::string heroFaceFilePath)
{
	auto heroFace = Sprite::create(heroFaceFilePath);
	heroFace->setPosition(Vec2(74, 126));
	addChild(heroFace);
}
void BrandLevel::addHud()
{
	auto hud = Sprite::create("combatScene/hud.png");
	hud->setPosition(Vec2(320, 128));
	addChild(hud);
	addHeroSpells("ryze");
}
void BrandLevel::addHeroSpells(std::string nameOfHero)
{
	auto spellOneIcon = MenuItemImage::create("combatScene/spells/ryzeSpell1.png", "combatScene/spells/" + nameOfHero + "Spell1.png");
	auto spellTwoIcon = MenuItemImage::create("combatScene/spells/ryzeSpell2.png", "combatScene/spells/" + nameOfHero + "Spell2.png");
	spellOneIcon->setPosition(Vec2(-30, -436));
	spellTwoIcon->setPosition(Vec2(+150, -436));
	auto spellsIconMenu = Menu::create();
	spellsIconMenu->addChild(spellOneIcon);
	spellsIconMenu->addChild(spellTwoIcon);
	addChild(spellsIconMenu);
}