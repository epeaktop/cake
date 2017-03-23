#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class PopupLayer : public cocos2d::Layer
{
public:
    PopupLayer();
    ~PopupLayer();

    virtual bool init();
    CREATE_FUNC(PopupLayer);


    bool TouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

    static PopupLayer* create(const char* backgroundImage);


    void setTitle(const char*title, int fontsize = 20);

    void setContentText(const char *text, int fontsize = 20, int padding = 50, int paddintTop = 100);

    void setCallbackFunc(Ref* target, SEL_CallFuncN callfun);

    bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);
    bool addButton(const char* normalImage, const char* selectedImage, Vec2 pos, int tag = 0);

    virtual void onEnter();
    virtual void onExit();
    void showOpenBoxAnimi(int flag);
    
    int level_;
    

private:

    void buttonCallback(Ref* pSender);

    // 文字内容两边的空白区
    int m_contentPadding;
    int m_contentPaddingTop;

    Ref* m_callbackListener;
    SEL_CallFuncN m_callback;

    CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
    CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);
    CC_SYNTHESIZE_RETAIN(ui::Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE_RETAIN(Label*, m__ltTitle, LabelTitle);
    CC_SYNTHESIZE_RETAIN(Label*, m__ltContentText, LabelContentText);
    
};
