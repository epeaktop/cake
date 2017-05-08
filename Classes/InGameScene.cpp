
#include "InGameScene.h"
#include "PauseLayer.h"
#include "ScoreScene.h"
#include "AppDelegate.h"
#include "GameData.h"
#include <sstream>
#include "GameResult.h"
#include "UserData.h"
#include "HelpScene.h"
#include "SpriteFrameAnimation.h"
#include "GatherLayer.h"
#include "GameSetting.h"
#include "Tools.h"
#include "NDKHelper.h"
#include "FailLayer.h"
#include <time.h>
#define PAN 0.000001
#define BOMB_MESSAGE 100001

using namespace std;

using namespace cocos2d;
using namespace CocosDenshion;

bool InGameScene::isPaused = false;
unsigned int InGameScene::level = 1;
unsigned int InGameScene::background = 1;
unsigned int InGameScene::bomb = 2;
const char *InGameScene::strMode[3] = {"Simple", "Normal", "Expert"};
const unsigned int InGameScene::limitTime[3] = {60, 60, 60};
const unsigned int InGameScene::baseScore[3] = {20, 50, 100};
const unsigned int InGameScene::limitScore[3] = {6000, 10000, 12000};
const unsigned int InGameScene::limitFireball[3] = {100, 70, 30};
const unsigned int InGameScene::limitCrazy[3] = {8, 10, 6};

const int MOVES_NUM_POSX = 26;
const int MOVES_NUM_POSY = 1227;
/**
 * 元素从move_number处飞行的时间
 */
const float MOVE_NUMBER_MOVE_TIME = 0.3f;
/**
 * 原来元素fadeout的时间
 */
const float ITEM_FADEOUT_TIME = 0.3f;
/**
 * 原来元素换成bomb的时间
 */
const float BOMB_SHOW_TIME = 0.1f;


void InGameScene::reset()
{
    InGameScene::isPaused = false;
}

InGameScene::InGameScene()
    : m_nMagicCount(0)
    , m_pMagicProgress(NULL)
    , m_nTime(0)
    , m_nScore(0)
    , m_nTempScore(0)
    , m_nDiamondRow(0)
    , m_nDiamondLine(0)
    , m_bIsReadyGoEnd(false)
    , m_pPause(NULL)
    , m_pDiamondBatchNode(NULL)
    , m_pRemovedDiamond(NULL)
    , m_pScoreLable(NULL)
    , m_pTimerBar(NULL)
    , m_pMoveLable(NULL)
    , m_pTargetLable(NULL)
    , m_bFireballMode(false)
    , m_bError(false)
    , m_nTimeCount(0)
    , m_nCrazyCount(0)
    , m_bIsCrazyMode(false)
    , m_pEffectDict(NULL)
    , m_startType(-1)
    , m_moveStatus(-1)
    , moves_number_(0)
    , m_lineObjs(nullptr)
{

}

InGameScene::~InGameScene()
{
    CC_SAFE_RELEASE_NULL(m_pPause);
    CC_SAFE_RELEASE_NULL(m_pMagicProgress);
    CC_SAFE_RELEASE_NULL(m_pMoveLable);
    CC_SAFE_RELEASE_NULL(m_pTargetLable);
    CC_SAFE_RELEASE_NULL(m_pTimerBar);
    CC_SAFE_RELEASE_NULL(m_pScoreLable);
    CC_SAFE_RELEASE_NULL(m_pDiamondBatchNode);
    CC_SAFE_RELEASE_NULL(m_pRemovedDiamond);
    CC_SAFE_RELEASE_NULL(m_pEffectDict);
    //CC_SAFE_RELEASE_NULL(m_lineObjs);
}

void InGameScene::dealHp()
{
    if (USER()->getHp() > 0)
    {
        USER()->addHp(-1);
    }
    
    if (USER()->getHp() < 1 )
    {
        USER()->setLastTime(time(nullptr));
    }
   
}


