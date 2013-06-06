#pragma once
#pragma once
#ifndef _WCONFIGFILE_H
#define _WCONFIGFILE_H

#include "CommonCore.h"
#include "WFile.h"
#include <map>

union ConfigData_t {
	int intData;		// Just pure numbers
	float floatData;	// Has a '.' inside
	char* strData;		// Indicated by the presence of a non-number
};

class WConfigFile: public WFile
{
public:
	WConfigFile(const std::string&);
	virtual ~WConfigFile(void);

private:
	/*
	 * Reads in line data from the configuration file and saves it in the map.
	 */
	void ParseConfigData(const std::vector<std::string>&);
	ConfigData_t ReadConfigDataFromString(const std::string&);

	std::map<std::string, std::map<std::string, ConfigData_t> > mConfigData;
};

#endif // _WCONFIGFILE_H