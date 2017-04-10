#ifndef __DIAMOND_H__
#define __DIAMOND_H__

#include "cocos2d.h"
#define CLEAR_ONE_LINE 1
#define CLEAR_ONE_ROW  2
#define ITEM_BOMB      3
#define ITEM_ONE_COL   4

using namespace cocos2d;

class Diamond : public CCSprite
{
public:
	Diamond();

	static Diamond* createWithSpriteFrameName(const char *pszSpriteFrameName);

public:
	
    static const char* TypeStr[5];
	static const char* TypeBwStr[5];
	static const char* BombTypeStr[6];

private:
	CC_SYNTHESIZE(int, m_nType, Type);
    CC_SYNTHESIZE(int, itemType_, ItemType);
    CC_SYNTHESIZE(int, oldType_, OldType);

	CC_SYNTHESIZE(bool, m_nFireball, Fireball);
	CC_SYNTHESIZE(bool, m_nBomb, Bomb);

	CC_SYNTHESIZE(bool, m_nMoving, Moving);

public:
    Sprite* itemObj_ = nullptr;
};

#endif