//#INIT
bool InGameScene::init()
{
    bool bRet = false;
    m_lineObjs = nullptr;
    moves_number_ = 0;
    srand((unsigned)time(nullptr));

    do
    {
        CC_BREAK_IF(! Layer::init());

        if (GameSetting::getInstance()->getSound())
        {
            SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/bgm.mp3", true);
        }

        registEvent();


        InGameScene::isPaused = false;


        InGameScene::level = UserData::getInstance()->getSelLevel();
        m_nTime = 1200;

        Size winSize = Director::getInstance()->getWinSize();
        auto sp = Sprite::create("gui/df.png");
        addChild(sp, -3);
        TargetData ret = GameData::getInstance()->getTarget(InGameScene::level);
        TargetDataEx retEx = GameData::getInstance()->getTargetEx(InGameScene::level);
        moves_number_ = ret.movesNum;

        sp->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

        m_pRemovedDiamond = __Array::create();
        m_pRemovedDiamond->retain();

        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effects/effects-800x_port_mdpi.plist");

        m_pScoreLable = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        m_pScoreLable->retain();
        m_pScoreLable->setString("0");
        m_pScoreLable->setPosition(Vec2(583, 1280 - 55));

        addChild(m_pScoreLable, 100);


        m_pMoveLable = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        m_pMoveLable->retain();

        m_pMoveLable->setPosition(Vec2(MOVES_NUM_POSX, MOVES_NUM_POSY));
        m_pMoveLable->setString(TI()->_itos(moves_number_));
        addChild(m_pMoveLable, 100);

        initScoreTarget(ret);

        initGatherLayer(retEx);

        auto *pPauseItem = MenuItemImage::create("gui/game_stop.png", "gui/game_stop.png", this, menu_selector(InGameScene::menuPauseCallback));
        pPauseItem->setPosition(Vec2(690, 1280 - 37));

        refreshItemNum_ = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');

        refreshItemNum_->setString(TI()->_itos(UserData::getInstance()->getRefreshItemNum()));
        refreshItemNum_->setPosition(192, 1280-135);
        refreshItemNum_->setScale(0.6);
        addChild(refreshItemNum_, 2000);
       
        moveItemNum_ = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
//        moveItem->addChild(moveItemNum_);
        moveItemNum_->setString(TI()->_itos(UserData::getInstance()->getMoveItemNum()));
        moveItemNum_->setPosition(664, 1280-135);
        moveItemNum_->setScale(0.6);
        addChild(moveItemNum_, 2000);

        
        CREATE_LABEL(bombItemNum, 424, 1280-135);
        CREATE_LABEL(colorItemNum, 315,1280-135);
        CREATE_LABEL(digItemNum, 555,1280-135);

        auto currentLevel = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        currentLevel->setPosition(Vec2(439, 1280 - 60));
        currentLevel->setString(TI()->_itos(InGameScene::level));

        addChild(currentLevel, 100);

        Menu *pMenu = Menu::create(pPauseItem, NULL);
        CC_BREAK_IF(! pMenu);
        pMenu->setPosition(Vec2::ZERO);
        addChild(pMenu, 200);

        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui/cake.plist");
        m_pDiamondBatchNode = SpriteBatchNode::create("gui/cake.png");
        m_pDiamondBatchNode->retain();
        addChild(m_pDiamondBatchNode);


        playReadyGo();
        addFirstDiamond();

        scheduleUpdate();

        m_pEffectDict = __Dictionary::create();
        m_pEffectDict->retain();

        drawBg();

        bRet = true;

        sf = SpriteFrameAnimation::createWithPlist("gui/long.plist", 0.2);
        addChild(sf, 200);
        sf->setPosition(439, 1280 - 55);

        sf->play(-1);

    }
    while (0);

    dealHp();
    posMap_.clear();
    
    return bRet;
}
string InGameScene::getElementName(int type)
{
    
    stringstream _name;
    
    if (!TI()->isDiamond())
    {
        _name << Diamond::TypeStr[type];
    }
    else
    {
        auto _type = type + 1;
        _name << _type <<".png";
    }
    
    return _name.str();
}
void InGameScene::registEvent()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);

    listener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(InGameScene::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(InGameScene::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void InGameScene::onEnter()
{
    Image::setPVRImagesHavePremultipliedAlpha(true);

    this->setTouchEnabled(true);
    Layer::onEnter();
}

void InGameScene::onExit()
{
    Layer::onExit();
}

Scene *InGameScene::scene()
{
    Scene *scene = NULL;

    do
    {

        scene = Scene::create();
        CC_BREAK_IF(! scene);


        InGameScene *layer = InGameScene::create();
        CC_BREAK_IF(! layer);


        scene->addChild(layer);
    }
    while (0);

    return scene;
}

void InGameScene::initScoreTarget(TargetData &ret)
{
    if (isGatherMode())
    {
        return;
    }

    m_pTargetLable = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
    m_pTargetLable->retain();
    m_pTargetLable->setPosition(Vec2(210, 1280 - 58));
    m_pTargetLable->setString(TI()->_itos(ret.targetScore));
    addChild(m_pTargetLable, 100);
}

void InGameScene::playSound(string name)
{
    if (UserDefault::getInstance()->getBoolForKey("isEffectEnabled", false))
    {
        SimpleAudioEngine()->playEffect(name.c_str());
    }
}

void InGameScene::initGatherLayer(TargetDataEx target)
{
    if (!isGatherMode())
    {
        return;
    }

    ViewData ret = GameData::getInstance()->getViewData(InGameScene::level);

    if (ret.name1 == "egg_item.png")
    {
        isRecsue_ = true;
    }
    else
    {
        isRecsue_ = false;
    }

    if (!gl_)
    {
        gl_ = new GatherLayer(ret.name1, ret.name2, ret.name3,
                              Vec2(150, 1280 - 65), Vec2(220, 1280 - 65), Vec2(290, 1280 - 65));
        gl_->setString(target.num1_, target.num2_, target.num3_);
        addChild(gl_, 2000);
    }
}

void InGameScene::updateGatherNumber(int num1, int num2, int num3)
{
    if (! isGatherMode())
    {
        return;
    }

    GameData::getInstance()->num1 += num1;
    GameData::getInstance()->num2 += num2;
    GameData::getInstance()->num3 += num3;

    auto ret = GameData::getInstance()->getTargetEx(InGameScene::level);

    num1 = ret.num1_ - GameData::getInstance()->num1;
    num2 = ret.num2_ - GameData::getInstance()->num2;
    num3 = ret.num3_ - GameData::getInstance()->num3;

    if (num1 <= 0)
    {
        num1 = 0;
    }

    if (num2 <= 0)
    {
        num2 = 0;
    }

    if (num3 <= 0)
    {
        num3 = 0;
    }

    gl_->setString(num1, num2, num3);
}

void InGameScene::playReadyGo()
{
    playSound("sounds/readyGo.ogg");
    LabelTTF *readyGo = LabelTTF::create("Ready", "fonts/Verdana Bold.ttf", 60.0f);
    readyGo->setPosition(Vec2(400, 750));
    this->addChild(readyGo);
    readyGo->setScale(0.1f);
    readyGo->runAction(Sequence::create(
                           ScaleTo::create(1.1f, 1.0f),
                           DelayTime::create(.3f),
                           CallFuncN::create(this, callfuncN_selector(InGameScene::readyCallback)),
                           NULL));
}

void InGameScene::readyCallback(Node *pSender)
{
    LabelTTF *p = (LabelTTF *)pSender;
    p->setFontSize(65.f);
    p->setString("Go!!!");
    p->runAction(Sequence::create(
                     DelayTime::create(.7f),
                     CallFuncN::create(this, callfuncN_selector(InGameScene::goCallback)),
                     NULL));
}

void InGameScene::goCallback(Node *pSender)
{
    this->removeChild(pSender);
}
void InGameScene::doRefresh()
{

    if (USER()->getRefreshItemNum() <= 0)
    {
        return;
    }
    map<int, int> posMap;

    for (int line = 0; line < m_nDiamondLineMax ; line++)
    {
        for (int row = 0; row < m_nDiamondRowMax; row++)
        {
            auto p = m_pDiamond[line][row];
            if (!p)
            {
                continue;
            }

            int oldpos = line * m_nDiamondRowMax + row;
            int i = rand() % (m_nDiamondLineMax);
            int j = rand() % (m_nDiamondRowMax);

            if (posMap[oldpos] != 1)
            {
                posMap[oldpos]  = 1;
            }


            int newpos = i * m_nDiamondRowMax + j;
            if (posMap[newpos] == 1)
            {
                continue;
            }

            
            auto newDiamond = m_pDiamond[i][j];
            if (!newDiamond)
            {
                continue;
            }

            m_pDiamond[line][row] = newDiamond;
            posMap[newpos] = 1;
            Vec2 pos = newDiamond->getPosition();

            newDiamond->setPosition(p->getPosition());
            p->setPosition(pos);

            m_pDiamond[i][j] = p;

        }
    }
    USER()->addRefreshItemNum(-1);
    refreshItemNum_->setString(TI()->_itos(USER()->getRefreshItemNum()));
}

void InGameScene::addFirstDiamond()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui/cake.plist");
    addDiamond(0.1f);
}

Vec2 InGameScene::getPositionByRowAndLine(int row, int line)
{

    float x = CELL_WIDTH * row +  OFFSET_X;
    float y = CELL_HEIGHT * line + OFFSET_Y;

    return Vec2(x, y);
}

int InGameScene::getDiamondType()
{
    if (InGameScene::level < 5)
    {
        return 3;
    }
    else if (InGameScene::level < 20)
    {
        return 4;
    }

    return 5;
}

string InGameScene::getImageName(int type)
{
    string ret = "";

    switch (type)
    {
    case 0:
        ret = "gems_blue";
        break;

    case 1:
        ret = "gems_green";
        break;

    case 2:
        ret = "gems_purple";
        break;

    case 3:
        ret = "gems_red";
        break;

    case 4:
        ret = "gems_yellow";
        break;

    default:
        break;
    }

    return ret;
}

int InGameScene::isObstacle(int i, int j)
{
    int ret = 0;
    vector<obsData> data = GameData::getInstance()->getObs(InGameScene::level);
    for(obsData _data : data)
    {
        if(_data.i == i && _data.j == j)
        {
		    return _data.type;
        }
    }
    
    return ret;

}


Vec2 InGameScene::getCreatePos(int row, int line)
{
    return Vec2(CELL_WIDTH * row + OFFSET_X, CELL_HEIGHT * line + OFFSET_Y);
}

void InGameScene::addDiamond(float delta)
{
    while (true)
    {
        int ret = 0;
        if( (ret = isObstacle(m_nDiamondLine,m_nDiamondRow)) > 0 )
        {
//            auto sp = Sprite::create("zhuan.png");
//            addChild(sp);
//            
//            sp->setPosition(getCreatePos(m_nDiamondRow,m_nDiamondLine));
            m_pDiamond[m_nDiamondLine][m_nDiamondRow] = nullptr;
        }
        else
        {
			int diamondType = rand() % getDiamondType();
            

			Diamond *pDiamond = Diamond::createWithSpriteFrameName(getElementName(diamondType).c_str());
			pDiamond->setType(diamondType);
            
            addChild(pDiamond);
			pDiamond->setPosition(getCreatePos(m_nDiamondRow,m_nDiamondLine));
			m_pDiamond[m_nDiamondLine][m_nDiamondRow] = pDiamond;
            
		}

		if (++m_nDiamondRow == m_nDiamondRowMax)
        {
            m_nDiamondRow = 0;
            ++m_nDiamondLine;
        }

        if (m_nDiamondLine == m_nDiamondLineMax)
        {
            m_bIsReadyGoEnd = true;
            break;
        }
    }
}

void InGameScene::drawBg()
{
    for (auto line = 0; line < m_nDiamondLineMax; line++)
    {

        for (auto row = 0; row < 7; row++)
        {
            if(isObstacle(line, row))
            {
                continue;
            }
            auto sp1 = Sprite::create("gui/b1.png");
            auto sp2 = Sprite::create("gui/b2.png");

            if (line % 2 == 0)
            {
                if (row % 2 == 0)
                {
                    sp1->setPosition(getPositionByRowAndLine(row, line));
                    sp2->setVisible(false);
                }
                else
                {
                    sp2->setPosition(getPositionByRowAndLine(row, line));
                    sp1->setVisible(false);
                }
            }
            else
            {
                if (row % 2 == 0)
                {
                    sp2->setPosition(getPositionByRowAndLine(row, line));
                    sp1->setVisible(false);
                }
                else
                {
                    sp1->setPosition(getPositionByRowAndLine(row, line));
                    sp2->setVisible(false);
                }

            }

            addChild(sp1, BG_ODER);
            addChild(sp2, BG_ODER);
        }
    }
}


void InGameScene::DrawLine()
{

    auto line = Sprite::create("gui/line.png");
    line->setPosition(last_position);
    line->setAnchorPoint(Vec2(1, 0.5));
    addChild(line, -1);

    if (m_lineObjs == nullptr || m_nScore == 0)
    {
        m_lineObjs = __Array::create();
        m_lineObjs->retain();
        log("m_lineObjs inited");
        m_nScore = 1;
    }

    log("m_lineObjs add object");
    m_lineObjs->addObject(line);

    if (fabs(last_position.x - cur_position.x) < PAN)
    {
        if (last_position.y - cur_position.y > 1.0f)
        {
            // 向下
            line->setRotation(270);
        }
        else
        {
            line->setRotation(90);
        }
    }
    else if (fabs(last_position.y - cur_position.y) < PAN)
    {
        if (last_position.x - cur_position.x < 1.0f)
        {

            line->setRotation(180);
        }
    }
    else
    {
        if (last_position.x - cur_position.x < 1.0f)
        {
            if (last_position.y - cur_position.y < 1.0f)
            {
                line->setRotation(135);
            }
            else
            {
                line->setRotation(225);
            }
        }
        else
        {

            if (last_position.y - cur_position.y < 1.0f)
            {
                line->setRotation(45);
            }
            else
            {

                line->setRotation(315);
            }
        }
    }
}

void InGameScene::setupTag(Diamond *_obj, int line, int row)
{
    if (nullptr == _obj)
    {
        return;
    }

    _obj->setTag(line * m_nDiamondRowMax + row);
}

vector<Diamond * > InGameScene::getNearItem(int line, int row)
{
    vector<Diamond * > _retList;

    if (line > 0)
    {
        setupTag(m_pDiamond[line - 1][row], line - 1, row);
        _retList.push_back(m_pDiamond[line - 1][row]);

    }

    if (line < m_nDiamondLineMax - 1)
    {
        setupTag(m_pDiamond[line + 1][row], line + 1, row);
        _retList.push_back(m_pDiamond[line + 1][row]);
    }

    if (row > 0)
    {
        setupTag(m_pDiamond[line][row - 1], line, row - 1);
        _retList.push_back(m_pDiamond[line][row - 1]);
    }

    if (row < m_nDiamondRowMax - 1)
    {
        setupTag(m_pDiamond[line][row + 1], line, row + 1);
        _retList.push_back(m_pDiamond[line][row + 1]);
    }

    if (line > 0 && row > 3)
    {
        setupTag(m_pDiamond[line - 1][row - 4], line - 1, row - 4);
        _retList.push_back(m_pDiamond[line - 1][row - 4]);
    }

    if (line > 0 && row > 1)
    {
        setupTag(m_pDiamond[line - 1][row - 2], line - 1, row - 2);
        _retList.push_back(m_pDiamond[line - 1][row - 2]);
    }

    if (line < m_nDiamondLineMax && row < m_nDiamondRowMax - 2)
    {
        setupTag(m_pDiamond[line + 1][row + 2], line + 1, row + 2);
        _retList.push_back(m_pDiamond[line + 1][row + 2]);
    }

    if (line < m_nDiamondLineMax && row < m_nDiamondRowMax - 4)
    {
        setupTag(m_pDiamond[line + 1][row + 4], line + 1, row + 4);
        _retList.push_back(m_pDiamond[line + 1][row + 4]);
    }

    return _retList;
}
bool InGameScene::isNearby(int line, int row, int _type)
{

    if (line > 0 && m_pDiamond[line - 1][row]->getType() == _type)
    {
        return true;
    }

    if (line < m_nDiamondLineMax - 1 && m_pDiamond[line + 1][row]->getType() == _type)
    {
        return true;
    }

    if (row > 0 && m_pDiamond[line][row - 1]->getType() == _type)
    {
        return true;
    }

    if (row < m_nDiamondRowMax - 1 && m_pDiamond[line][row + 1]->getType() == _type)
    {
        return true;
    }

    if (line > 0 && row > 3 && m_pDiamond[line - 1][row - 4]->getType() == _type)
    {
        return true;
    }

    if (line > 0 && row > 1 && m_pDiamond[line - 1][row - 2]->getType() == _type)
    {
        return true;
    }

    if (line < m_nDiamondLineMax && row < m_nDiamondRowMax - 2 && m_pDiamond[line + 1][row + 2]->getType() == _type)
    {
        return true;
    }

    if (line < m_nDiamondLineMax && row < m_nDiamondRowMax - 4 && m_pDiamond[line + 1][row + 4]->getType() == _type)
    {
        return true;
    }

    return false;
}

void InGameScene::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    log("[onTouchMoved] ==== begin ==== ");
    if (m_moveStatus == 0)
    {
        log("[onTouchMoved] m_moveStatus is ZERO. Draw line is over!");
        return;
    }

    if (m_startType >= egg_number)
    {
        return;
    }
    
    if (m_startType < 0)
    {
        log("[onTouchMoved] m_startType(%d)!!", m_startType);
        return;
    }

    Vec2 location = pTouch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);

    for (int line = 0; line < m_nDiamondLineMax; ++line)
    {
        for (int row = 0; row < m_nDiamondRowMax; ++row)
        {
            if (!m_pDiamond[line][row])
            {
                continue;
            }

            if (m_pDiamond[line][row]->getReferenceCount() <= 0)
            {
                continue;
            }

            if (m_pDiamond[line][row]->getMoving())
            {
                continue;
            }

            if (m_pDiamond[line][row]->getType() >= egg_number)
            {
                continue;
            }

            if ((m_pDiamond[line][row])->boundingBox().containsPoint(location))
            {
                // 还在原来的格子里
                if (m_pRemovedDiamond->containsObject(m_pDiamond[line][row]))
                {
                    return;
                }

                ssize_t count = m_pRemovedDiamond->count();

                if (count > 0)
                {
                    deleteMask();
                    drawMask(m_startType);
                    
                    if(m_startType == m_pDiamond[line][row]->getType())
                    {
                        cur_position = getPositionByRowAndLine(row, line);
                        DrawLine();
                        last_position = cur_position;
                        m_pDiamond[line][row]->setScale(1.05);
                    }
                }
                
                if(m_startType == m_pDiamond[line][row]->getType())
                {
                    // 将自己加入到队列中去
                    m_pDiamond[line][row]->setTag(line * m_nDiamondRowMax + row);
                    log("[move]addObject(%p)", m_pDiamond[line][row]);
                    m_pRemovedDiamond->addObject(m_pDiamond[line][row]);
                }
                return;
            }
        }
    }
   
    log("onTouchMoved End ~");
}
bool InGameScene::touchColorItem(Vec2 v)
{
    Vec2 v1(165, 1280-193);
    Vec2 v2(265, 1280-1183);
    return TI()->isInScope(v, v1, v2);
}

