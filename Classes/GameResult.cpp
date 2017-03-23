
#include "GameResult.h"
#include "UserData.h"
#include "NDKHelper.h"

const int STAR_TAG = 1212;
const int STAR1_TAG = 1213;
const int STAR2_TAG = 1214;

GameResult::GameResult():
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

GameResult::~GameResult()
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

bool GameResult::init()
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
    	a->setCallback(CC_CALLBACK_1(GameResult::buttonCallback,this));
        
        auto b = MenuItemImage::create("box1.png", "box1.png");
        b->setCallback(CC_CALLBACK_1(GameResult::buttonCallback,this));
        
        auto c = MenuItemImage::create("box2.png", "box2.png");
        c->setCallback(CC_CALLBACK_1(GameResult::buttonCallback, this));
        
        a->setTag(CLOSE_TAG);
        b->setTag(GIFT1_TAG);
        c->setTag(GIFT2_TAG);
        
        a->setPosition(670, 1280 - 320);
        b->setPosition(720/2, 1280 - 575);
        c->setPosition(720/2, 1280 - 570);
        
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
        b->setVisible(false);
        c->setVisible(false);
        
        auto charMap = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        charMap->setPosition(720/2, 1280 - 475);
        std::stringstream ss;
        ss.str("");
        ss << UserData::getInstance()->getScore();
        charMap->setString(ss.str());
        addChild(charMap,100);
        
        Sprite* star;
 
        star = Sprite::create("popup_star_bg.png");
        star->setPosition(720/2, 1280 - 475 -100);
        
        auto size = Director::getInstance()->getWinSize();
        
        ActionInterval* move = MoveTo::create(1.f, Vec2(720/2, 1280 - 475 - 100));
        ActionInterval* scale = ScaleTo::create(1.0f, 0.9f);
        ActionInterval* sineIn = EaseBackIn::create(move);
        
        FiniteTimeAction * spawn = Spawn::create(sineIn, scale, NULL);
        
        auto starSp = Sprite::create("star.png");
        starSp->setPosition(size.width/2, size.height/2);
        starSp->setScale(0.2, 0.2);
        starSp->setTag(STAR_TAG);
        addChild(starSp, 100);
        
        CallFuncN* callback = CallFuncN::create(CC_CALLBACK_1(GameResult::starCallback, this));
        starSp->runAction(Sequence::create(spawn, callback, NULL));
        
        
        addChild(star,100);
        auto title = Sprite::create("lvl_up.png");
        title->setPosition(720/2, 1280 - 300);
        addChild(title, 100);
        
        bRef = true;
    }
    while (0);
    return bRef;
}

void GameResult::starCallback(Ref* obj)
{

    auto starSp = getChildByTag(STAR_TAG);
    starSp->setVisible(false);
    
    Sprite* star = Sprite::create("popup_star_bg1.png");
    auto score = UserData::getInstance()->getScore();
    if (score > 1000)
    {
        auto size = Director::getInstance()->getWinSize();
        
        ActionInterval* move = MoveTo::create(1.f, Vec2(720/2, 1280 - 475 - 100));
        ActionInterval* scale = ScaleTo::create(1.0f, 0.3f);
        ActionInterval* sineIn = EaseBackIn::create(move);
        
        FiniteTimeAction * spawn = Spawn::create(sineIn, scale, NULL);
        
        auto starSp = Sprite::create("star.png");
        starSp->setPosition(size.width/2, size.height/2);
        starSp->setScale(0.2, 0.2);
        starSp->setTag(STAR1_TAG);
        addChild(starSp, 100);
        
        CallFuncN* callback = CallFuncN::create(CC_CALLBACK_1(GameResult::star2Callback, this));
        starSp->runAction(Sequence::create(spawn, callback, NULL));
        
    }

    star->setPosition(720/2, 1280 - 475 - 100);
    addChild(star, 100);
}

void GameResult::star2Callback(Ref* obj)
{

    auto starSp = getChildByTag(STAR1_TAG);
    starSp->setVisible(false);
    
   
    auto score = UserData::getInstance()->getScore();
    if (score >= 3000)
    {
        auto size = Director::getInstance()->getWinSize();
        
        ActionInterval* move = MoveTo::create(1.f, Vec2(720/2, 1280 - 475 - 100));
        ActionInterval* scale = ScaleTo::create(1.0f, 0.3f);
        ActionInterval* sineIn = EaseBackIn::create(move);
        
        FiniteTimeAction * spawn = Spawn::create(sineIn, scale, NULL);
        
        auto starSp = Sprite::create("star.png");
        starSp->setPosition(size.width/2, size.height/2);
        starSp->setScale(0.2, 0.2);
        starSp->setTag(STAR2_TAG);
        addChild(starSp, 100);
        
        CallFuncN* callback = CallFuncN::create(CC_CALLBACK_1(GameResult::star3Callback, this));
        starSp->runAction(Sequence::create(spawn, callback, NULL));
    }
    
    Sprite* star = Sprite::create("popup_star_bg2.png");
    star->setPosition(720/2, 1280 - 475 - 100);
    addChild(star, 100);
}

