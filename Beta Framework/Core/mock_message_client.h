#include "gtest-common.h"
#include "IMessageClient.h"

class MockMessageClient: public IMessageClient {
public:
	MOCK_METHOD1(RegisterGroup, void(EMessageGroups group));
	MOCK_METHOD1(UnregisterGroup, void(EMessageGroups group));
	MOCK_METHOD1(IsRegistered, bool(EMessageGroups group));

	MOCK_METHOD1(NotifyKeyInputMessage, void(const sKeyInputMessageData& data));
	MOCK_METHOD0(RegisterInitialGroups, void());
};

class BareMessageClient: public IMessageClient {
	virtual void RegisterInitialGroups() {}
};
