#pragma once
#include <windows.h>
#include <iostream>
#include <Shlwapi.h>
#include <direct.h>
#include <shlobj.h>
#include <algorithm>

#define INSTALL 1
#define NO_INSTALL 0
using namespace std;
class config
{
private:
	string base_path = string(getexepath().append("\\config.ini"));

public:
	typedef struct configurations
	{
		bool chrome;
		bool firefox;
		bool java;
		bool skype;
		bool reader;
		bool vlc;
		bool mse;
		bool copy_tv;
		bool drivereasy;
		bool winrar;
	}configurations;
	BOOL get_info(string name);
	string getexepath();
	configurations configure();
	BOOL is64();
	string getdesktop();
};

