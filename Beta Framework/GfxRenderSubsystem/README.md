Gfx Render Subsystem Overview (Graphics Rendering, 3D or 2D)
==============================================================================

General Information
------------------
The GfxRender Subsystem renders 2D/3D objects using OpenGL. The creation of windows and handling input is taken care of elsewhere. In code, I will refer to this subsystem as the "Gfx Subsystem."

Frontend
------------------
Handles the interaction between the GfxRender Backend and the code that wants to use this subsystem.

Technical Details
------------------
**Initialization**

*Frontend*

The engine interfaces with the graphics subsytem by first requesting it via *GetGfxSubsystem* (GfxSubsystem.h). Once the subsytem object is constructed, the underlying backend and the user window are created and initialized.

*Windowing System*

Currently, I only provide a windowing system using SDL 2.0.3 (version subject to change) (SDLWindow.cpp). Once this management object is created, the window is created and the OpenGL context is created. Currently, it is hard-coded to request an 800x600 (GfxWindow.h). I request an OpenGL 4.1 context (hard-coded). This should be supported on most modern Windows computers and Mac OSX computers made after 2010/2011. The SDL context is also set to use 32-bit color(R8/B8/G8/A8) in addition to a 24-bit depth buffer.

*Backend*

After the OpenGL context is set with the windowing system, the backend gets initialied (GfxBackend::InitializeGraphicsAPI). The first step is to use GLEW to retrieve all necessary OpenGL function pointers. At this point the texture manager is initialized so that the user can begin to start using textures immediately.

**Mesh Rendering**

**Shader System**

**Lighting System**
