#pragma once
#ifndef _MESSAGESERVER_H
#define _MESSAGESERVER_H

#include "CommonCore.h"
#include "MessageTypes.h"
#include "ITickable.h"
#include <time.h>

/*
 * Central messaging system (server).
 * Each client registers itself with the server and sets itself to a group (or multiple groups) to receive messages from. 
 * Whenever a client has a message to send, it pushes it into a (thread-safe?) queue on the server which will then 
 *  push it out towards the appropriate groups later.
 */
class MessageServer: public ITickable
{
public:
  MessageServer(void);
  ~MessageServer(void);

  // Generic Register/Unregister
  virtual void RegisterClient(class IMessageClient*, EMessageGroups);
  virtual void UnregisterClient(class IMessageClient*, EMessageGroups);
  virtual bool CheckIsRegistered(class IMessageClient*, EMessageGroups);

  // Keyboard Input
  virtual void PushKeyInputMessage(const sKeyInputMessageData&);
  virtual sKeyInputMessageData PopKeyInputMessage();

  /*
   * Tick
   */
  virtual void Tick(float);
  virtual bool ShouldTick() { return true; }

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
  KeyInputMessageQueue  mKeyInputQueue;
  KeyInputClientList    mKeyInputClients;
  bool          mProcessKeyInputMessages;
  void ProcessKeyInputMessages();
};

MessageServer* GetGlobalMessageServer();

#endif // _MESSAGESERVER_H
