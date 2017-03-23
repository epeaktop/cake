#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:

	virtual bool init();

    CREATE_FUNC(PauseLayer);
    
    void menuCallback(Ref* pSender);

};

#endif
