Open Game Framework
===================================
- - -

Vision and Objective
--------------------------
I believe that indie games are the future in bringing in fresh, innovative concepts into the gaming industry. Games like Chivalry: Medieval Warfare, Primal Carnage, The Ball, Sanctum, and more have been successful because they were given easy access to free tools like the UDK that enabled them to focus on making great games and significantly reduced the barrier to entry. Eventually, however, most teams discover that not having access to the source code of the engine prevented them from doing a lot of cool things but getting access to that would cost them a significant lump of money, pre and post-release.

This is where Open Game Framework (OpenGF, Open Good Fun?) comes into the picture. With OpenGF, I plan to create all the various subsystems that are necessary for a game: rendering, physics, audio, etc. In addition, I plan to create a tool-set that would allow for easy content creation and editing. Finally, I also hope to introduce a backend system like Steamworks that would enable developers to track stats and more. Eventually I would also like to integrate some AAA technologies as well such as Scaleform, and Steamworks (although the integration of these AAA frameworks would most likely not be open source). By splitting OpenGF into these three areas, this would allow a developer to pick and choose what he/she wants to use. If the developer wanted to use OpenGF for rendering but take care of audio, he/she would easily be able to do that due to the modular setup of OpenGF. However, most indie developers want to create awesome games, not deal with tedious game engine internals. So, I will also create another layer that will neatly tie together all the subsystems and make it so that developers will only have to write code that deals with gameplay.

- - -

Alpha Tools
--------------------------
Provide a toolset that will create content packages (maps, assets) to be used with the framework. However, any application that decides to make use of the alpha tools will also need to utilize the subsystem that deals with loading/saving these assets. 

TBD.

- - -

Beta Framework
--------------------------

The beta layer is what goes on behind the scenes of the game engine. It will take care of the internals of rendering, audio, networking, etc. Due to the design of the framework, any subsystem (besides Core) can be used individually. 	

#### Core

Any game/program that uses any of the subsystems MUST also use the Core subsystem as it contains a number of important classes that are used throughout the framework. Currently provides:

* Error Detection/Logging (ErrorCatch.h/cpp)
* Tickable Interface (ITickable.h/cpp)
* Various useful data structures

Planned features include:

* Memory management

#### GfxRender Subsystem

Subsystem that will take care of rendering 3D or 2D elements into a window. In addition, it will create a window and capture input events that will be passed to whoever using function delegates. Currently makes use of OpenGL for rendering and SDL for creating the window and capturing input.

- - -

Delta Applications
--------------------------
#### Examples

Provides examples of using the various subsystems.

- - -

Gamma Backend
--------------------------

A backend that will handle log-ins and authentication to not only determine if a player has legitimately acquired the game but also keep track of stats (public and developer only) in addition to achievements. In addition, will provide "player attributes" that allows developers to store information about users. The Gamma Backend will strive to make editing stats/attributes about users simple, efficient, and flexible.

TBD. 
- - -

Omega Bootstrapper
--------------------------

Want to just focus on making a game? The Omega Bootstrapper will take care of initializing all the subsystems and all the developer has to do is to write gameplay code. I plan to make the gameplay code programmable using C/C++ rather than using a scripting language like LuA to make sure performance is not bottle-necked by the gameplay code.

TBD.
- - -