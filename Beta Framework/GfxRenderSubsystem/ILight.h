#pragma once
#ifndef _ILIGHT_H
#define _ILIGHT_H

#include "CommonGfx.h"

/*
 * Light Interface. All lights will need to have "energy" and be able to determine what, in the world, it is actual has an effect on.
 */
class ILight
{
public:
	ILight(void);
	virtual ~ILight(void);
	
protected:
	glm::vec3 mLightColor;
};

#endif // _ILIGHT_H