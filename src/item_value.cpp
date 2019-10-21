#include "item_value.h"


using namespace std;




item_value::item_value(int value)
{
	value_ = std::to_string(value);
}

item_value::item_value(float value)
{
	value_ = std::to_string((double)value);
}

item_value::item_value(std::string value)
{
	value_ = value;
}


int item_value::asInt()
{
	return atoi(value_.c_str());
}

float item_value::asFloat()
{
	return atof(value_.c_str());
}

std::string item_value::asString()
{
	return value_;
}
