#pragma once
#ifndef _MESSAGESERVER_H
#define _MESSAGESERVER_H

#include "CommonCore.h"
#include "MessageTypes.h"

/*
 * Central messaging system (server).
 * Each client registers itself with the server and sets itself to a group (or multiple groups) to receive messages from. 
 * Whenever a client has a message to send, it pushes it into a (thread-safe?) queue on the server which will then 
 *	push it out towards the appropriate groups later.
 */
class MessageServer
{
public:
	MessageServer(void);
	~MessageServer(void);

	// Generic Register/Unregister
	void RegisterClient(class IMessageClient*, EMessageGroups);
	void UnregisterClient(class IMessageClient*, EMessageGroups);

	// Keyboard Input
	void PushKeyInputMessage(const sKeyInputMessageData&);
	sKeyInputMessageData PopKeyInputMessage();

private:
	/*
	 * Specific Registration Functions.
	 */
	void RegisterKeyInputClient(class IMessageClient*);
	void UnRegisterKeyInputClient(class IMessageClient*);


	/*
	 * Group Queues;
	 * Maintain a separate queue for each category of data that comes in.
	 */
	KeyInputMessageQueue	mKeyInputQueue;
	KeyInputClientList		mKeyInputClients;
};

MessageServer* GetGlobalMessageServer();

#endif // _MESSAGESERVER_H