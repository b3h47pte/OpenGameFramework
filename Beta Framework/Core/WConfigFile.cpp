#include "WConfigFile.h"
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

WConfigFile::WConfigFile(const std::string& inFile) : WFile(inFile) {
	// Read in each line as a string and then parse it so that we separate the config file into sections and get the key value pairs
	vector<string> allData;
	ReadAllTextData(allData);
	ParseConfigData(allData);
}


WConfigFile::~WConfigFile(void) {
	mConfigData.clear();
}

/*
 * Configuration File Format: 
 * -- [SECTION NAME] : all section titles will be forced to upper-case when stored in the map
 * -- KEY=VALUE (single value)
 * -- ; denotes a comment
 * TODO: Support array data.
 */
void WConfigFile::ParseConfigData(const std::vector<std::string>& inData) {
	string curSection = "DEFAULT"; 
	for (auto& line : inData) {
		// Strip white space before first character

		if (line[0] == ';')
			continue;

		// Read in section name
		if (line[0] == '[') {
			curSection = line.substr(1, line.size() - 2);
			for_each(curSection.begin(), curSection.end(), toupper);
		}
		// Read in data
		else if (line.find('=') != string::npos) {
			// Get Key -- KEY IS CASE SENSITIVE
			size_t eq = line.find('=');
			string key = line.substr(0, eq);

			// Get Data
			ConfigData_t data = ReadConfigDataFromString(line.substr(eq+1));
		}
		else {
			cout << "Unknown command in configuration file: " << line << endl;
		}
	}
}

/*
 * Given a value as read from the config file, identify what type it is and save it appropriately.
 */
ConfigData_t WConfigFile::ReadConfigDataFromString(const std::string& inData) {
	ConfigData_t t;
	// String
	if (std::any_of(inData.begin(), inData.end(), ::isalpha)) {
		t.strData = new char[inData.size()+1];
		t.strData[inData.size()] = '\0';
		memcpy(t.strData, inData.c_str(), sizeof(char) * inData.size());
	}
	// Float
	else if (inData.find('.') != string::npos) {
		t.floatData = atof(inData.c_str());
	}
	// Integer
	else { 
		t.intData = atoi(inData.c_str());
	}
	return t;
}
