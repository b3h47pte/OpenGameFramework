#include "IMessageClient.h"

#include <algorithm>

IMessageClient::IMessageClient(void) {
}


IMessageClient::~IMessageClient(void) {
	for (auto grp : mRegisteredGroups) {
		UnregisterGroup(grp);
	}
}

void IMessageClient::RegisterGroup(EMessageGroups in) {
	mRegisteredGroups.push_back(in);
}

void IMessageClient::UnregisterGroup(EMessageGroups in) {
	std::vector<EMessageGroups>::const_iterator it = find(mRegisteredGroups.begin(), mRegisteredGroups.end(), in);
	mRegisteredGroups.erase(it);
}

bool IMessageClient::IsRegistered(EMessageGroups in) {
	return (find(mRegisteredGroups.begin(), mRegisteredGroups.end(), in) != mRegisteredGroups.end());
}