bool InGameScene::touchRefreshItem(Vec2 v)
{
    Vec2 v1(131, 1280-193);
    Vec2 v2(256 , 1280 - 109);
    return TI()->isInScope(v, v1, v2);
}


bool InGameScene::touchMoveItem(Vec2 v)
{
    Vec2 v1(600, 1280-193);
    Vec2 v2(696, 1280-109);
    return TI()->isInScope(v, v1, v2);
}

// #began
bool InGameScene::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    log("[onTouchBegan] begin!");
    if (! m_bIsReadyGoEnd)
    {
        log("[onTouchBegan] m_bIsReadyGoEnd is false !");
        return true;
    }

	
    m_pRemovedDiamond->removeAllObjects();

    Vec2 location = pTouch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);

    if (touchRefreshItem(location))
    {
        doRefresh();
        log("touchRefreshItem");
        return true;
    }
    
    if (touchColorItem(location))
    {
        log("touchColorItem");
        if(USER()->getcolorItemNum() <= 0)
        {
            return true;
        }
        
        USER()->addcolorItemNum(-1);
        createItemDiamond(20);
        
        colorItemNum_->setString(TI()->_itos(USER()->getcolorItemNum()));
        return true;
    }
    
    if (touchMoveItem(location))
    {
        log("touchColorItem");
        if (UserData::getInstance()->getMoveItemNum() <= 0)
        {
            return true;
        }
        
        moves_number_ += 5;
        showMoveNumber();
        USER()->addMoveItemNum(-1);
        moveItemNum_->setString(TI()->_itos(USER()->getMoveItemNum()));
        return true;
    }
    
    
    for (int line = 0; line < m_nDiamondLineMax; ++line)
    {
        for (int row = 0; row < m_nDiamondRowMax; ++row)
        {
            if (m_pDiamond[line][row] && (! m_pDiamond[line][row]->getMoving()))
            {
                if ((m_pDiamond[line][row])->boundingBox().containsPoint(location))
                {

                    m_startType = m_pDiamond[line][row]->getType();
                    last_position = getPositionByRowAndLine(row, line);
                    log("m_starType %d", m_startType);

                    return true;
                }
            }
        }
    }

    return true;
}

