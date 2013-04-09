#include "Frontend/GfxSubsystem.h"

// Factory Function To create the GFx Subsystem
extern "C" GFXSUBAPI IGfxSubsystem* GetGfxSubsystem()
{
	static GfxSubsystem* newSub = new GfxSubsystem();
	return newSub;
}

GfxSubsystem::GfxSubsystem(void)
{
}


GfxSubsystem::~GfxSubsystem(void)
{
}
