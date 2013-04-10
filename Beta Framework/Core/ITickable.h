#pragma once
#ifndef _ITICKABLE_H
#define _ITICKABLE_H

#include "CommonCore.h"

class COREAPI ITickable
{
public:
	ITickable(void);
	virtual ~ITickable(void);

	virtual void Tick(float) = 0;
	virtual bool ShouldTick() = 0;
};
#endif // _ITICKABLE_H