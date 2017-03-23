
#ifndef _h_AnimHelp_h
#define _h_AnimHelp_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;


struct SeqData : public Node
{
    SeqData():seq_(NULL)
    ,dt_(0.1f)
    ,obj_(NULL)
    {
        
    }
    
    CREATE_FUNC(SeqData);
    
    Sequence* seq_;
    float     dt_;
    Node*     obj_;
};

class AnimHelp
{
public:
     	void callOut(Node* _obj, float dt, SEL_CallFuncND func)
     	{
     		if (!_obj)
     		{
     			log("[CallOut] obj got nil!");
     			return;
     		}
     		auto _dt = DelayTime::create(dt);
     		auto _sq = Sequence::create(_dt, func, NULL);
    
     		_obj->runAction(_sq);
     	}
    
    AnimHelp() :index_(0)
               ,inited_(false)
    
    {
        
    }
    void init(vector<SeqData*>   _seq)
    {
        seq_ = _seq;
        index_ = 0;
        inited_ =true;
    }
    
    Sequence* getAnim()
    {
        SeqData* data = seq_[index_];
        if (!data)
        {
            return nullptr;
        }
        return data->seq_;
    }
    
    float getTime()
    {
        SeqData* data = seq_[index_];
        
        if (!data)
        {
            return 5.f;
        }
        
        return data->dt_;
    }
    void setIndex(int _index)
    {
        index_ = _index;
    }
    
    int getIndex()
    {
        return index_;
    }
    
    int getLength()
    {
        return seq_.size();
    }
    bool inited()
    {
        return inited_;
    }
    Node* getObj()
    {
        SeqData* data = seq_[index_];
        log("[getObj]index = %d", index_);
        if (!data)
        {
            return nullptr;
        }
        return data->obj_;
    }
    
    static AnimHelp* getInstance()
    {
        if (NULL == instance_)
        {
            instance_ = new AnimHelp;
        }
        return instance_;
    }
    
private:
    static AnimHelp* instance_;
    vector<SeqData* > seq_;
    int index_;
    bool inited_;
};


#define HEARTBEAT(classname, func) public: \
vector<SeqData*> vec##func##_; \
public: \
void func(float dt) \
{ \
	if(vec##func##_.empty()) \
	{ \
        return; \
    } \
    if(!AnimHelp::getInstance()->inited()) \
    { \
		AnimHelp::getInstance()->init(vec##func##_); \
    }\
    auto _index = AnimHelp::getInstance()->getIndex(); \
    auto length = AnimHelp::getInstance()->getLength(); \
\
    if (length == _index) \
    { \
        unschedule(schedule_selector(classname::func));\
        return; \
    } \
\
    unschedule(schedule_selector(classname::func)); \
    schedule(schedule_selector(classname::func), AnimHelp::getInstance()->getTime()); \
    Node* obj = AnimHelp::getInstance()->getObj() ; \
	if(obj == nullptr) return; \
	obj->runAction(AnimHelp::getInstance()->getAnim()); \
    _index++; \
    AnimHelp::getInstance()->setIndex(_index); \
}


#endif
