#pragma once
#ifndef _MESSAGETYPES_H
#define _MESSAGETYPES_H

#include "CommonCore.h"
#include <queue>
#include <vector>

/*
 * Message Categories (Groups).
 */
enum EMessageGroups {
	EMG_KEYINPUT
};

struct sMessageDataBase {
	float	mClockTickTime;
};

/*
 * Keyboard Input Message Types.
 */
#define INPUT_KEY_DOWN		0
#define INPUT_KEY_UP		1
#define INPUT_KEY_REPEAT	2
struct sKeyInputMessageData: public sMessageDataBase {
	char	mKeyState; // 0 - Down, 1 - Up, 2 - Repeat
	int32_t mKeyCode;  // Will contain the keycode (in the case of SDL, SDL_Keycode)
	unsigned int mRepeatCount;	// Number of times repeat has been going on
};
typedef std::queue<sKeyInputMessageData>	KeyInputMessageQueue;
typedef std::vector<class IMessageClient*>	KeyInputClientList;

#endif // _MESSAGETYPES_H