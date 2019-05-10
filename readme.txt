
Test Mode: 4/5
 - You put in a lot of tests for your game, but most of the graphics stuff isn't quite as debuggable, especially the skybox and cubemap reflections.

Game Programming Requirements (30%):

 7% - Game rules/Physics     - 7/7
 - The game works well, but I can't see any feedback if I'm hitting the boss, other than his health bar goes down.  Otherwise it's quite good, love the variety of attacks the red boss has.
 3% - Audio                  - 2/3
 - Your audio cue class is working for your single sound, but it's not a scalable approach, you should be creating one audio cue for each type of sound effect, similar to all the other resources.  So you would have an audio cue for projectiles that contains a single vector of 3 projectile sounds, then the game code can play that single cue which will randomly select a sound.  Also, you guys didn't adjust the sound player object to be able to play multiple sounds at once.  The way it is now, each sound will cut off the previous one.
 3% - Saved game             - 3/3
 - Simple and clean, the only issue would be your function is called SaveSound and your options could have been placed in a helper class that would handle the loading/saving without the variables being mixed into the game class.
 4% - Scene management       - 4/4
 - The scene manager is good, but it took me a while to figure out why the game was being reset after a pause, I thought it was a bug in the scene manager, but it's a choice you guys made when hitting F1 it resets before popping up the options scene, a very odd choice.
 3% - Tweening               - 1/3
 - Your tween class looks like it's working since you're using a linear tween, but if you switch it out to any of the others, like elastic or bounce, it's either breaking or applying an odd acceleration curve.  This could use more work.
10% - Polish                 - 10/10
 - Excellent work overall, you guys have put together a fairly complete game.


Graphics Requirements (30%):

10% - Lighting               - 5/10
 - Most of your light code seems to be in a single shader (TexAndLight.frag), frankly, it's a bit of a mess.  As you say, you're not exposing the light properties to the mesh code, which is most of the work I looking for.
 5% - Rendering to a texture - 5/5
 - Perfect, it's a simple effect and could be better integrated into the project, but it works well.
 5% - Cubemaps               - 5/5
 - This seems to work, but you need to add better testing tools, unless you move/rotate your camera, you can't actually tell.
10% - Polish                 - 6/10
 - You put in a lot of systems, but they are all very rough around the edges.  Your game code is great, but your graphics stuff could use a lot of cleanup and organization.  Still, overall, like I said above, it came together and works well as a game.  Nice job guys!


Team members:
    -Kyle Johnson
    -Timothy Hood

Game Description:
    
	Our game has the player in a small arena with a boss that will move arround and use attacks. The player must dodge the bosses attacks while firing at the boss.
	The playaaaaaaaaaaaaaaaaaaaaaaaa
	Red Boss Differences
	-Laser Attack 

	Blue Boss Differences
	-Prismatic joint attack
	- if you stand still you wont take damage from projectiles(This is more so important for the both boss fight)

	Controlls:
	- WASD to move arround
	- Left mouse click to shoot
	- Right mouse click to teleport
	- F1 for Options menu
	- F2 for going back to the main menu
	- F3 for DebugMenu
	- F4 for immediatelly winning the fight(Inorder to get the unlock requirment for the both boss fight you will 
						need to win legitimately)

	Warning
Hit boxes on the bosses are extremely wonky

Game Programming Requirements (30%):

 7% - Game rules/Physics
    - Fixtures(The projectiles cant collide with the redboss / blue boss)
	- Sensors are used by all projectile attacks
	- Joints(One of the blue bosses attacks is moving the wall with a prismatic joint);
	- Raycasting(This is used by the player to attack)
  
 3% - Audio
    - Audio is placed in everything that isnt in the menus
	- Audio que system is inplace(we didnt use it for too much since it wasnt particularly necessary for our game)

 3% - Saved game
    - The game both loads and saves 
	- The Current highscore it gets overwritten if you get a higher high score
	- If the two bosses have been killed already or not(This will see if you can fight the final challenge of both bosses)
	- it also saves in the options menu if you have sound or not;
	- also in the options is a user interface turn on or off; 

 4% - Scene management
    - All types of scenes are created and stored in a scene manager;
	- every scene is able to exit out to a different scene (example if you press f2 in the gameplay screen you will go back to the main menu)
	- If the player presses f1 the options menu will appear up during gameplay and stop the pause screen;
 
 3% - Tweening
    - A tweening class has been created and is used.
	- the tweening is used in both the options menu and the main menu

