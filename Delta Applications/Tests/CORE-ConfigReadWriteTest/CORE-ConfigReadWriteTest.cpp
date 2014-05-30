// CORE-ConfigReadWriteTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WConfigFile.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  WConfigFile newConfig("test.ogfconfig");
  std::string sec[] = { "Section", "defAult", "DEfaUlt", "default", "DEFAULT", "TESTTEST"};
  newConfig.SetFloatData(sec[0], "key1", 0.5f);
  newConfig.SetFloatData(sec[0], "key2", 1.0f);
  newConfig.SetFloatData(sec[0], "key3", 2.0f);
  newConfig.SetIntData(sec[1], "key1", 0);
  newConfig.SetIntData(sec[2], "key2", 1);
  newConfig.SetIntData(sec[3], "key3", 2);
  newConfig.SetIntData(sec[4], "key4", 3);
  char* mm = new char[8];
  for (int i = 0; i < 8; ++i) 
    mm[i] = 'A';
  newConfig.SetStrData(sec[5], "Chicken", mm, 8);
  newConfig.SaveConfigFile();

  WConfigFile newConfig2("test.ogfconfig");
  cout << newConfig2.GetFloatData(sec[0], "key1") << endl;
  cout << newConfig2.GetFloatData(sec[0], "key2") << endl;
  cout << newConfig2.GetFloatData(sec[0], "key3") << endl;
  cout << newConfig2.GetIntData(sec[3],"key1") << endl;
  cout << newConfig2.GetIntData(sec[3], "key2") << endl;
  cout << newConfig2.GetIntData(sec[3], "key3") << endl;
  cout << newConfig2.GetIntData(sec[3], "key4") << endl;
  cout << newConfig2.GetStrData(sec[5], "Chicken") << endl;

  int exit;
  std::cin >> exit;
  return 0;
}

