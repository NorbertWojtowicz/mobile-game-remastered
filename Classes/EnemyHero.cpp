#include "EnemyHero.h"
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
	//TBD fill filePath correctly
	sprite = Sprite::create("heroes/brand/" + nameOfHero + "Sprite.png");
	sprite->setPosition(Vec2(320, 570));
}