void InGameScene::showMoveNumber()
{
    log("moves_number_(%d)", moves_number_);
    stringstream _ss;
    _ss.str("");
    _ss << moves_number_;
    m_pMoveLable->setString(_ss.str());
}

// #END
void InGameScene::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    deleteMask();
    m_moveStatus = -1;
    m_startType = -1;
    log("< moves_number_(%d)", moves_number_);

    if (!handleSelectedDiamond())
    {
        return;
    }

    Ref *pObj;
    CCARRAY_FOREACH(m_lineObjs, pObj)
    {
        auto sp = (Sprite *) pObj;
        sp->removeFromParent();
    }
    if (m_lineObjs!=nullptr)
    {
        m_lineObjs->removeAllObjects();
    }
    

    playSound("sounds/Remove.mp3");
    auto count = m_pRemovedDiamond->count();
    removeSelectedDiamond();
    schedule(schedule_selector(InGameScene::addRemovedDiamond), 1 / 40);
    createItemDiamond(count);
    
    moves_number_ = moves_number_ - 1;
    showMoveNumber();

    if (isGatherMode())
    {
        if (GameData::getInstance()->isWin(InGameScene::level))
        {
            return showTime();
        }
    }
    else
    {
        if (GameData::getInstance()->isWin(InGameScene::level, m_nScore))
        {
            return showTime();
        }
    }

    if (moves_number_ <= 0)
    {
        return showFail();
    }
}

