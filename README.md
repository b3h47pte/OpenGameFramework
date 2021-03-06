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

#### OGF Config Editor

Simple tool to modify the config files (*.ogfconfig) for a project.

- - -

Beta Framework
--------------------------

The beta layer is what goes on behind the scenes of the game engine. It will take care of the internals of rendering, audio, networking, etc. Due to the design of the framework, any subsystem (besides Core) can be used individually. If you want to use a subsystem, one must link the generated *.lib (Windows) file into the project. There are no DLL files as I decided that the simplicity in just having one executable when using the core framework components would be simpler to manage.

#### Core

Any game/program that uses any of the subsystems MUST also use the Core subsystem as it contains a number of important classes that are used throughout the framework. Currently provides:

* Error Detection/Logging
* Tickable Interface
* Various useful data structures
* Binary/Text File Read
* Configuration File Read/Write
* Basic Object/World Object
* Message Passing

Planned features include:

* Memory management
* Mulit-threading Management

#### GfxRender Subsystem

Subsystem that will take care of rendering 3D or 2D elements into a window. In addition, it will create a window and capture input events that will be passed to whoever using function delegates. Currently makes use of OpenGL for rendering and SDL for creating the window and capturing input. Currently provides:

* Window Creation (SDL)
* Keyboard Input Detection (SDL)
* Perspective View and Camera View Transformations
* Rendering to Multiple Viewports
* Basic Shaders (Vertex and Fragment)
* Functionality to read in an OBJ file

#### Audio Subsystem

Provides a wrapper around FMOD to more easily play sounds and modify variou settings. Will later provide usage of other audio systems if possible (XAudio, etc). 

#### Network Library

Library to provide easy-to-use TCP and UDP networking functionality. 

- - -

Delta Applications
--------------------------
#### Tests

Unit tests for features in the subsystems. Also provide examples (basic and naive ones) of how one can approach utilizing the subsystems.

- - -

Gamma Backend
--------------------------

A backend that will handle log-ins and authentication to not only determine if a player has legitimately acquired the game but also keep track of stats (public and developer only) in addition to achievements. In addition, will provide "player attributes" that allows developers to store information about users. The Gamma Backend will strive to make editing stats/attributes about users simple, efficient, and flexible.

TBD. 
- - -

Omega Engine
--------------------------

Want to just focus on making a game? The Omega Engine will take care of initializing all the subsystems and all the developer has to do is to write gameplay code. I plan to make the gameplay code programmable using C/C++ rather than using a scripting language like LuA to make sure performance is not bottle-necked by the gameplay code.

TBD.
- - -