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

	void RegisterGroup(EMessageGroups);
	void UnregisterGroup(EMessageGroups);
	bool IsRegistered(EMessageGroups);

protected:
	virtual void RegisterInitialGroups() {};

private:
	std::vector<EMessageGroups> mRegisteredGroups;
};

#endif // _IMESSAGECLIENT_H