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
	CCSprite* m_pBgInfoScreen; //�������ָ��
	CCSize m_nBgSize; //�������Ĵ�С

	CCSprite *m_pSelected; //����������Ѷ�����ѡ��"�Թ�"����ͼָ��
};

#endif