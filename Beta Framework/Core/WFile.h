#pragma once
#ifndef _WFILE_H
#define _WFILE_H

#include "CommonCore.h"

class COREAPI WFile
{
public:
	WFile(const std::string&);
	virtual ~WFile(void);

	/*
	 * Each line is represented by a char array.
	 * The input reference to an int will output how many lines there are in the file.
	 */
	char** ReadAllTextData(int&);

private:
#pragma warning( push )
#pragma warning (disable: 4251)
	std::string mFileName;
#pragma warning (pop)
};

#endif // _WFILE_H