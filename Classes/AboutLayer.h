#ifndef __ABOUT_LAYER_H__
#define __ABOUT_LAYER_H__

#include "cocos2d.h"

class AboutLayer : public cocos2d::Layer
{
public:

	virtual bool init();

    CREATE_FUNC(AboutLayer);
    
    void menuCallback(Ref* pSender);

};

#endif
