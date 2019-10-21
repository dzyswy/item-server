#ifndef __ITEM_SERVER_H
#define __ITEM_SERVER_H

#include <iostream>
#include <sstream>
#include <functional>
#include <vector>
#include <typeinfo>
#include <mutex>
#include <thread>
#include <condition_variable>


#include "item_value.h"


class rpc_impl;
class rpc_items;
class cfg_items;


class item_server
{
public:
	item_server(int port, const char *config_name, int debug = 0);
	~item_server();
	void add_item(const char *key, std::function<int(item_value)> set, std::function<item_value(item_value)> get = NULL, const char *default_value = NULL, const char *section = NULL);
	void run();
	void stop();
	int save_config();
	int load_config();
	
protected:
	rpc_impl *impl_r_;
	rpc_items *items_r_;
	cfg_items *items_c_;
	std::thread *run_thread_;
};










#endif

