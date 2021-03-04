#ifndef __ARTIFACT_VIEW_H__
#define __ARTIFACT_VIEW_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>
USING_NS_CC;
class ArtifactView : public Node
{
public:
	CREATE_FUNC(ArtifactView);
	virtual bool init();
	static Scene* createScene();
	ui::ScrollView* scrollView;
	void initScrollView();
	void addArtifactsToScrollView();
	void checkArtifactStatuses();
	void addArtifactInscription();
	std::string artifactLocations[7];
	std::string artifactStatuses[7];
	void closeScene();
};
#endif