5% TestMode
	-Press F3 twice to open up the debug menu. This can only be in use during the gameplay screens so either redboss scene or blueboss scene

10% - Polish
    - State machines: the bosses are completely controlled by multiple state machines one for the attack.
	- The bosses have multiple attacks
	Includeing
		-Line projectiles (Lines that go in a straight line)
		-Homing Projectils (Projectile that follow the player a little bit)
		-Lazer( The boss will move down the left side and shoot attack that are the lenght of the screen)
		-Magic Circle (Magic circles will appear and get faster till eventually fire will sprout and only then will damage be dealt)
		- Prismatic Attack (The blue boss will move a prismatic joint that will attack the player)

	Movement Options
		-The boss can teleport to nodes all across the arena
		-The boss can orbit around the player but only on certain restrained axises


	-An entire Score menu system is created that checks the amount of hits you took your score the high score and the differences between
	-A third boss fight with both of the bosses.
	-Multiple diffcultys
       
Graphics Requirements (30%):

10% - Lighting
    - lighting shader has been created and other textures can be reflected on the light(for our game we just used the floor texture but if you switched it to
	anything everything can be lit)
	-4 different lights with different colors are interacting withing red boss scene;
	-The only thing we couldnt accomplish is having a light move;
  
 5% - Rendering to a texture
    - when you beat the boss the fbo gets a render of the end screen and then distorts the image before giving you the score screen
	- You can quickly check this in any of the gameplay scenerios by pressing f4;
  
 5% - Cubemaps
    - A cube map surronds all gameplay screens
	- using the debug menu of F3 you can have a sphere appear in the center of the room that reflects the skybox(Yes megaman is part of the skybox)
  
10% - Polish
    - The post processing shader when the player wins against the boss(it is using the ripple but it also has many other layered on effects)
	- The players teleportation is used by a radius around the player and if the mouse coordinates are outside that the player is teleported to the closest
	point inside the radius(see playerobject for more details)
	-Mouse Coordinates inorder for the mouse coordinates to be working it took alot of math and computations
	-Health bar both the player and enemy have health bars that can be dynamically changed on will.
	-Score is used with 6 meshes and a photo dividing the uvs
	-A basic particle system is implemented with two diffrent particle effects


Progress Week 4
-A bunch of menus were made and are interactable
-Sound can be turned off in the options menu (And is saved to a json file and loaded)
-Tweening was added to the cursors
-Pixel art was created for most assets(We have to keep megaman after all)
-Boss now orbits around the player
-Teleportion game mechanic was added(a radius around the player they can teleport to and if the cursor if farther then the 
radius the player will move to the closest point in that direction that the radius can do)
for the sake of testing shooting has been removed but it still functions fine.


Progress Week 3(The reason why this week is a far bit less then the others is due to me spending most of my 
time debugging and some smaller improvments across the board)

-Created a basic SceneManager(Press the space bar to switch to the other scene)
-Created MachineGun Firemode for the boss
-Added Collision to the wall(For some of our GameObjects we desabled Physics bodys so the movement would be smooth)
-Added Shooting with the raycast.
-Projectiles now have a force put upon them so collisions can work
-Magic Circles Now deal damage to the player(For some reason the first one wont deal damage but everyone passed that one will)
-Shooting now damages the bosses health
-Additions to lighting were added(In the code no lighting is used in any of the scenes)

11

Progress Week 2

-Created Prismatic joint
-Created Particle Object
-Added Json(Only loading not saving)
-Added Audio
-The json file contains a sound if on bool variable to turn all the music off or on.
-Json File Contains the highscore
-Added Flame Effect to the magic circle
-Added Collision filtering
-Projectile now uses a direction vector


Progress Week 1

-Created a Boss setup
-Created a Healthbar setup(Currently they are just shown at the different values since projectiles dont deal damage yet)
-Created Statemachines for the bosses.
-Created Magical circles and projectiles that are object pooled and taken from the specific boss, and then delete themselves within the class.
-The Raycasting to the mouse coordinates are there but dont currently work.
