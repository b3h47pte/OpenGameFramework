/*
 * Include THIS file when you want to take advantage of the core classes.
 *
 */
#pragma once
#ifndef _CORE_EXTERNAL_H
#define _CORE_EXTERNAL_H

#include "CommonCore.h"
#include "ErrorCatch.h"
#include "ITickable.h"
#include "TIntrusiveLinkedList.h"

// Use GLM for Math
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Object.h"
#include "WorldObject.h"

#include <assert.h>
#endif
