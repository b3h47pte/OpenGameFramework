#ifndef MESSAGE_SERVER_MOCK_H
#define MESSAGE_SERVER_MOCK_H
#include "gtest-common.h"
#include "MessageServer.h"

using ::testing::_;
using ::testing::Invoke;

class MockMessageServer: public MessageServer {
public:
  MockMessageServer() {
    ON_CALL(*this, RegisterClient(_,_)).WillByDefault(
      Invoke(&real_, &MessageServer::RegisterClient)
    );

    ON_CALL(*this, UnregisterClient(_,_)).WillByDefault(
      Invoke(&real_, &MessageServer::UnregisterClient)
    );

    ON_CALL(*this, CheckIsRegistered(_,_)).WillByDefault(
      Invoke(&real_, &MessageServer::CheckIsRegistered)
    );

  }

  MOCK_METHOD2(RegisterClient, void(class IMessageClient* c, EMessageGroups group));
  MOCK_METHOD2(UnregisterClient, void(class IMessageClient* c, EMessageGroups group));
  MOCK_METHOD2(CheckIsRegistered, bool(class IMessageClient* c, EMessageGroups group));
private:
  MessageServer real_;
};
#endif 
