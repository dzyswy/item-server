#ifndef __RPC_ITEMS_H
#define __RPC_ITEMS_H

#include <iostream>
#include <sstream>
#include <functional>
#include <vector>
#include <typeinfo>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "item_value.h"


struct rpc_item
{
	std::string key;
	std::function<int(item_value)> set;
	std::function<item_value(item_value)> get;
};




class rpc_items
{
public:
	rpc_items(int debug = 0);
	~rpc_items();
	void add_item(const std::string key, std::function<int(item_value)> set, std::function<item_value(item_value)> get = NULL);
	int handle(std::string &request, std::string &result);
	
protected:	
	void split_string(std::string s, std::vector<std::string>& sv, const char c = ' ');
	
protected:
	int debug_;
	std::map<std::string, struct rpc_item> items_;
	
};










#endif

