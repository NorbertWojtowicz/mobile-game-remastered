#pragma once
#ifndef __TELEPORT_H__
#define __TELEPORT_H__

#include "cocos2d.h"
#include "GameScene.h"
#include <string>
#include <vector>

USING_NS_CC;

class Teleport
{
public:
	static Teleport createWithIcon();
	Node* nodeWithIcon;
private:
	Animate* createTeleportAnimate();
	void openMap();
	void buildTeleportIconNode();
	void pushWorldMapScene();
};

#endif