void GameResult::star3Callback(Ref* obj)
{
    auto starSp = getChildByTag(STAR2_TAG);
    starSp->setVisible(false);
    
    Sprite* star = Sprite::create("popup_star_bg3.png");
    star->setPosition(720/2, 1280 - 475 - 100);
    addChild(star, 100);
    
    
    auto ro = RotateBy::create(2, 360);
    auto light = Sprite::create("level_light.png");
    
    addChild(light, 99);
    auto rt = RepeatForever::create(ro);
    light->runAction(rt);
    light->setPosition(720/2, 1280 - 475 - 100);
    
}

bool GameResult::TouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    log("GameResult touch");
    return true;
}


GameResult* GameResult::create(const char *backgroundImage)
{
    GameResult* ml = GameResult::create();
    ml->setSpriteBackGround(Sprite::create(backgroundImage));
    ml->setSprite9BackGround(ui::Scale9Sprite::create(backgroundImage));
    return ml;
}


void GameResult::setTitle(const char*title, int fontsize)
{
    auto ltfTitle = Label::createWithSystemFont(title, "Arial", fontsize);
    setLabelTitle(ltfTitle);
}

void GameResult::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
    auto ltf = Label::createWithSystemFont(text, "Arial", fontsize);
    setLabelContentText(ltf);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}


void GameResult::setCallbackFunc(cocos2d::Ref *target, SEL_CallFuncN callfun)
{
    m_callbackListener = target;
    m_callback = callfun;
}


bool GameResult::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag)
{
    Size winSize = Director::getInstance()->getWinSize();
    Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);

    // 创建图片菜单按钮
    auto menuImage = MenuItemImage::create(normalImage, selectedImage);
    menuImage->setCallback(CC_CALLBACK_1(GameResult::buttonCallback,this));
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
void GameResult::showOpenBoxAnimi(int flag)
{
    auto a = ParticleSystemQuad::create("BubbleSpecial/yanhua02.plist");
    a->setPosition(268, 960 - 428);
    
    auto b = FadeOut::create(0.2);
    auto box1 = getMenuButton()->getChildByTag(GIFT1_TAG);
    auto box2 = getMenuButton()->getChildByTag(GIFT2_TAG);
    auto c = FadeOut::create(0.2);
    box1->runAction(b);
    box2->runAction(c);
    
    auto sp = Sprite::create("time.png");
    addChild(sp);
    sp->setPosition(268, 960-428);
    auto fi = FadeIn::create(0.5);
    sp->runAction(fi);
    addChild(a);
}
bool GameResult::addButton(const char *normalImage, const char *selectedImage, Vec2 pos, int tag)
{
    // 创建图片菜单按钮
    auto menuImage = MenuItemImage::create(normalImage, selectedImage);
    menuImage->setCallback(CC_CALLBACK_1(GameResult::buttonCallback, this));
    menuImage->setTag(tag);
    menuImage->setPosition(pos);
    
    getMenuButton()->addChild(menuImage);
    return true;
}

void GameResult::buttonCallback(cocos2d::Ref *pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    log("touch tag: %d", node->getTag());
    if (GIFT1_TAG == node->getTag() || GIFT2_TAG == node->getTag())
    {
        callJava("showAds","");
        showOpenBoxAnimi(1);
        return;
    }
    
    if (m_callback && m_callbackListener)
    {
        node->setUserData((void*)&level_);
        (m_callbackListener->*m_callback)(node);
    }
    removeFromParentAndCleanup(true);
}



void GameResult::onEnter()
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
    float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);

    Vector < Node* > array = getMenuButton()->getChildren();
    
//    int i = 0;
//    for(auto node : array)
//    {
//        node->setPosition(Vec2(winSize.width / 2 - contentSize.width / 2 + btnWidth * (i + 1), winSize.height / 2 - contentSize.height / 3));
//        i++;
//    }

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


void GameResult::onExit()
{
    log("popup on exit.");
    Layer::onExit();
}
