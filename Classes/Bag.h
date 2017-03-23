#ifndef _Itembag_H_
#define _Itembag_H_

#include "Item.h"
#include <vector>
using namespace std;
#define BAG_SIZE 3
string icons[] =    {"item1.png","item2.png","item3.png" };
int max_numbers[] = { 3,3,3 };

class Bag
{
public:
    Bag() :number_(0)
        , maxItemNumber_(999)
    {

    }

    void init()
    {
        for (int i = 0; i < BAG_SIZE; i++)
        {
            auto item = new Item();
            item->init((1000+i), max_numbers[i], icons[i]);
            itemArray_.push_back(item);
            item->load();
        }
    }

    Item* get(int itemId, int num = 1)
    {
        auto item = find(itemId);
        if (!item)
        {
            return nullptr;
        }
        
        item->add(num);
        item->save();
        return item;
    }


    void use(int itemId, int num = 1)
    {
        auto item = find(itemId);
        if (!itemId)
        {
            return;
        }

        item->sub(num);
        item->save();
    }

    Item* find(int itemId)
    {
        for (auto item : itemArray_)
        {
            if (!item)
            {
                continue;
            }
            if (item->getId() == itemId)
            {
                return item;
            }
        }

        return nullptr;
    }


    static Bag* getInstance()
    {
        if (instance_ == nullptr)
        {
            instance_ = new Bag;
            instance_->init();
        }

        return instance_;
    }


private:
    /**
    * item 数量
    */
    int number_;
    /**
    * item最大数量
    */
    int maxItemNumber_;
    /**
    * item id
    */
    int id_;

    vector<Item * > itemArray_;

    static Bag* instance_;
};

#define BAGI Bag::getInstance

// BAGI->get(1000,1);
// auto item  = BAGI->find(1000);
#endif // !_Item_H_
