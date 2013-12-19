#include "WConfigFile.h"

#include <fstream>
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
		size_t firstChar = line.find_first_not_of(' ');
		if (firstChar == string::npos)
			continue;
		string parsedLine = line.substr(firstChar);

		if (parsedLine[0] == ';')
			continue;

		// Read in section name
		if (parsedLine[0] == '[') {
			curSection = line.substr(1, line.size() - 2);
			transform(curSection.begin(), curSection.end(), curSection.begin(), ::toupper);
		}
		// Read in data
		else if (parsedLine.find('=') != string::npos) {
			// Get Key -- KEY IS CASE SENSITIVE
			size_t eq = parsedLine.find('=');
			string key = parsedLine.substr(0, eq);

			// Get Data
			ConfigData_t data = ReadConfigDataFromString(parsedLine.substr(eq+1));

			mConfigData[curSection][key] = data;
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
	// String -- has an alpha character
	if (std::any_of(inData.begin(), inData.end(), ::isalpha)) {
		t.dataType = 2;
		t.strData = new char[inData.size()+1];
		t.strData[inData.size()] = '\0';
		memcpy(t.strData, inData.c_str(), sizeof(char) * inData.size());
	}
	// Float -- at this point it should~ be a number, floats would have a period
	else if (inData.find('.') != string::npos) {
		t.dataType = 1;
		t.floatData = atof(inData.c_str());
	}
	// Integer -- no period, number, must be an integer
	else { 
		t.dataType = 0;
		t.intData = atoi(inData.c_str());
	}
	return t;
}

int WConfigFile::GetIntData(std::string& section, const std::string& key) const {
	transform(section.begin(), section.end(), section.begin(), ::toupper);
	if (mConfigData.find(section) != mConfigData.end() && mConfigData.at(section).find(key) != mConfigData.at(section).end())
		return mConfigData.at(section).at(key).intData;
	return 0;
}

float WConfigFile::GetFloatData(std::string& section, const std::string& key) const {
	transform(section.begin(), section.end(), section.begin(), ::toupper);
	if (mConfigData.find(section) != mConfigData.end() && mConfigData.at(section).find(key) != mConfigData.at(section).end())
		return mConfigData.at(section).at(key).floatData;
	return 0.f;
}

const char* WConfigFile::GetStrData(std::string& section, const std::string& key) const {
	transform(section.begin(), section.end(), section.begin(), ::toupper);
	if (mConfigData.find(section) != mConfigData.end() && mConfigData.at(section).find(key) != mConfigData.at(section).end())
		return mConfigData.at(section).at(key).strData;
	return "";
}

void WConfigFile::SetIntData(std::string& section, const std::string& key, int data) {
	transform(section.begin(), section.end(), section.begin(), ::toupper);
	mConfigData[section][key].dataType = 0;
	mConfigData[section][key].intData = data;
}

void WConfigFile::SetFloatData(std::string& section, const std::string& key, float data) {
	transform(section.begin(), section.end(), section.begin(), ::toupper);
	mConfigData[section][key].dataType = 1;
	mConfigData[section][key].floatData = data;
}

/*
 * 'size' contains the number of chars in the char array (data).
 */ 
void WConfigFile::SetStrData(std::string& section, const std::string& key, char* data, int size) {
	transform(section.begin(), section.end(), section.begin(), ::toupper);
	// If this string data doesn't already exist, we will want to allocate memory for it
	// Otherwise if it does exist, delete and create new memory
	if (mConfigData.find(section) != mConfigData.end() && mConfigData.at(section).find(key) != mConfigData.at(section).end()) {
		if (mConfigData[section][key].strData)
			delete mConfigData[section][key].strData;
	}
	mConfigData[section][key].dataType = 2;
	mConfigData[section][key].strData = new char[sizeof(char) * (size+1)];
	mConfigData[section][key].strData[size] = '\0';
	memcpy(mConfigData[section][key].strData, data, size);
}

/*
 * Rewrite the file using the data in mConfigdata.
 */
void WConfigFile::SaveConfigFile() {
	ofstream file;
	file.open(mFileName, std::ios::out | std::ios::trunc);

	// Iterate through each section
	for (auto& section : mConfigData) {
		file << "[" << section.first << "]" << endl;
		// Iterate through each key/value pair in the section
		for (auto& kvp : section.second) {
			file << kvp.first << "=";
			switch (kvp.second.dataType) {
			case 0:
				file << kvp.second.intData << endl;
				break;
			case 1:
				file << std::showpoint << kvp.second.floatData << endl;
				break;
			case 2:
				file << kvp.second.strData << endl;
				break;
			default:
				file << "0" << endl;
				cout << "WConfigFile: Invalid data type: " << kvp.second.dataType << endl;
				break;
			}
		}
		file << endl;
	}
	file.close();
}
