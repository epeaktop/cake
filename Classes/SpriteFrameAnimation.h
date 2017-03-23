//
//  SpriteFrameAnimation.h
//  rpg
//
//  Created by 朱小猛 on 11/10/14.
//
//

#ifndef __rpg__SpriteFrameAnimation__
#define __rpg__SpriteFrameAnimation__

#include <stdio.h>
#include <string>
#include <vector>
#include <cocos2d.h>

USING_NS_CC;

class SpriteFrameAnimation : public Sprite
{
public:
    static SpriteFrameAnimation* createWithPlist(const std::string& plist, float delayPerUnit, int loops = 1);
    SpriteFrameAnimation()
    : _animate(nullptr)
    {}
    
    ~SpriteFrameAnimation()
    {
        _animate->release();
    }
    
    void initWithAnimation(Animate* anim);
    /**
     *  repeat播放次数， remove播放完是否需要删除
     */
    void play(int repeat=1, bool remove=false);
    void setScale(float scale);
    const std::vector<std::string>& getFrameNames() { return _frameNames; }
    
    void onRemove(Node *pObject);
    
    const Vector<AnimationFrame*>& getAnimationFrames() const;
    
private:
    static SpriteFrameAnimation* createWithSpriteFrameName(const std::string& spriteFrameName);
    static SpriteFrameAnimation* createWithSpriteFrame(SpriteFrame *spriteFrame);
private:
    float _scale;
    
    std::vector<std::string> _frameNames;
    cocos2d::Animate* _animate;
};

#endif /* defined(__rpg__SpriteFrameAnimation__) */
