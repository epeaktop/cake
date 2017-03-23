#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "cocos2d.h"

#define RANDOM_RANGE(_MIN_,_MAX_) (CCRANDOM_0_1()*((_MAX_)-(_MIN_))+(_MIN_))

#define SimpleAudioEngine()		SimpleAudioEngine::sharedEngine()



#pragma clang diagnostic push
#pragma clang diagnostic ignored"-Wdeprecated-declarations"

#define OFFSET_X 60
#define OFFSET_Y 220

#define CELL_WIDTH 100
#define CELL_HEIGHT 100

#define BG_ODER -2


#endif
