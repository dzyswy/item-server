#include "rpc_client.h"



using namespace std;


int main(int argc, char *argv[])
{
	int ret;
	if (argc != 3)
	{
		printf("usage: %s ip port\n", argv[0]);
		return 0;
	}	
	
	string ip = argv[1];
	int port = atoi(argv[2]);
	
	rpc_client client;
	client.set_connect(ip.c_str(), port);
	
	int ival = 0;
	float fval = 0;
	string sval = "";
	
	ret = client.set_value("ival", 10, 5);
	if (ret < 0)
		return -1;
	
	ret = client.get_value("ival", ival, 5);
	if (ret < 0)
		return -1;
	
	ret = client.set_value("fval", 11, 5);
	if (ret < 0)
		return -1;
	
	ret = client.get_value("fval", fval, 5);
	if (ret < 0)
		return -1;
	
	ret = client.set_value("sval", "192.168.3.55", 5);
	if (ret < 0)
		return -1;
	
	ret = client.get_value("sval", sval, 5);
	if (ret < 0)
		return -1;
	
	ret = client.do_action("save_config", 5);
	if (ret < 0)
		return -1;
	
	cout << "ival:" << ival << endl;
	cout << "fval:" << fval << endl;
	cout << "sval:" << sval << endl;
	
	return 0;
}


















