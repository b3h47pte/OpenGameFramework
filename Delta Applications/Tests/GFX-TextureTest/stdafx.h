// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#ifdef _WIN32
	#include<tchar.h>
#else
	#define _TCHAR char*
	#define Sleep usleep
	#include <unistd.h>
#endif

// TODO: reference additional headers your program requires here
