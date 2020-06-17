# SzybciorPlusPlus

A 2d platformer project.

Made in Visual Studio Community 2019.
To run the game, open the VC++ Project file, in the configuration field choose Debug and x86 and you are ready to go.
**SFML version:** SFML 2.5.1

### How to play:
**Movement:** You can move your character using **A** - left, **D** - right and **Space** - jump (or rather in current state - fly)
**Editing:** **LMB** - placing/choosing tiles, **RMB** - removing tiles, **C** - enable/disable collision on the tile
You can Load/Save the game map in the Editor.
The goal of the game is yet to be established.
Try not to get killed by deadly spikes! (Fortunately, you can't die from them, for now at least)


### Changelog:

**FixPatch (17/06/2020):**
- Added support for 1920x1080 and resolutions below
- Tilemap is now 100x80 (was 50x40)
- Fixed collision (problem with updating player before tilemap collision)
- Fixed starting position of a player
- Minor changes to GUI elements in states
- Created a StateData class for easier data transfer in all states	
	- Added a gridSize variable
- Created bakcup of the tilemap .szybcior file
- ~~Added fullscreen dropbox in settings~~ Gave up
