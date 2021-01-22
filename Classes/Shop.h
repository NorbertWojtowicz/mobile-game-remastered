#ifndef __SHOP_H__
#define __SHOP_H__

#include "cocos2d.h"
//#include "GameScene.h"
#include <iostream>
#include <string>
USING_NS_CC;

class Shop {
public:
	static Shop *createShopLayer();
	Node* shopIconsLayer = Node::create();
private:
	void addSignToLayer();
	void addShopMenuToLayer();
	int numberOfPage, numberOfCategory;
	void turnPageToRight();
	void turnPageToLeft();
	void addButtons();
	void buyHero();
	Menu* shopMenu;
	void removePreviousHero();
	void changeShopPage(int numberOfPage);
	void closeShop();
	Node* shopLayer;
	Sprite* boughtHeroSprite;
	static const std::string shop_products[3][7];
	Label* moneyLabel;
	std::string generateMoneyStringFromInt(int money);
	int money = 0;
	int costsOfProducts[3][7] = { { 0, 100, 100, 100, 100, 100, 100 }, {350, 550, 750, 950}, {350, 800, 950} };
	void addMoneyStatusToShopLayer();
	void addNoMoneyPopup();
	void changeCategory(int numberOfCategory);
	void buyMultiplier();
	void buyItem();
	void removeNoMoneyPopup();
	bool isOwned();
};
#endif
