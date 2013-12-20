#pragma once
#ifndef _NWLCOMMON_H
#define _NWLCOMMON_H

#include <iostream>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifdef _WIN32 
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <IPHlpApi.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

#endif // _NWLCOMMON_H
