#ifndef __BRAND_LEVEL_H__
#define __BRAND_LEVEL_H__
#include <string>
#include "cocos2d.h"
USING_NS_CC;
class BrandLevel : public cocos2d::Node
{
public:
	virtual bool init();
	CREATE_FUNC(BrandLevel);
	static Scene* createScene();
private:
	void addEssentialElements();
	void addBackground(std::string backgroundFilePath);
	void addHeroFace(std::string heroFaceFilePath);
	void addHud();
	void addHeroSpells(std::string nameOfHero);
};
#endif