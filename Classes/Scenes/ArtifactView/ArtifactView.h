#ifndef __ARTIFACT_VIEW_H__
#define __ARTIFACT_VIEW_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>
USING_NS_CC;
class ArtifactView : public Node
{
public:
	static Scene* createScene();
	static ArtifactView* createWithChest();
	Node* node = Node::create();
private:
	CREATE_FUNC(ArtifactView);
	ArtifactView() {};
	virtual bool init();
	ui::ScrollView* scrollView;
	void initScrollView();
	void addArtifactsToScrollView();
	void checkArtifactStatuses();
	void addArtifactInscription();
	std::string artifactLocations[7];
	void closeScene();
	void createNode();
	void runArtifactView();
	void addChestToNode();
	void addSignToNode();
};
#endif
