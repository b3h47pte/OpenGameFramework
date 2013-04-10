#pragma once
#ifndef _COMMON_CORE_H
#define _COMMON_CORE_H

// CORE_EXPORT defined in project properties for the Core API
#ifdef CORE_EXPORT // inside DLL
	#define COREAPI __declspec(dllexport)
#else // outside DLL
	#define COREAPI __declspec(dllimport)
#endif  // CORE_EXPORT

#include <iostream>
#include <string>

#endif // _COMMON_CORE_H