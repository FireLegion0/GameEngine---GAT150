**My Game Engine - A random little Platformer Game Engine**

Create a README for my game engine project. 
* It is using C++ 20 with SDL3, FMOD, BOX2D, rapidjson for serialization.
* It is a component based engine.
* It has an audio, input, physics, renderer systems.
* It also contains a demo game to show the engine with
  actors, components, tilemaps and UI.

In this little proto game, you simply control a character that can move left and right, jump, and attack. 
The goal is to survive as long as possible while avoiding and defeating enemies.

I included a respawn system, so when the player dies, they will respawn at the starting point.
Made it so that the player can restart as well.
I also made the Enemies give points when defeated, and the player can collect these points to increase their score.

Added Audio to the game, which includes music and when the player attacks.

It's a small game and probably not very exciting, but it was a fun project to work on and I learned a lot about game development in the process.
I do hope that whoever plays this game enjoys it!

Controls:
* CTRL + B - Builds the game
* F5 - Runs the game
* A - Move Left
* D - Move Right
* Space - Jump
* Right Shift - Attack