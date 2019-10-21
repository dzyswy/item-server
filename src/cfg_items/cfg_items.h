#ifndef __CFG_ITEMS_H
#define __CFG_ITEMS_H


#include <iostream>
#include <functional>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
# pragma warning(disable: 4786)
#endif

#include <locale.h>
#include <stdio.h>
#include <cassert>

#define SI_SUPPORT_IOSTREAMS
#if defined(SI_SUPPORT_IOSTREAMS) && !defined(_UNICODE)
# include <fstream>
#endif

//#define SI_CONVERT_GENERIC
//#define SI_CONVERT_ICU
//#define SI_CONVERT_WIN32
#include "SimpleIni.h"

#ifdef SI_CONVERT_ICU
// if converting using ICU then we need the ICU library
# pragma comment(lib, "icuuc.lib")
#endif

#ifdef _WIN32
# include <tchar.h>
#else // !_WIN32
# define TCHAR      char
# define _T(x)      x
# define _tprintf   printf
# define _tmain     main
#endif // _WIN32


#include "item_value.h"


struct cfg_item
{
	std::string section;
	std::string key;
	std::string default_value;
	std::function<int(item_value)> set;
	std::function<item_value(item_value)> get;
};


class cfg_items
{
public:
	cfg_items(const char *config_name);
	~cfg_items();
	void add_item(const char *section, const char *key, const char *default_value, std::function<int(item_value)> set, std::function<item_value(item_value)> get);
	int save_config();
	int load_config();
	
protected:
	std::string config_name_;
	std::vector<struct cfg_item> items_;
};








#endif

