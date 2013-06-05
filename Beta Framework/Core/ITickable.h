#pragma once
#ifndef _ITICKABLE_H
#define _ITICKABLE_H

#include "CommonCore.h"

class  ITickable
{
public:
	ITickable(void);
	virtual ~ITickable(void);

	virtual void PreTick() {}
	virtual void Tick(float) = 0;
	virtual bool ShouldTick() = 0;
};
#endif // _ITICKABLE_H