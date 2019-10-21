#include "item_server.h"

#include <iostream>
#include <string>
#include <asio.hpp>
#include "server.hpp"
#include "rpc_items.h"
#include "cfg_items.h"





using namespace std;





class rpc_impl
{
public:
	rpc_impl(int port, rpc_items *items_r)
	{
		string _ip = "0.0.0.0";
		string _port = std::to_string(port);
		string _doc_root = ".";
		srv_ = new http::server::server(_ip, _port, _doc_root, *items_r);
	}
	
	~rpc_impl()
	{
		delete srv_;
	}
	
	void run()
	{
		srv_->run();
	}
	
	void stop()
	{
		srv_->stop();
	}

protected:
	http::server::server *srv_;	
	
};




item_server::item_server(int port, const char *config_name, int debug)
{
	items_r_ = new rpc_items(debug);
	items_c_ = new cfg_items(config_name);
	impl_r_ = new rpc_impl(port, items_r_);
}

item_server::~item_server()
{
	delete impl_r_;
	delete items_r_;
	delete items_c_;
}

 
void item_server::add_item(const char *key, std::function<int(item_value)> set, std::function<item_value(item_value)> get, const char *default_value, const char *section)
{
	if (section)
	{
		items_c_->add_item(section, key, default_value, set, get);
	}
	
	items_r_->add_item(key, set, get);
}

void item_server::run()
{
	run_thread_ = new std::thread([this] () {impl_r_->run();printf("rpc server done!\n");});
}

void item_server::stop()
{
	impl_r_->stop();
	if (run_thread_)
	{
		run_thread_->join();
		delete run_thread_;
	}
}

int item_server::save_config()
{
	return items_c_->save_config();
}

int item_server::load_config()
{
	return items_c_->load_config();
}













