#pragma once
#ifndef _MESSAGETYPES_H
#define _MESSAGETYPES_H

#include "CommonCore.h"
#include <time.h>
#include <queue>
#include <vector>

/*
 * Message Categories (Groups).
 */
enum EMessageGroups {
	EMG_KEYINPUT
};

struct sMessageDataBase {
	clock_t	mClockTickTime;
};

/*
 * Keyboard Input Message Types.
 */
#define INPUT_KEY_DOWN		0
#define INPUT_KEY_UP		1
#define INPUT_KEY_REPEAT	2

/*
 * Keys.
 */
#include "MessageKeyboardInputTypes.h"
struct sKeyInputMessageData: public sMessageDataBase {
	char	mKeyState; // 0 - Down, 1 - Up, 2 - Repeat
	int32_t mKeyCode;  // Will contain the keycode (in the case of SDL, SDL_Keycode)
};
typedef std::queue<sKeyInputMessageData>	KeyInputMessageQueue;
typedef std::vector<class IMessageClient*>	KeyInputClientList;

#endif // _MESSAGETYPES_H