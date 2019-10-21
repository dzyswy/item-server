#include "item_server.h"
#include <iostream>
#include <errno.h>
#include <signal.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



using namespace std;


static int going = 1;

void signal_handler(int sig)
{
	going = 0;
	printf("receive signal!\n");
}


int main(int argc, char *argv[])
{
	int ret;
	if (argc != 3)
	{
		printf("usage: %s port *.ini\n", argv[0]);
		return -1;
	}	
	
	int port = atoi(argv[1]);
	string config_name = argv[2];
	
	if(signal(SIGINT, signal_handler) == SIG_ERR) {
        return -1;
    }
	
	int ival = 0;
	float fval = 0;
	string sval = "hello world";
	
	auto set_ival = [&] (item_value value) {ival = value.asInt(); return 0;};
	auto set_fval = [&] (item_value value) {fval = value.asFloat(); return 0;};
	auto set_sval = [&] (item_value value) {sval = value.asString(); return 0;};
	
	auto get_ival = [&] (item_value value) {item_value val(ival); return val;};
	auto get_fval = [&] (item_value value) {item_value val((float)fval); return val;};
	auto get_sval = [&] (item_value value) {item_value val(sval); return val;};
	
	auto save_config = [&] (item_value value) {printf("main save_config!\n"); return 0;};
	
	
	item_server server(port, config_name.c_str(), 1);
	server.add_item("ival", set_ival, get_ival, "5", "item_server");
	server.add_item("fval", set_fval, get_fval, "6", "item_server");
	server.add_item("sval", set_sval, get_sval, "haha", "item_server");
	server.add_item("save_config", save_config);
	
	ret = server.load_config();
	if (ret < 0)
		return -1;
	
	server.run();
	
	while(going)
	{
		cout << "ival:" << ival << endl;
		cout << "fval:" << fval << endl;
		cout << "sval:" << sval << endl;
		cout << "going:" << going << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}	
	
	ret = server.save_config();
	if (ret < 0)
		return -1;
	server.stop();
	
	printf("test ok!\n");
	
	return 0;
}


































