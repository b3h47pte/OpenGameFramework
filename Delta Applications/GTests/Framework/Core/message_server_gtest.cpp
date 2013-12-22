#include "gtest-common.h"
#include "MessageServer.h"
#include "mock_message_client.h"

using ::testing::Return;

class MessageServerTest: public testing::Test {
protected:
	virtual void SetUp() {
		server = new MessageServer();
	}

	virtual void TearDown() {
		delete server;
	}

	MessageServer* server;
	MockMessageClient client;
};

// Make sure only one message server will ever exist
TEST_F(MessageServerTest, IsASingleton) {
	MessageServer* tmp1 = GetGlobalMessageServer();
	MessageServer* tmp2 = GetGlobalMessageServer();
	EXPECT_EQ(tmp1, tmp2);
}

// Register and Unregister Client Test
TEST_F(MessageServerTest, HandlesClientRegistration) {
	EXPECT_CALL(client, IsRegistered(_)).Times(4);

	EXPECT_CALL(client, RegisterGroup(_)).Times(1);
	server->RegisterClient(&client, EMG_KEYINPUT);
	EXPECT_TRUE(server->CheckIsRegistered(&client, EMG_KEYINPUT));
	EXPECT_TRUE(client.IsRegistered(EMG_KEYINPUT));

	EXPECT_CALL(client, UnregisterGroup(_)).Times(1);
	server->UnregisterClient(&client, EMG_KEYINPUT);
	EXPECT_FALSE(server->CheckIsRegistered(&client, EMG_KEYINPUT));
	EXPECT_FALSE(client.IsRegistered(EMG_KEYINPUT));
}

/**
 * KEYS MESSAGES.
 */
TEST_F(MessageServerTest, PassesKeyMessages) {
	sKeyInputMessageData data;
	data.mKeyState = INPUT_KEY_DOWN;
	data.mKeyCode = EKEY_SPACE;

	server->PushKeyInputMessage(data);
	sKeyInputMessageData ret = server->PopKeyInputMessage();
	EXPECT_EQ(data.mKeyState, ret.mKeyState);
	EXPECT_EQ(data.mKeyCode, ret.mKeyCode);
}

TEST_F(MessageServerTest, ReceivesKeyMessages) {
	sKeyInputMessageData data;
	data.mKeyState = INPUT_KEY_DOWN;
	data.mKeyCode = EKEY_SPACE;
	server->PushKeyInputMessage(data);

	EXPECT_CALL(client, IsRegistered(_));
	EXPECT_CALL(client, RegisterGroup(_));
	server->RegisterClient(&client, EMG_KEYINPUT);

	// Client should receive a message telling that it has a new message!
	EXPECT_CALL(client, NotifyKeyInputMessage(data)).Times(1);
	server->Tick(0.01f);
}
