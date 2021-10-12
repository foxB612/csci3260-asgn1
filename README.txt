CSCI3260 Assignment 1

 - Name: 		********
 - Student ID:	1155******

Objects:
 - Ground                    2D plane
 - Cliff                     2D planes, connected with ground
 - Log                       3D object
 - Stump                     3D object
 - Tree                      two 3D objects
 - Bushes                    3D object
 - Character (named River)   three 3D objects
 - Moon & Rabbit *           2D planes
 - Stars                     Tiny triangles

* The moon is located at the east sky. Rotate view counterclockwise by 90 degrees to see the moon.

Manipulation:
 - Camera
   The camera is always focused on the character River.
   - Q & E
     Rotate the camera horizontally.
   - Z & X
     Rotate the camera vertically within a specific range (0 - 90).
 - Model Transformation:
   - W A S D
     Move River around within a specific range.
     The moving direction is adapted to the camera direction (Try rotate the camera 90 degrees and move).
   - C & V
     Scale the bushes.
   - R
     Rotate the tree.
 - Projection
   - F & G
     Change the fov of the perspective projection while keeping `aspect`, `near` and `far` unchanged.
 - Easter Egg
   - Space
     Show/Hide the rabbit on the moon.

This is a scene from the game "To The Moon".
The scene: https://steamcommunity.com/sharedfiles/filedetails/?id=709026528
The rabbit on the moon: https://www.deviantart.com/stphq/art/Origami-Rabbit-To-The-Moon-585676279

"What if you forget... or get lost?"
"Then we can always regroup on the moon, silly!"
