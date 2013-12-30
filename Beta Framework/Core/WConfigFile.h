#pragma once
#pragma once
#ifndef _WCONFIGFILE_H
#define _WCONFIGFILE_H

#include "CommonCore.h"
#include "WFile.h"
#include <map>

struct ConfigData_t {
	/*
	 * dataType tells us what kind of data is stored here. 
	 *	-- Used when storing data so we know how to interpret the data in the union.
	 * 0 - INT
	 * 1 - FLOAT
	 * 2 - CHAR*
	 */
	char dataType; 
	union {
		int intData;		// Just pure numbers
		float floatData;	// Has a '.' inside
		char* strData;		// Indicated by the presence of a non-number
	};
};

class WConfigFile: public WFile
{
public:
	WConfigFile();
	WConfigFile(const std::string&);
	virtual ~WConfigFile(void);

	/*
	 * Get/Set Methods for Config Data.
	 * First two parameters: SECTION, KEY
	 */
	int GetIntData(std::string&, const std::string&) const;
	float GetFloatData(std::string&, const std::string&) const;
	const char* GetStrData(std::string&, const std::string&) const;

	void SetIntData(std::string&, const std::string&, int);
	void SetFloatData(std::string&, const std::string&, float);
	// Does not assume the input string is null-terminated
	void SetStrData(std::string&, const std::string&, const char*, int); 

	/*
	 * Save Config File.
	 */
	void SaveConfigFile();
private:
	/*
	 * Reads in line data from the configuration file and saves it in the map.
	 */
	void ParseConfigData(const std::vector<std::string>&);
	ConfigData_t ReadConfigDataFromString(const std::string&);

	std::map<std::string, std::map<std::string, ConfigData_t> > mConfigData;
};

#endif // _WCONFIGFILE_H
