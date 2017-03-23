#ifndef __SETTING_LAYER_H__
#define __SETTING_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class SettingLayer : public CCLayer
{
public:
	SettingLayer();
	virtual ~SettingLayer();

	virtual bool init();

    CREATE_FUNC(SettingLayer);
    
    void menuCallback(CCObject* pSender);

public:

	

	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

private:
	CCSprite* m_pBgInfoScreen; //设置面板指针
	CCSize m_nBgSize; //设置面板的大小

	CCSprite *m_pSelected; //设置面板中难度栏被选中"对钩"的贴图指针
};

#endif