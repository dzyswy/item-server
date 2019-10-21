#ifndef __ITEM_VALUE_H
#define __ITEM_VALUE_H


#include <iostream>
#include <sstream>
#include <functional>
#include <vector>
#include <map>
#include <typeinfo>
#include <mutex>
#include <thread>
#include <condition_variable>





class item_value
{
public:
	item_value(int value);
	item_value(float value);
	item_value(std::string value);
	
	int asInt();
	float asFloat();
	std::string asString();

protected:
	std::string value_;
};













#endif

