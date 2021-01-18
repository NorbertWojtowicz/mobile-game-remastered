#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__
#include "cocos2d.h"
#include "EnemyHero.h"
#include "Brand.h"
#include "Ryze.h"
#include "AllyHero.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class WorldMap : public cocos2d::Node
{
public:
	CREATE_FUNC(WorldMap);
	virtual bool init();
	static Scene* createScene();
	ui::ScrollView* scrollView;
	void initScrollView();
	void startLevelWithHeroesId(short enemyId, short allyId);
	typedef std::map<std::string, EnemyHero* (*)()> map_Enemy;
	typedef std::map<std::string, AllyHero* (*)()> map_Ally;
	map_Enemy mapEnemy;
	map_Ally mapAlly;
	void prepareEnemyMap();
	void prepareAllyMap();
private:
	void addIslandsToScrollView();
	short allyId, enemyId;
	std::string alliesTab[4] = { "Ryze", "Ashe", "Garen", "Twisted_Fate" };
	std::string enemiesTab[11] = { "Brand", "Cassiopeia", "Darius", "Taliyah", "Karthus" , "Pantheon", "Lucian", "Kogmaw", "Malhazar", "Irelia", "Yuumi" };
};
#endif
