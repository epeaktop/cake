#ifndef _Item_H_
#define _Item_H_

#include <iostream>

using namespace std;
class Item
{
public:
    Item():number_(0)
        ,maxItemNumber_(999)
    {

    }

    void init(int id, int maxNum, string iconUrl)
    {
        id_ = id;
        maxItemNumber_ = maxNum;
        icon_ = iconUrl;
    }
    void add(int num)
    {
        if (num<=0)
        {
            return;
        }
        auto tmp = num + number_;
        if (tmp > maxItemNumber_)
        {
            number_ = maxItemNumber_;
            return;
        }

        number_ = tmp;
    }

    void sub(int num)
    {
        if (num <= 0)
        {
            return;
        }
        auto tmp = number_ - num;
        if (tmp < 0 )
        {
            number_ = 0;
            return;
        }

        number_ = tmp;
    }


    void use()
    {
        sub(1);
    }

    int getId()
    {
        return id_;
    }

    void load();
    void save();


    string getSaveName();
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
    string icon_;
};


#endif // !_Item_H_
