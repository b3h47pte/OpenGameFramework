#include "MessageServer.h"
#include "IMessageClient.h"

MessageServer* GetGlobalMessageServer() {
  static MessageServer* msg = [] () {
    MessageServer* srv = new MessageServer();
    if (!srv) return (MessageServer*)NULL;
    return srv;
  }();
  return msg;
}

MessageServer::MessageServer(void): mProcessKeyInputMessages(true) {
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

  // If client doesn't know it's registered, make sure it does.
  if (!client->IsRegistered(grp))
    client->RegisterGroup(grp);
}

void MessageServer::UnregisterClient(class IMessageClient* client, EMessageGroups grp) {
  switch (grp) {
  case EMG_KEYINPUT:
    UnRegisterKeyInputClient(client);
    break;
  }

  // Make sure client unregisters itself
  if (client->IsRegistered(grp))
    client->UnregisterGroup(grp);
}
  
// TODO: Generalize based on group
bool MessageServer::CheckIsRegistered(class IMessageClient* client, EMessageGroups group) {
  std::vector<class IMessageClient*>::const_iterator it = find(mKeyInputClients.begin(), mKeyInputClients.end(), client);
  return (it != mKeyInputClients.end());
}

void MessageServer::RegisterKeyInputClient(class IMessageClient* client) {
  mKeyInputClients.push_back(client);
}

// TODO: Generalize based on group
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

/*
 * Tick -- process all messages in the queue every tick. 
 * TODO: When doing multi-threading, make sure to lock the queues when reading off of it.
 */ 
void MessageServer::Tick(float) {
  ProcessKeyInputMessages();
}

void MessageServer::ProcessKeyInputMessages() {
  if (!mProcessKeyInputMessages)
    return;

  while (!mKeyInputQueue.empty()) {
    sKeyInputMessageData data = mKeyInputQueue.front();
    for (auto client : mKeyInputClients) {
      client->NotifyKeyInputMessage(data);
    }
    mKeyInputQueue.pop();
  }
}
