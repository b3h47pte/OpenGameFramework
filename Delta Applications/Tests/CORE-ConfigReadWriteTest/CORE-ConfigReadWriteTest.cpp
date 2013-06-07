// CORE-ConfigReadWriteTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WConfigFile.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	WConfigFile newConfig("test.ogfconfig");
	newConfig.SetFloatData(std::string("Section"), "key1", 0.5f);
	newConfig.SetFloatData(std::string("Section"), "key2", 1.0f);
	newConfig.SetFloatData(std::string("Section"), "key3", 2.0f);
	newConfig.SetIntData(std::string("defAult"), "key1", 0);
	newConfig.SetIntData(std::string("DEfAult"), "key2", 1);
	newConfig.SetIntData(std::string("default"), "key3", 2);
	newConfig.SetIntData(std::string("DEFAULT"), "key4", 3);
	newConfig.SetStrData(std::string("TestTest"), "Chicken", "Buttocks", 8);
	newConfig.SaveConfigFile();

	WConfigFile newConfig2("test.ogfconfig");
	cout << newConfig2.GetFloatData(string("Section"), "key1") << endl;
	cout << newConfig2.GetFloatData(string("Section"), "key2") << endl;
	cout << newConfig2.GetFloatData(string("Section"), "key3") << endl;
	cout << newConfig2.GetIntData(string("default"), "key1") << endl;
	cout << newConfig2.GetIntData(string("default"), "key2") << endl;
	cout << newConfig2.GetIntData(string("default"), "key3") << endl;
	cout << newConfig2.GetIntData(string("default"), "key4") << endl;
	cout << newConfig2.GetStrData(string("TestTest"), "Chicken") << endl;

	int exit;
	std::cin >> exit;
	return 0;
}

