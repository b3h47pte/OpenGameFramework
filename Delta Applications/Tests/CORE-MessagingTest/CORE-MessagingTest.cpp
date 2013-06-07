// CORE-MessagingTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MessageServer.h"
#include "IMessageClient.h"

class TestMessageClient: public IMessageClient {
public:
	TestMessageClient() { RegisterInitialGroups(); }
	~TestMessageClient() {}

	virtual void NotifyKeyInputMessage(const sKeyInputMessageData& in) {
		std::cout << "Notify Key Input Message:" << std::endl;
		std::cout << "Clock Time: " << in.mClockTickTime << std::endl;
		std::cout << "Key Code: " << in.mKeyCode << std::endl;
		std::cout << "Key State: " << (int)in.mKeyState << std::endl;
		std::cout << "Repeat Count: " << in.mRepeatCount << std::endl;
	}

protected:
	virtual void RegisterInitialGroups() { 
		GetGlobalMessageServer()->RegisterClient(this, EMG_KEYINPUT); 
	}

private:
};

int _tmain(int argc, _TCHAR* argv[])
{
	MessageServer* srv = GetGlobalMessageServer();
	TestMessageClient* client = new TestMessageClient();

	sKeyInputMessageData data;
	data.mClockTickTime = clock();
	data.mKeyCode = 0;
	data.mKeyState = 1;
	data.mRepeatCount = 2;
	srv->PushKeyInputMessage(data);

	srv->Tick(0.1f);

	delete client;

	int exit;
	std::cin >> exit;

	return 0;
}

