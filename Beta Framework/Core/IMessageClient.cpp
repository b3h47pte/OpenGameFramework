#include "IMessageClient.h"
#include "MessageServer.h"

#include <algorithm>

IMessageClient::IMessageClient(void): mMessageServerRef(GetGlobalMessageServer()) {
}


IMessageClient::~IMessageClient(void) {
	for (auto grp : mRegisteredGroups) {
		UnregisterGroup(grp);
	}
}

void IMessageClient::RegisterGroup(EMessageGroups in) {
	mRegisteredGroups.push_back(in);
	// Make sure server recognizes us as being in the group
	if (!GetMessageServer()->CheckIsRegistered(this, in))
		GetMessageServer()->RegisterClient(this, in);
}

void IMessageClient::UnregisterGroup(EMessageGroups in) {
	std::vector<EMessageGroups>::const_iterator it = find(mRegisteredGroups.begin(), mRegisteredGroups.end(), in);
	mRegisteredGroups.erase(it);
	if (GetMessageServer()->CheckIsRegistered(this, in))
		GetMessageServer()->UnregisterClient(this, in);
}

bool IMessageClient::IsRegistered(EMessageGroups in) {
	return (find(mRegisteredGroups.begin(), mRegisteredGroups.end(), in) != mRegisteredGroups.end());
}