Vec2 InGameScene::getRandomPosition()
{
    int line = 0;
    int row  = 0;
    
    while (1)
    {
        line = rand() % (m_nDiamondLineMax - 1);
        row = rand() % (m_nDiamondRowMax - 1);
    
        if (posMap_[line * m_nDiamondRowMax + row] != 1)
        {
            break;
        }
    }
    
    posMap_[line * m_nDiamondRowMax + row] = 1;
    
    return getPositionByRowAndLine(row, line);
}
void InGameScene::showTime()
{
    animList_.clear();
    posList_.clear();
    callJava("showAds", "");

    for (int i = 0; i < moves_number_ && i < 5; i++)
    {
   
        Vec2 pos = getRandomPosition();

        auto _move = MoveTo::create(MOVE_NUMBER_MOVE_TIME, pos);
        auto _fadain = FadeIn::create(0.2);
        auto _spawn  = Spawn::create(_move, _fadain, NULL);
        auto _callback = CallFuncN::create(this, callfuncN_selector(InGameScene::moveCallback));
        auto _seqeue = Sequence::create(_spawn, _callback, NULL);
        _seqeue->retain();

        animList_.push_back(_seqeue);
    }

    schedule(schedule_selector(InGameScene::playMoveAnim), getAnimTime());
}

void InGameScene::bombPos(int line, int row)
{
    auto _list = getNearItem(line, row);

    for (auto item : _list)
    {
        if (!item)
        {
            continue;
        }

        if (m_pRemovedDiamond->containsObject(item))
        {
            continue;
        }

        m_pRemovedDiamond->addObject(item);
    }

    if (m_pDiamond[line][row] == nullptr)
    {
        return;
    }

    setupTag(m_pDiamond[line][row], line, row);
    m_pRemovedDiamond->addObject(m_pDiamond[line][row]);

}


void InGameScene::bombAllBombs()
{
    for (auto tag : posList_)
    {
        int line = tag / m_nDiamondRowMax, row = tag % m_nDiamondRowMax;
        bombPos(line, row);
        
        auto _bomb = getChildByTag(1000 + tag);
        if (_bomb)
        {
            _bomb->setVisible(false);
        }
    }

    removeSelectedDiamond();
    schedule(schedule_selector(InGameScene::addRemovedDiamond), 1 / 40);
    //restoreOriginalDiamond();
    auto func = CallFuncN::create([this](Node * obj)->void
    {
        showWin();
    });

    auto delay = DelayTime::create(2);
    auto seq = Sequence::create(delay, func, NULL);
    runAction(seq);
}

void InGameScene::playMoveAnim(float dt)
{
    if (animList_.size() == 0)
    {
        unschedule(schedule_selector(InGameScene::playMoveAnim));
        bombAllBombs();
        return;
    }

    auto _seq = animList_[animList_.size() - 1];
    auto _sp = Sprite::create("gui/fire_ball.png");
    _sp->setPosition(MOVES_NUM_POSX, MOVES_NUM_POSY);
    addChild(_sp, 300);
    _sp->runAction(_seq);
    animList_.pop_back();
    moves_number_ -= 1;
    showMoveNumber();
}

