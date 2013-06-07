#include "MessageServer.h"

MessageServer* GetGlobalMessageServer() {
	static MessageServer* msg = [] () {
		MessageServer* srv = new MessageServer();
		if (!srv) return (MessageServer*)NULL;
		return srv;
	}();
	return msg;
}

MessageServer::MessageServer(void) {
}


MessageServer::~MessageServer(void) {
}

/*
 * Registration Related Functions.
 * Generic Register/Unregister function will call the appropriate group-specific
 * register/unregister functions to perform the work.
 */
void MessageServer::RegisterClient(class IMessageClient* client, EMessageGroups grp) {
	switch (grp) {
	case EMG_KEYINPUT:
		RegisterKeyInputClient(client);
		break;
	}
}

void MessageServer::UnregisterClient(class IMessageClient* client, EMessageGroups grp) {
	switch (grp) {
	case EMG_KEYINPUT:
		UnRegisterKeyInputClient(client);
		break;
	}
}

void MessageServer::RegisterKeyInputClient(class IMessageClient* client) {
	mKeyInputClients.push_back(client);
}

void MessageServer::UnRegisterKeyInputClient(class IMessageClient* client) {
	std::vector<class IMessageClient*>::const_iterator it = find(mKeyInputClients.begin(), mKeyInputClients.end(), client);
	mKeyInputClients.erase(it);
}

/*
 * Input Messages.
 */
void MessageServer::PushKeyInputMessage(const sKeyInputMessageData& inData) {
	mKeyInputQueue.push(inData);
}

sKeyInputMessageData MessageServer::PopKeyInputMessage() {
	sKeyInputMessageData top = mKeyInputQueue.front();
	mKeyInputQueue.pop();
	return top;
}