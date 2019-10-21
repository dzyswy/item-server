#include "cfg_items.h"




using namespace std;




cfg_items::cfg_items(const char *config_name)
{
	config_name_ = config_name;
}

cfg_items::~cfg_items()
{
	items_.clear();
}



void cfg_items::add_item(const char *section, const char *key, const char *default_value, std::function<int(item_value)> set, std::function<item_value(item_value)> get)
{
	struct cfg_item item;
	item.section = section;
	item.key = key;
	item.default_value = default_value;
	item.set = set;
	item.get = get;
	items_.push_back(item);
}



int cfg_items::save_config()
{
	int ret;
	CSimpleIniA ini;
	ini.SetUnicode();
	ret = ini.LoadFile(config_name_.c_str());
	if (ret < 0)
		return -1;
	
	for (int i = 0; i < items_.size(); i++)
	{
		struct cfg_item &item = items_[i];
		item_value val((int)0);
		string value = item.get(val).asString();
		
		ini.SetValue(item.section.c_str(), item.key.c_str(), value.c_str());
		std::cout << "save " << item.section << "." << item.key << "=" << value << std::endl;	
	}	
	
	ret = ini.SaveFile(config_name_.c_str());
	if (ret < 0)
		return -1;
	
	return 0;
}

int cfg_items::load_config()
{
	int ret;
	CSimpleIniA ini;
	ini.SetUnicode();
	ret = ini.LoadFile(config_name_.c_str());
	if (ret < 0)
		return -1;
	
	for (int i = 0; i < items_.size(); i++)
	{
		struct cfg_item &item = items_[i];
		string value = ini.GetValue(item.section.c_str(), item.key.c_str(), item.default_value.c_str());
		item_value val(value);
		item.set(val); 
		std::cout << "load " << item.section << "." << item.key << "=" << value << std::endl;
	
	}	
	
	return 0;
}








