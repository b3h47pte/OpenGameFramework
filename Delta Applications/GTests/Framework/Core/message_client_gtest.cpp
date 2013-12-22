#include "gtest-common.h"
#include "IMessageClient.h"
#include "mock_message_server.h"
#include "mock_message_client.h"

using ::testing::Return;

class MessageClientTest: public testing::Test {
	void SetUp() {
		client.SetMessageServer(&server);
	}

	void TearDown() {
		client.ResetMessageServer();
	}

protected:
	BareMessageClient client;
	MockMessageServer server;
};

// If client gets registered then the server should get registered too
// Unregister should do the same.
TEST_F(MessageClientTest, EnforcesServerSideRegistration) {
	EXPECT_CALL(server, CheckIsRegistered(_,_)).Times(2);

	EXPECT_CALL(server, RegisterClient(_,_)).Times(1);
	client.RegisterGroup(EMG_KEYINPUT);
	EXPECT_TRUE(client.IsRegistered(EMG_KEYINPUT));

	EXPECT_CALL(server, UnregisterClient(_,_)).Times(1);
	client.UnregisterGroup(EMG_KEYINPUT);
	EXPECT_FALSE(client.IsRegistered(EMG_KEYINPUT));
}

