[WEEK 1]
OBJECTIVE: Return a list of enemies that are behind, in front of, or perpendicular to the player.
APPROACH: Using C++, (without a game engine), I simulated a player location, and forward direction utilizing a custom 'Vector3' struct which holds x,y,z values. 
I then calculated the dot product between 1) the player's normalized direction vector and 2) the normalized vector of player location - enemy location.
This would return us the cosine of the angle between the player's location/facing direction, and the enemy location. 
If the result was negative, then the enemy must be behind the player since cosine of pi (non inclusive) -> 2pi (non inclusive) tells us that the angle between the location of the enemy compared to the facing direction of the player and it's location, is negative.
-We assumed the player FOV to be a full 180 degrees. 
-The player's location is always at (0,0,0).
-The player's forward vector is always (1,0,0).
-The amount of enemies spawned is 100.
-The location of the enemies are randomly generated.

GOALS FOR IMPROVEMENT:
-Expand the system to input a custom vector for player location, and facing direction.
-Expand to input a custom number of enemies to spawn.
-Expand to include behind/infront of player check for a field of vision cone of the player of (THETA) degrees.
