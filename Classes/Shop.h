#ifndef __SHOP_H__
#define __SHOP_H__

#include "cocos2d.h"
#include "GameScene.h"
#include <iostream>
#include <string>
USING_NS_CC;

class Shop {
public:
	static Shop createShopLayer();
	Node* shopIconsLayer = Node::create();
private:
	void addSignToLayer();
	void addShopMenuToLayer();
	int numberOfPage;
	void turnPageToRight();
	void turnPageToLeft();
	void addButtons();
	Menu* shopMenu;
	void changeShopPage(int numberOfPage);
	void closeShop();
	Node* shopLayer;
	static const std::string hero_names[4];
};


#endif