void InGameScene::showFail()
{
    UserData::getInstance()->setScore(m_nScore);

    callJava("showAds", "");
    auto failLayer = FailLayer::create();
    failLayer->retain();
    addChild(failLayer, 10000);
    failLayer->setPosition(720 / 2, 1280 / 2);
}

void InGameScene::buttonCallback(Node *_obj)
{
    auto s = HelpScene::scene();
    auto t = TransitionFade::create(0.5, s);
    Director::getInstance()->replaceScene(t);
}

void InGameScene::showWin()
{
    GameData::getInstance()->num1 = 0;
    GameData::getInstance()->num2 = 0;
    GameData::getInstance()->num3 = 0;
    UserData::getInstance()->setScore(m_nScore);

    UserData::getInstance()->setScore(InGameScene::level, m_nScore);
    UserData::getInstance()->addSliver(3);
    UserData::getInstance()->addHp(1);
    
    GameResult *pl = GameResult::create("game_start.png");
    
    pl->setContentSize(Size(720, 1280));
    pl->setTitle("", 30);
    pl->setContentText("", 33, 80, 150);
    pl->setCallbackFunc(this, callfuncN_selector(InGameScene::buttonCallback));

    pl->addButton("start_bt.png", "start_bt.png", Vec2(720 / 2, 450), 10001);

    this->addChild(pl, 2000);

    if (UserData::getInstance()->getLevel() <= UserData::getInstance()->getSelLevel())
    {
        UserData::getInstance()->addLevel(1);
    }
}

float InGameScene::getAnimTime()
{
    return MOVE_NUMBER_MOVE_TIME + ITEM_FADEOUT_TIME + BOMB_SHOW_TIME;
}

void InGameScene::moveCallback(Node *pSender)
{
    Vec2 pos = pSender->getPosition();
    pSender->setVisible(false);

    for (int line = 0; line < m_nDiamondLineMax; ++line)
    {
        for (int row = 0; row < m_nDiamondRowMax; ++row)
        {
            if (m_pDiamond[line][row] == nullptr)
            {
                continue;
            }

            if ((m_pDiamond[line][row])->boundingBox().containsPoint(pos))
            {

                auto _delay   = DelayTime::create(ITEM_FADEOUT_TIME);
                auto _fadein  = FadeIn::create(BOMB_SHOW_TIME);
                auto _sequeue = Sequence::create(_delay, _fadein, NULL);

                auto _sp = Sprite::create("gui/item_bomb.png");
                addChild(_sp, 300);
                _sp->retain();

                _sp->runAction(_sequeue);
                _sp->setPosition(getPositionByRowAndLine(row, line));
                _sp->setTag(1000 + line * m_nDiamondRowMax + row);

                auto _fadeout = FadeOut::create(ITEM_FADEOUT_TIME);
                (m_pDiamond[line][row])->runAction(_fadeout);
                posList_.push_back(line * m_nDiamondRowMax + row);
                break;
            }
        }
    }
}

bool InGameScene::handleSelectedDiamond()
{
    auto count = m_pRemovedDiamond->count();

    if (count < 2)
    {
        m_nCrazyCount = 0;

        if (m_bIsCrazyMode)
        {
            m_bIsCrazyMode = false;
        }
        return false;
    }

    return true;
}

void InGameScene::update(float delta)
{
    ++m_nTimeCount;

    if (m_nTimeCount > 10)
    {


    }
}

//#addScore
void InGameScene::playJumpScore(int count)
{
    int m = 10;
    if(count < 4)
    {
        m = 20;
    }
    else if(m < 6)
    {
        m = 30;
    }
    else if(m < 8)
    {
        m = 80;
    }
    else if(m < 15)
    {
        m = 150;
    }
    else
    {
        m = 200;
    }



    m_nTempScore = count * 50 + m * (count - 2);
    m_nScore += m_nTempScore;

    schedule(schedule_selector(InGameScene::playJumpScoreUpdate), 0.4f / 60);
}

void InGameScene::playJumpScoreUpdate(float delta)
{
    if (m_nTempScore < 0)
    {
        __String *strScore = __String::createWithFormat("%d", m_nScore);
        m_pScoreLable->setString(strScore->getCString());
        this->unschedule(schedule_selector(InGameScene::playJumpScoreUpdate));
        return;
    }

    __String *strScore = __String::createWithFormat("%d", m_nScore - m_nTempScore);
    m_pScoreLable->setString(strScore->getCString());
    m_nTempScore -= InGameScene::baseScore[1] / 5;
}

void InGameScene::playDiamondExplosion(const Vec2 pos)
{
    Vector<SpriteFrame * > diamondExplosionNormalFrame;

    for (int i = 1; i < 10; ++i)
    {
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("gem_explosion_normal%d.png", i)->getCString());
        diamondExplosionNormalFrame.pushBack(frame);
    }

    Animation *diamondAnimation = Animation::createWithSpriteFrames(diamondExplosionNormalFrame, 0.05f);

    Sprite *explosion = Sprite::createWithSpriteFrameName("gem_explosion_normal1.png");
    explosion->setPosition(pos);
    this->addChild(explosion);
    //播放完消失时的动画
    explosion->runAction(Sequence::create(
                             Animate::create(diamondAnimation),
                             //播放完消失时的动画后，删除它
                             CallFuncN::create(this, callfuncN_selector(InGameScene::removeExplosionCallback)),
                             NULL));
}

void InGameScene::removeExplosionCallback(Node *pSender)
{
    this->removeChild(pSender, true);
}

