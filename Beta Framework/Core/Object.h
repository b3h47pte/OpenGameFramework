#pragma once
#ifndef _OBJECT_H
#define _OBJECT_H

#include "CommonCore.h"

/*
 * All things used by the framework is an "object".
 */
class COREAPI Object
{
public:
	Object(void);
	virtual ~Object(void);
};


#endif // _OBJECT_H