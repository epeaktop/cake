#include "Diamond.h"

const char* Diamond::TypeStr[5] = {
    "gems_blue.png",	
    "gems_green.png",		
    "gems_purple.png",		
    "gems_red.png",	
    "gems_yellow.png"
};

const char* Diamond::TypeBwStr[5]= {
    "gems_blue_bw.png",
    "gems_green_bw.png",
    "gems_purple_bw.png",
    "gems_red_bw.png",
    "gems_yellow_bw.png"
};
const char* Diamond::BombTypeStr[6]= {
    "bomb_blue.png",
    "bomb_green.png",
    "bomb_purple.png",
    "bomb_red.png",
    "bomb_orange.png",
    "bomb_grey.png"
};

Diamond::Diamond()
:m_nType(-1)
, itemType_(-1)
,m_nFireball(false)
,m_nBomb(false)
,m_nMoving(false)
{
	
}

Diamond* Diamond::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
	Diamond *p = new Diamond;

	if(p && p->initWithSpriteFrameName(pszSpriteFrameName))
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_RELEASE(p);
	return NULL;
}
