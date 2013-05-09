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

char* WFile::ReadAllBinaryDataNull() {
	ifstream file(mFileName, std::ios::in | std::ios::binary);
	int fsize;
	file.seekg(0, file.end);
	fsize = (int)file.tellg();
	file.seekg(0, file.beg);

	char* allData = new char[fsize+1];
	if (!allData) return NULL;
	file.read(allData, fsize);
	allData[fsize] = '\0';
	file.close();


	return allData;
}