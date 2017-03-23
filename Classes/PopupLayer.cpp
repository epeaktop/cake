

#include "PopupLayer.h"
#include "UserData.h"
#define TTF_FONT_NAME  "FZDHTJW.TTF"


PopupLayer::PopupLayer():
    m__pMenu(NULL)
    , m_contentPadding(0)
    , m_contentPaddingTop(0)
    , m_callbackListener(NULL)
    , m_callback(NULL)
    , m__sfBackGround(NULL)
    , m__s9BackGround(NULL)
    , m__ltContentText(NULL)
    , m__ltTitle(NULL)
	, level_(1)
{

}

PopupLayer::~PopupLayer()
{
    CC_SAFE_RELEASE(m__pMenu);
    CC_SAFE_RELEASE(m__sfBackGround);
    CC_SAFE_RELEASE(m__ltContentText);
    CC_SAFE_RELEASE(m__ltTitle);
    CC_SAFE_RELEASE(m__s9BackGround);
}

const int CLOSE_TAG = 10240;
const int GIFT1_TAG = 10241;
const int GIFT2_TAG = 10242;

bool PopupLayer::init()
{
    bool bRef = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        this->setContentSize(Size::ZERO);
        // 初始化需要的 Menu
        Menu* menu = Menu::create();
        menu->setPosition(Vec2::ZERO);
        menu->setAnchorPoint(Vec2::ZERO);
        setMenuButton(menu);
        auto a = MenuItemImage::create("button_close.png", "button_close.png");
    	a->setCallback(CC_CALLBACK_1(PopupLayer::buttonCallback,this));
        
        auto b = MenuItemImage::create("box1.png", "box1.png");
        b->setCallback(CC_CALLBACK_1(PopupLayer::buttonCallback,this));
        
        auto c = MenuItemImage::create("box2.png", "box2.png");
        c->setCallback(CC_CALLBACK_1(PopupLayer::buttonCallback, this));
        
        a->setTag(CLOSE_TAG);
        b->setTag(GIFT1_TAG);
        c->setTag(GIFT2_TAG);
        
        a->setPosition(670, 1280 - 320);
        b->setPosition(720/2, 1280 - 575);
        c->setPosition(720/2, 1280 - 575);
        
        auto r1 = RotateTo::create(0.2, 1);
        auto r2 = RotateTo::create(0.2, -1);
        auto r5 = RotateTo::create(0.2, 0);
        
        auto r3 = RotateTo::create(0.2, 3);
        auto r4 = RotateTo::create(0.2, -3);
        auto r6 = RotateTo::create(0.2, 0);
        auto d1 = DelayTime::create(1);
        auto action_ = Sequence::create(d1,r1,r2,r1,r2,r5, d1,nullptr);
        auto action1_ = Sequence::create(d1,r3,r4,r3,r4,r6,d1,nullptr);
        auto a1 = RepeatForever::create(action_);
        auto a2 = RepeatForever::create(action1_);
        b->runAction(a1);
        c->runAction(a2);
        getMenuButton()->addChild(a);
        getMenuButton()->addChild(b);
        getMenuButton()->addChild(c);
        bRef = true;
    }
    while (0);
    return bRef;
}




bool PopupLayer::TouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    log("PopupLayer touch");
    return true;
}


PopupLayer* PopupLayer::create(const char *backgroundImage)
{
    PopupLayer* ml = PopupLayer::create();
    ml->setSpriteBackGround(Sprite::create(backgroundImage));
    ml->setSprite9BackGround(ui::Scale9Sprite::create(backgroundImage));
    return ml;
}


void PopupLayer::setTitle(const char*title, int fontsize)
{
    auto ltfTitle = Label::createWithSystemFont(title, "Arial", fontsize);
    setLabelTitle(ltfTitle);
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
    auto ltf = Label::createWithSystemFont(text, "Arial", fontsize);
    setLabelContentText(ltf);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}


void PopupLayer::setCallbackFunc(cocos2d::Ref *target, SEL_CallFuncN callfun)
{
    m_callbackListener = target;
    m_callback = callfun;
}


bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag)
{
    Size winSize = Director::getInstance()->getWinSize();
    Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);

    // 创建图片菜单按钮
    auto menuImage = MenuItemImage::create(normalImage, selectedImage);
    menuImage->setCallback(CC_CALLBACK_1(PopupLayer::buttonCallback,this));
    menuImage->setTag(tag);
    menuImage->setPosition(pCenter);

    // 添加文字说明并设置位置
    Size imenu = menuImage->getContentSize();
    auto ttf = Label::createWithSystemFont(title, "Arial", 20);
    ttf->setColor(Color3B(0, 0, 0));
    ttf->setPosition(Vec2(imenu.width / 2, imenu.height / 2));
    menuImage->addChild(ttf);

    getMenuButton()->addChild(menuImage);
    return true;
}
void PopupLayer::showOpenBoxAnimi(int flag)
{
    auto a = ParticleSystemQuad::create("yanhua02.plist");
    a->setPosition(720/2, 1280 - 575);
    
    auto b = FadeOut::create(0.2);
    auto box1 = getMenuButton()->getChildByTag(GIFT1_TAG);
    auto box2 = getMenuButton()->getChildByTag(GIFT2_TAG);
    auto c = FadeOut::create(0.2);
    box1->runAction(b);
    box2->runAction(c);
    
    auto sp = Sprite::create("gui/item_move.png");
    addChild(sp);
    sp->setPosition(720/2, 1280 - 575);
    auto fi = FadeIn::create(0.5);
    sp->runAction(fi);
    addChild(a);
    UserData::getInstance()->addMoveItemNum(1);
}
bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, Vec2 pos, int tag)
{
    // 创建图片菜单按钮
    auto menuImage = MenuItemImage::create(normalImage, selectedImage);
    menuImage->setCallback(CC_CALLBACK_1(PopupLayer::buttonCallback, this));
    menuImage->setTag(tag);
    menuImage->setPosition(pos);
    
    getMenuButton()->addChild(menuImage);
    
    
    auto charMap = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
    charMap->setPosition(720/2, 1280-475);
    std::stringstream ss;
    ss.str("");
    ss << level_;
    charMap->setString(ss.str());
    addChild(charMap,100);
    return true;
}
#include "NDKHelper.h"
void PopupLayer::buttonCallback(cocos2d::Ref *pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    log("touch tag: %d", node->getTag());
    if (GIFT1_TAG == node->getTag() || GIFT2_TAG == node->getTag())
    {
        callJava("showAds","");
        showOpenBoxAnimi(1);
        UserData::getInstance()->setOpenBox(true);
        return;
    }
    
    if (m_callback && m_callbackListener)
    {
        node->setUserData((void*)&level_);
        (m_callbackListener->*m_callback)(node);
    }
    removeFromParentAndCleanup(true);
}



void PopupLayer::onEnter()
{
    Layer::onEnter();

    Size winSize = Director::getInstance()->getWinSize();
    Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);

    Size contentSize;
    // 设定好参数，在运行时加载
    if (getContentSize().equals(Size::ZERO))
    {
        getSpriteBackGround()->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
        this->addChild(getSpriteBackGround(), 0, 0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    }
    else
    {
        ui::Scale9Sprite *background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
        this->addChild(background, 0);
        contentSize = getContentSize();
    }


    // 添加按钮，并设置其位置
    this->addChild(getMenuButton());

    Vector < Node* > array = getMenuButton()->getChildren();
    // 显示对话框标题
    if (getLabelTitle())
    {
        getLabelTitle()->setPosition(Vec2(pCenter) + Vec2(0, contentSize.height / 2 - 35.0f));
        this->addChild(getLabelTitle());
    }

    // 显示文本内容
    if (getLabelContentText())
    {
        auto ltf = getLabelContentText();
        ltf->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
 
        ltf->setHorizontalAlignment(TextHAlignment::LEFT);
        this->addChild(ltf);
    }

    Action* popupLayer = Sequence::create(ScaleTo::create(0.0, 0.0),
                           ScaleTo::create(0.06, 1.05),
                           ScaleTo::create(0.08, 0.95),
                           ScaleTo::create(0.08, 1.0), NULL);
    this->runAction(popupLayer);

}


void PopupLayer::onExit()
{
    log("popup on exit.");
    Layer::onExit();
}
