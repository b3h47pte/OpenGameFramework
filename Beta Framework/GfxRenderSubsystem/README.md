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
Makes use of OpenGL.