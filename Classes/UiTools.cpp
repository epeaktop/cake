#include "UiTools.h"
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>

using namespace std;

UiTools* UiTools::instance_ = nullptr;


UiTools*  UiTools::getInstance()
{
    if (nullptr == instance_)
    {
        instance_ = new UiTools;
    }
    return instance_;
}
