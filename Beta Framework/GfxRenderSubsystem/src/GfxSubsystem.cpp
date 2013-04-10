#include "GfxSubsystem.h"

// Factory Function To create the GFx Subsystem
extern "C" GFXSUBAPI IGfxSubsystem* GetGfxSubsystem()
{
	// Initialize a GFx Subsystem entirely and make sure it's ready to use right after this function is called
	static GfxSubsystem* newSub = [] () {
		GfxSubsystem* sys = new GfxSubsystem();
		return sys;
	}();

	return newSub;
}

GfxSubsystem::GfxSubsystem(void)
{
}


GfxSubsystem::~GfxSubsystem(void)
{
}
