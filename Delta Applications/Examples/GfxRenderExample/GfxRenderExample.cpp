// GfxRenderExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "GfxSubsystem.h"

int _tmain(int argc, _TCHAR* argv[])
{
	IGfxSubsystem* gfx = GetGfxSubsystem();

	while(gfx->ShouldTick()) {
		gfx->Tick(0.1f);
		Sleep(1);
	}

	return 0;
}

