// SDL-InputTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "GfxSubsystem.h"
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
	}

protected:
	virtual void RegisterInitialGroups() { 
		GetGlobalMessageServer()->RegisterClient(this, EMG_KEYINPUT); 
	}

private:
};


int _tmain(int argc, _TCHAR* argv[])
{
	IGfxSubsystem* gfx = GetGfxSubsystem(GFX_CREATE_DEFAULT_CAMERA);
	MessageServer* srv = GetGlobalMessageServer();
	TestMessageClient* client = new TestMessageClient();
	if (!gfx)
		return 0;
	while(gfx->ShouldTick()) {
		gfx->Tick(0.1f);
		srv->Tick(0.1f);
		Sleep(1);
	}
	return 0;
}

