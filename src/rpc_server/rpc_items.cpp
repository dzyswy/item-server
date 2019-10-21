#include "rpc_items.h"



using namespace std;



rpc_items::rpc_items(int debug)
{
	debug_ = debug;
}

rpc_items::~rpc_items()
{
	items_.clear();
}


void rpc_items::add_item(const std::string key, std::function<int(item_value)> set, std::function<item_value(item_value)> get = NULL)
{
	struct rpc_item item;
	item.key = key;
	item.set = set;
	item.get = get;
	items_.insert(make_pair(key, item));
}

int rpc_items::handle(std::string &request, std::string &result)
{
	int ret;
	std::vector<std::string> ss;
	split_string(request, ss, '&');
	
	if (debug_)
		cout << request << endl;
	
	//request:   /set&detect_mode&1& /get&detect_mode&null& /set&save_config&null&
	ret = ss.size();
	if (ret < 3)
		return -3;
	
	int action = (strncmp(ss[0].c_str(), "set", strlen("set")) == 0) ? 1:0;
	string key = ss[1]; 
	string value = ss[2];
	
	if (debug_) {
		cout << "action=" << action << ", key=" << key << ", value=" << value << endl;
	}
	 
	typename std::map<std::string, struct rpc_item>::iterator it;
	it = items_.find(key);
	if (it == items_.end())
		return -2;
	
	
	if (action) {
		item_value val(value);
		return it->second.set(value);
	} else {
		item_value val(value);
		item_value res = it->second.get(val);
		result = res.asString();
		return 0; 
	}
}


void rpc_items::split_string(std::string s, std::vector<std::string>& sv, const char c) 
{
    sv.clear();
    istringstream iss(s);
    string temp;
	
    while (std::getline(iss, temp, c)) {
        sv.push_back(temp);
    } 
}















