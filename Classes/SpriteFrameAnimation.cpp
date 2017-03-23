//
//  SpriteFrameAnimation.cpp
//  rpg
//
//  Created by 朱小猛 on 11/10/14.
//
//

#include "SpriteFrameAnimation.h"

using namespace std;
namespace {
    Animate* createAnimateWithPlist(const std::string& plist, float delayPerUnit, int loops, std::vector<std::string>& frameNames)
    {
        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile(plist);
        
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
        const ValueMap& framesDict = dict["frames"].asValueMap();
        
        std::vector<std::string> orderedNames;
        orderedNames.reserve(framesDict.size());
        for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter) {
            orderedNames.push_back(iter->first);
        }
        std::sort(orderedNames.begin(), orderedNames.end());
        
        Vector<SpriteFrame*> arr;
        for (auto const& spriteFrameName : orderedNames)
        {
            frameNames.push_back(spriteFrameName);
            SpriteFrame* spriteFrame = cache->getSpriteFrameByName(spriteFrameName);
            if(spriteFrame == nullptr)
                continue;
            arr.pushBack(spriteFrame);
        }
        
        cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(arr, delayPerUnit, loops);
        
        return Animate::create(animation);
    }
}

SpriteFrameAnimation* SpriteFrameAnimation::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
    SpriteFrameAnimation *sprite = new (std::nothrow) SpriteFrameAnimation();
    if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

SpriteFrameAnimation* SpriteFrameAnimation::createWithSpriteFrameName(const std::string& spriteFrameName)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

    #if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
    CCASSERT(frame != nullptr, msg);
    #endif

    return createWithSpriteFrame(frame);
}

SpriteFrameAnimation* SpriteFrameAnimation::createWithPlist(const std::string& plist, float delay, int loops)
{
    vector<string> frameNames;
    auto animate = createAnimateWithPlist(plist, delay, loops, frameNames);
    SpriteFrameAnimation * ret = createWithSpriteFrameName(frameNames.front());
    ret->_animate = animate;
    ret->_animate->retain();
    ret->_frameNames = frameNames;
    return ret;
    //SpriteFrameAnimation * ret = createWithSpriteFrame();
}

void SpriteFrameAnimation::play(int repeat, bool remove)
{
    FiniteTimeAction*  action1 = nullptr;
    if(repeat == -1) {
        action1 = RepeatForever::create(_animate);
        remove = false;
    } else if (repeat == 1) {
        action1 = _animate;
    } else {
        action1 = Repeat::create(_animate, repeat);
    }
    
    action1->setTag(1);
    
    this->stopActionByTag(1);

    auto action2 = CallFuncN::create(std::bind(&SpriteFrameAnimation::onRemove, this, std::placeholders::_1));

    
    if (remove)
    {
        runAction(Sequence::create(action1, action2, nullptr));
    }
    else {
        auto stopAction = CallFunc::create([this]()
                                           {
                                               this->stopActionByTag(1);
                                           });
        if (repeat == -1) {
            runAction(action1);
        } else if(repeat == 1) {
            runAction(action1);
        }else {
            auto seq = Sequence::create(action1, stopAction, nullptr);
            
            runAction(seq);
        }
    }
}

void SpriteFrameAnimation::setScale(float scale)
{
    Sprite::setScale(scale);
}

void SpriteFrameAnimation::onRemove(Node *pObject)
{
    removeFromParent();
}

const Vector<AnimationFrame*>& SpriteFrameAnimation::getAnimationFrames() const
{
    return _animate->getAnimation()->getFrames();
}
