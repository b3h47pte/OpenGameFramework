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

// Use GLM for Math
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/string_cast.hpp>
#endif