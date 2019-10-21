#ifndef __ASYNC_CLIENT_H
#define __ASYNC_CLIENT_H


#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <asio.hpp>


using namespace asio;
using namespace asio::ip; 



class async_client
{
public:
	async_client(std::string ip, int port, std::string request);
	~async_client();
	int get_result(std::string &result, int timeout = 5);
	
protected:
	void do_connect(ip::tcp::endpoint &ep);
	void do_write_request();
	void do_read_status_line();
	void do_read_headers();
	
protected:
	asio::io_context io_context_;
	tcp::socket socket_;
	asio::streambuf request_;
	asio::streambuf response_;
	
	std::string request_s_;
	
	int ret_;
	std::string result_;

	std::mutex mux_;
	std::condition_variable cond_;
	std::thread *run_thread_;
};















#endif