void InGameScene::removeSelectedDiamond(int flag)
{
    Diamond *removed = NULL;
    Ref *pObj = NULL;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    
    if(flag != 1)
    {
    	trigerItem();
    }
    
    playJumpScore(m_pRemovedDiamond->count());
    CCARRAY_FOREACH(m_pRemovedDiamond, pObj)
    {
        removed = (Diamond *)pObj;

        if (removed == NULL)
        {
            continue;
        }

        if (removed->getType() == 0)
        {
            num1++;
        }

        if (removed->getType() == 1)
        {
            num2++;
        }

        if (removed->getType() == 2)
        {
            num3++;
        }

        int tag = removed->getTag();
        if (tag < 0)
        {
            continue;
        }

        int line = tag / m_nDiamondRowMax, row = tag % m_nDiamondRowMax;

        if (m_pDiamond[line][row] ==  nullptr)
        {
            continue;
        }

        if (TI()->isDiamond())
        {
            auto _sp = getChildByTag(tag);
            if (nullptr == _sp || removed != _sp)
            {
                continue;
            }
            removeChildByTag(tag);
        }
        else
        {
            auto _sp = m_pDiamondBatchNode->getChildByTag(tag);
            if (nullptr == _sp || removed != _sp)
            {
                continue;
            }
   	
            m_pDiamondBatchNode->removeChild(removed, true);
        }
        m_pDiamond[line][row] = nullptr;
    }

    updateGatherNumber(num1, num2, num3);

}

void InGameScene::addRemovedDiamond(float delta)
{
    int toLine, toRow;
    for (toLine = 0; toLine < m_nDiamondLineMax ; ++toLine)
    {
        for (toRow = 0; toRow < m_nDiamondRowMax ; ++toRow)
        {
            if (m_pDiamond[toLine][toRow] == NULL) //被删除掉的宝石的位置，即要掉落的目的地
            {
                
                if (isObstacle(toLine, toRow))
                {
                    continue;
                }
                
                int fromLine;
				
                for (fromLine = toLine + 1; fromLine < m_nDiamondLineMax; ++fromLine)
                {
                    //被删除宝石的上方第一个存在，并处于固定状态，即没有在移动中的宝石
                    if (m_pDiamond[fromLine][toRow])
                    {
                        if (isObstacle(fromLine, toRow))
                        {
                            continue;
                        }
                        //播放宝石被添加时掉落的效果
                        if (m_pDiamond[fromLine][toRow]->getMoving())
                        {
                            m_pDiamond[fromLine][toRow]->stopAllActions();
                        }

                        m_pDiamond[fromLine][toRow]->setMoving(true);

                        auto func = CallFuncN::create(this, callfuncN_selector(InGameScene::addEndCallback));
                        auto moveto = MoveTo::create(0.25f, Vec2(100 * toRow + 50, 100 * toLine + 220));

                        auto seq = Sequence::create(moveto, func, NULL);
                        setupTag(m_pDiamond[fromLine][toRow], toLine, toRow);
                        m_pDiamond[fromLine][toRow]->runAction(seq);

                        m_pDiamond[toLine][toRow] = m_pDiamond[fromLine][toRow];

                        m_pDiamond[fromLine][toRow] = NULL;

                        return;
                    }
                }

                if (fromLine == m_nDiamondLineMax)
                {
                    int diamondType = rand() % getDiamondType();
                    Diamond *pDiamond = Diamond::createWithSpriteFrameName(getElementName(diamondType).c_str());
                    pDiamond->setType(diamondType);

                    int num = rand() % 10 ;
                    TargetDataEx ret = GameData::getInstance()->getTargetEx(InGameScene::level);

                    if (num > 8 && isRecsue_ && egg_num_ < ret.num1_ + 2)
                    {
                        pDiamond = Diamond::createWithSpriteFrameName("egg.png");
                        pDiamond->setType(egg_number);
                    }

                    pDiamond->setPosition(Vec2(100 * toRow + 50, 1280 + 100));
                    if (TI()->isDiamond())
                    {
                        addChild(pDiamond, 2);
                    }
                    else
                    {
                        m_pDiamondBatchNode->addChild(pDiamond, 2);
                    }
                    //播放宝石被添加时掉落的效果
                    pDiamond->setMoving(true);
                    setupTag(pDiamond, toLine, toRow);

                    auto moveto = MoveTo::create(.25f, Vec2(100 * toRow + 50, 100 * toLine + 220));
                    auto func = CallFuncN::create(this, callfuncN_selector(InGameScene::addEndCallback));
                    auto seq = Sequence::create(moveto, func, NULL);

                    pDiamond->runAction(seq);

                    m_pDiamond[toLine][toRow] = pDiamond;
                }

                return;
            }
        }
    }

    if ((toLine == m_nDiamondLineMax) && (toRow == m_nDiamondRowMax))
    {
        this->unschedule(schedule_selector(InGameScene::addRemovedDiamond));
        m_moveStatus = -1;

        if (m_bFireballMode)
        {
            m_bFireballMode = false;
        }
    }
}

void InGameScene::addEndCallback(Node *pSender)
{
    auto diamond = (Diamond *)pSender;
    auto tag = diamond->getTag();

    int toLine = tag / m_nDiamondRowMax, toRow = tag % m_nDiamondRowMax;

    diamond->setMoving(false);

    if (diamond->itemObj_ != nullptr)
    {
        diamond->itemObj_->setPosition(diamond->getPosition() - Vec2(-25, 25));
    }

    if (diamond->getType() == egg_number)
    {
        if (toLine == 0)
        {
            m_pDiamond[0][toRow] = nullptr;
            addRemovedDiamond(0.1f);
        }
    }
    drawItemIcon();
}

string InGameScene::getItemIconName(int type)
{
    switch (type)
    {
    case CLEAR_ONE_LINE:
        return "gui/item_line.png";

    case CLEAR_ONE_ROW:
        return "gui/item_row.png";

    case ITEM_BOMB:
        return "gui/bomb.png";

    case ITEM_ONE_COL:
        return "gui/item_bomb2.png";

    default:
        break;
    }

    return "item_line.png";
}

