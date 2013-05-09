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
	 * Reas a file as binary data and puts a NULL at the end.
	 */
	char* ReadAllBinaryDataNull();

private:
#pragma warning( push )
#pragma warning (disable: 4251)
	std::string mFileName;
#pragma warning (pop)
};

#endif // _WFILE_H