#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "SettingLayer.h"
#include "AboutLayer.h"

class StartScene : public cocos2d::Layer
{
public:
	StartScene();
	virtual ~StartScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCallback(Ref* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(StartScene);

private:

	virtual void updateSetting(float delta);
	virtual void updateAbout(float delta);

	void createStarAnimation(Vec2 pos, float delay);

	void pandaCallback1(Node *pSender);
	void pandaCallback2(Node *pSender);

public:
	static bool isSetting;
	static bool isAbout;

private:
	SettingLayer *m_pSetting;
	AboutLayer *m_pAbout;
};

#endif  // __HELLOWORLD_SCENE_H__
