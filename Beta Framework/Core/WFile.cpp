#include "WFile.h"
#include <fstream>
#include <vector>

using namespace std;

WFile::WFile(const std::string& in): mFileName(in)
{
}


WFile::~WFile(void)
{
}

char** WFile::ReadAllTextData(int& outLines) {
	outLines = 0;
	ifstream file;
	vector<string> allLines;
	file.open(mFileName.c_str(), std::ifstream::in);
	if (file.is_open()) {
		std::string line;
		while (file.good()) {
			getline(file, line); 
			allLines.push_back(line);
		}
	}
	char** allData;
	outLines = allLines.size();
	allData = new char*[outLines];
	for (int i = 0; i < outLines; i++) {
		allData[i] = new char[allLines[i].size()];
		memcpy(allData[i], allLines[i].c_str(), allLines[i].size() * sizeof(char));
	}
	return allData;
}