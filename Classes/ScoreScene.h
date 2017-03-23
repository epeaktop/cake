#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"

class ScoreScene : public cocos2d::Layer
{
public:

	virtual bool init();

    static cocos2d::Scene* scene();

    CREATE_FUNC(ScoreScene);

	void chartsCallback();

    void menuCallback(Ref* pSender);

private:
	static const char* m_pMedal[5];
};

#endif
