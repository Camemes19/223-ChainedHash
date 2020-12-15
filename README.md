  
 **Creators:** "Quinn" John Barnwell, Cameron Jamieson, Svetoslav Dimitrov
 
 
 **Game idea:** For the PA 6 assignment, it was decided to make a bullet hell 2D down style game implementing the use of 
                the Godot game engine as a way to make the game. The idea was for there to be a single-player mode where the player 
                would face progressively challenging enemies on the map while getting a score for however many enemies killed. This score 
                could be placed into a priority queue that could keep track of the top scores. While the player is battling the enemies 
                special keywords will be shown on the screen that can be later used in the two-player mode of the game where two players 
                will get to battle each other. At the start of the game, the two players can enter the special keywords to unlock better 
                bullet abilities to battle with this would be implemented with a hash table, otherwise, the player would get the default ability. 
 
** What was accomplished:** We were able to accomplish successively player movement, game map, bullet physics, player and bullet 
                            collision, pause menu, and implementation of a hash table to control bullet ability.
     
 
** Controls:** wasd for movement or arrow keys, space or left mouse button for firing bullets, and escape to acces menu.


**notes:**  the menu for changing bullets was not fully implemented, while it is entirely possible to do it manuelly in the player.cpp source file.
            Also an executable was set up so that the game may be runned without having to set up godot with c++ which requires getting godot and also
            dowloading the godot github files as well and setting both up to work together. 