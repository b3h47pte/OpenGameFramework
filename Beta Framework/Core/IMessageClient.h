#pragma once
#ifndef _IMESSAGECLIENT_H
#define _IMESSAGECLIENT_H

#include "CommonCore.h"
#include "MessageTypes.h"
#include <vector>

/*
 * Client that registers itself with the server so that it can receive messages for a specific message group.
 */
class IMessageClient
{
public:
	IMessageClient(void);
	virtual ~IMessageClient(void);

	virtual void RegisterGroup(EMessageGroups);
	virtual void UnregisterGroup(EMessageGroups);
	virtual bool IsRegistered(EMessageGroups);

	/*
	 * Message notification functions -- child classes should overwrite only the ones that they need.
	 */
	virtual void NotifyKeyInputMessage(const sKeyInputMessageData&) {}

	virtual void RegisterInitialGroups() = 0;

	virtual class MessageServer* const GetMessageServer() {return mMessageServerRef;}

protected:
	class MessageServer* const mMessageServerRef;
private:
	std::vector<EMessageGroups> mRegisteredGroups;
};

#endif // _IMESSAGECLIENT_H
