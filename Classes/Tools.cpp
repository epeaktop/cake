#include "Tools.h"
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include <cocos2d.h>

using namespace std;

USING_NS_CC;

Tools* Tools::instance_ = nullptr;


Tools*  Tools::getInstance()
{
    if (nullptr == instance_)
    {
        instance_ = new Tools;
    }
    return instance_;
}

std::vector<std::string> Tools::split(const std::string &s, char delim) 
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }

    return elems;
}
#include <sstream>

int Tools::_stoi(string s)
{
    stringstream _ss(s);
    int num;
    _ss >> num;
    return num;
}

string Tools::_itos(int s)
{
    stringstream _ss;
    _ss.str("");
    _ss << s;
    return _ss.str();
}

int Tools::string2number(string str)
{
    if (str.length() != 3)
    {
        return -1;
    }

    if (str[0] == '0' && str[1] == '0' && str[2] == '0')
    {
        return 0;
    }
    else if (str[0] == '0' && str[1] == '0')
    {
        string _s = str.substr(2, 2);
        return _stoi(_s);
    }
    else if (str[0] == '0')
    {
        string _s = str.substr(1, 2);
        return _stoi(_s);
    }
    else
    {
        return _stoi(str);
    }
    return 0;
}

float Tools::getHeigh()
{
    auto size = Director::getInstance()->getWinSize();
    return size.height;
}

bool Tools::isInScope(Vec2 v,Vec2 v1, Vec2 v2)
{
	if (v.x < v2.x && v.x > v1.x)
	{
		if (v.y > v1.y && v.y < v2.y)
		{
			return true;
		}
	}

	return false;
}

float Tools::getWidth()
{
    auto size = Director::getInstance()->getWinSize();
    return size.width;
}








