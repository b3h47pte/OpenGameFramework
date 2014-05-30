#ifndef MESSAGE_CLIENT_MOCK_H
#define MESSAGE_CLIENT_MOCK_H
#include "gtest-common.h"
#include "IMessageClient.h"

using ::testing::_;
using ::testing::Invoke;

class BareMessageClient: public IMessageClient {
public:
  BareMessageClient(): overrideMsgServer(false) {
  }

  void SetMessageServer(class MessageServer* serv) {
    overrideMsgServer = true;
    newMsgServer = serv;  
  }
  
  void ResetMessageServer() {
    overrideMsgServer = false;
  }

  virtual class MessageServer* const GetMessageServer() {
    return (overrideMsgServer ? newMsgServer : mMessageServerRef);
  }
private:
  virtual void RegisterInitialGroups() {}
  
  // Stuff we need just for testing the server just in case.
  bool overrideMsgServer;
  class MessageServer* newMsgServer;
};

class MockMessageClient: public IMessageClient {
public:

  MockMessageClient() {
    ON_CALL(*this, RegisterGroup(_)).WillByDefault(
      Invoke(&real_, &IMessageClient::RegisterGroup)
    );

    ON_CALL(*this, UnregisterGroup(_)).WillByDefault(
      Invoke(&real_, &IMessageClient::UnregisterGroup)
    );

    ON_CALL(*this, IsRegistered(_)).WillByDefault(
      Invoke(&real_, &IMessageClient::IsRegistered)
    );
  }

  MOCK_METHOD1(RegisterGroup, void(EMessageGroups group));
  MOCK_METHOD1(UnregisterGroup, void(EMessageGroups group));
  MOCK_METHOD1(IsRegistered, bool(EMessageGroups group));

  MOCK_METHOD1(NotifyKeyInputMessage, void(const sKeyInputMessageData& data));
  MOCK_METHOD0(RegisterInitialGroups, void());

private:
  BareMessageClient real_;  
};
#endif
