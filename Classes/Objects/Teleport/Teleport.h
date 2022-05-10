#ifndef __TELEPORT_H__
#define __TELEPORT_H__

#include "cocos2d.h"
#include <string>

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
	void addSignToNode();
};

#endif