void InGameScene::deleteMask()
{
    for(int i = 20000; i < m_nDiamondLineMax*m_nDiamondRowMax+20000; i++)
    {
        auto old = getChildByTag(i);
        if (old)
        {
            old->removeFromParentAndCleanup(true);
        }
    }
}
void InGameScene::drawMask(int type)
{
    
    int index = 0;
    for (int line = 0; line < m_nDiamondLineMax; ++line)
    {
        for (int row = 0; row < m_nDiamondRowMax; ++row)
        {
            auto sp = m_pDiamond[line][row];
            if(sp == nullptr)
            {
                continue;
            }
            
            if (sp->getType() != type)
            {
                auto p = Sprite::create("gui/b3.png");
                addChild(p, 4);
                p->setPosition(sp->getPosition());
                p->setTag(index + 20000);
                index++;
            }
        }
    }
}

void InGameScene::drawItemIcon()
{
    
    for(int i = 10000; i < m_nDiamondLineMax*m_nDiamondRowMax+10000; i++)
    {
        auto old = getChildByTag(i);
        if (old)
        {
            old->removeFromParentAndCleanup(true);
        }
    }
    int index = 0;
    for (int line = 0; line < m_nDiamondLineMax; ++line)
    {
        for (int row = 0; row < m_nDiamondRowMax; ++row)
        {
            auto sp = m_pDiamond[line][row];
            if(sp == nullptr)
            {
                continue;
            }
      
            if (sp->getItemType() > -1)
            {
                auto p = Sprite::create(getItemIconName(sp->getItemType()));
                addChild(p, 3);
                p->setPosition(sp->getPosition());
                p->setTag(index + 10000);
                index++;
                TI()->shakeNode(p);
            }
        }
    }
}
void InGameScene::createItemDiamond(int count)
{
    if (count < 5)
    {
        return;
    }

    int row = -1, line = -1;

    while (1)
    {
        row = RANDOM_RANGE(0, m_nDiamondRowMax - 0.01);
        line = RANDOM_RANGE(0, m_nDiamondLineMax - 0.01);

        if (m_pDiamond[line][row])
        {
            break;
        }
    }

    auto diamond = m_pDiamond[line][row];

    if (count < 10)
    {
        row = RANDOM_RANGE(1, 2.9);
    }
    else
    {
        row = ITEM_ONE_COL;
    }

    diamond->setItemType(row);
    if (TI()->isDiamond())
    {
        return;
    }
    
    auto name = getImageName(diamond->getType());
    if (row == CLEAR_ONE_LINE)
    {
        name = name + "_line.png";
    }
    else if (row == CLEAR_ONE_ROW)
    {
        name = name + "_row.png";
    }
    else if(row == ITEM_ONE_COL)
    {
        name = name + "_bomb.png";
    }

    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
    diamond->setDisplayFrame(frame);
}

void InGameScene::removedOneLine(int _line)
{
    for (int line = 0; line < m_nDiamondLineMax; ++line)
    {
        for (int row = 0; row < m_nDiamondRowMax; ++row)
        {
            if (line == _line)
            {
                auto diamond = m_pDiamond[line][row];

                if (!diamond)
                {
                    continue;
                }

                if (m_pRemovedDiamond->containsObject(diamond))
                {
                    continue;
                }
                log("[oneLine]addObject(%p)", diamond);
                m_pRemovedDiamond->addObject(diamond);
            }
        }
    }
}
void InGameScene::removedOneRow(int _row)
{
    for (int line = 0; line < m_nDiamondLineMax; ++line)
    {
        for (int row = 0; row < m_nDiamondRowMax; ++row)
        {
            if (row == _row)
            {
                auto diamond = m_pDiamond[line][row];

                if (!diamond)
                {
                    continue;
                }

                if (m_pRemovedDiamond->containsObject(diamond))
                {
                    continue;
                }
				log("[oneRow]addObject(%p)", diamond);
                m_pRemovedDiamond->addObject(diamond);
            }
        }
    }
}

void InGameScene::removeOneColor(int type)
{
    for (int line = 0; line < m_nDiamondLineMax; ++line)
    {
        for (int row = 0; row < m_nDiamondRowMax; ++row)
        {

            auto diamond = m_pDiamond[line][row];
            if (!diamond)
            {
                continue;
            }

            if (m_pRemovedDiamond->containsObject(diamond))
            {
                continue;
            }

            if (diamond->getType() != type)
            {
                continue;
            }

            m_pRemovedDiamond->addObject(diamond);
        }
    }
}

void InGameScene::trigerItem()
{
    Ref *pObj;
    int itemType = -1;
    Diamond* sp = nullptr;
    
    CCARRAY_FOREACH(m_pRemovedDiamond, pObj)
    {
        sp = (Diamond *)pObj;
        CCASSERT(sp, "sp got nil!");
        
        itemType = sp->getItemType();
        log("<trigItem> itemType(%d)", itemType);
        if (itemType > 0)
        {
            break;
        }
    }
    
    auto tag = sp->getTag();
    
    int line = tag / m_nDiamondRowMax;
    int row = tag % m_nDiamondRowMax;
    
    if (itemType == CLEAR_ONE_LINE)
    {
        removedOneLine(line);
    }
    
    if (itemType == CLEAR_ONE_ROW)
    {
        removedOneRow(row);
    }
    
    if (itemType == ITEM_ONE_COL)
    {
        removeOneColor(sp->getType());
    }
}

void InGameScene::addRemovedDiamondCallback(Node *pSender)
{
    this->removeChild(pSender);
    this->schedule(schedule_selector(InGameScene::addRemovedDiamond), 1 / 40);
}

void InGameScene::menuPauseCallback(Ref *pSender)
{
    InGameScene::isPaused = true;


    this->unscheduleUpdate();
   

    m_pPause = PauseLayer::create();
    m_pPause->retain();
    this->addChild(m_pPause, 100);

    this->schedule(schedule_selector(InGameScene::updatePaused), 1 / 60);
}

void InGameScene::updatePaused(float delta)
{
    if (! InGameScene::isPaused)
    {

        this->unschedule(schedule_selector(InGameScene::updatePaused));
        this->removeChild(m_pPause);
        CC_SAFE_RELEASE_NULL(m_pPause);

        this->scheduleUpdate();
    }
}

