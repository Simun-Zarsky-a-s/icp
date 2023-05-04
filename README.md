# Project documentation to the subject ICP
* ***Name***: Daniel Žársky, Samuel Šimún
* ***Login***: xzarsk04, xsimun04
* ***E-mail***: xzarsk04@stud.fit.vutbr.cz, xsimun04@stud.fit.vutbr.cz


The task was to create an application using C++ and its graphics library Qt.
The player/user is able to play the game and at the same time replay or step their game
afterward.<br>
We proceeded with pair programming to create this project and together we were able to create a 
fully functional application.

## Map parsing
Map parsing ensures class `Resources` which temporarily stores loaded values and the game map.
The map is read from the given file. At first, the program reads the first line of the file and based on given values allocates
the matrix for the map. The values are loaded and checked by a function `std::stoi()`. After that, the matrix is loaded char by char. After reading the map, the map is checked, whether it contains
expected characters, whether it responds to given dimensions and whether it contains exactly one target, and one start.
A special case is loading the map from a log file which contains also other information. For this purpose is the loading function adjusted to read only the map.
To avoid internal errors the map is checked as usual.
## Gameplay

After launching the app, the player selects their settings and starts the game. 
The following sections describe these actions and entities.

### Settings 
Settings characterize the course of the game and have a great influence on it. General settings (even those that cannot 
be modified by the player) are stored in the Sources class. <br>
Settings that are available only to the player are :
* **Choose Map** - The player has the option to choose a map from their portfolio. If the player does not select a map 
from his local resource, the default map is selected.
* **Choose Log** - The player can customize the path from which destination to access the log file. If not specified, 
the log file will be selected in the root directory of the program.
* **Mode Game / Mode Player** - A setting that determines under which mode the application will run.
* **Set FPS** - Sets the FPS (Frame per second) which characterizes at what speed new frames will be generated.
* **Ghost speed** - Specifies at what speed the ghosts will move around the map.

Working with these parameters also determines the difficulty the player will face.

### Gamemap
When the game starts, map objects are loaded and placed in the scene. These objects are divided into 3 parts:
* **Grass** - Players and ghosts can move freely on these fields.
* **Wall** - The border for ghosts and players that borders the grass
* **Key** - The Entity the player is tasked with taking. When the player intersects with the key, the map 
changes to grass.
* **Door** - The goal that the player must achieve, the door becomes active only when the player 
collects all the keys from the map.

The map is divided into a 2D matrix in which a block represents just one character from the input map. Also, the map
is surrounded by a wall which prevents the player from leaving the map. <br>
On the map, the player and the ghosts can move freely according to the settings. Blocks are divided for player and 
ghosts according to **SWIFT** settings. This means that if SWIFT is set to 9 then 1 block will be divided into 9 subblocks 
for the player and ghost to move around.

### GUI
The opening window is created in the class `WelcomeWin`. The class uses `QLabel` for implementing the Pacman picture, the main title and to fill the background.
For other interactive elements is used `QPushBUtton`. Each button is connected to a function to take action. Buttons `map_button` and `file_button` are using `QFileDialog` to choose the file.
To set value from the user in other buttons is used a function `QInputDialog`. The style of the elements is set in the beginning of the class definition by a function `setStyleSheet` called on the parent QWidget.
The same procedure is used to create a window at the end of the game in class `EndWin`.
### Player
The player represents a moving entity that can be controlled by the user. It can move at will around the map. 
His task is to collect all the keys from the map and arrive at the location of the door, thus ending the game with a win. <br>
If the player encounters a ghost during this task, the game ends in a loss.
The user can control the player in two ways:
* **Keypad control** - The player responds to the **Arrow** and **W-A-S-D** keys. Moves according to the keys pressed. 
However, if the user is near a wall and directs the player into the wall, the game will not allow the player to do so
and will continue until the player hits the wall in the original direction.
* **Mouse control** - The player tries to get to the place where the user clicked. First he tries to align the x-axis 
and then the y-axis. In case he hits a wall, these actions are switched. The control ends when the player arrives at 
the clicked location the x-axis and y-axis are equal to the click location.

### Ghosts

The movement of the ghosts is initialized in the `game scene`, where the function `update_ghosts` calls for each ghost its functions to update their position.
To get a new direction ghost takes the position of the player and tries to get on his x or y coordinates. In case of hitting a wall, the ghost changes strategy and tries to get on the other coordinate.
After setting the direction the ghost set its next position. 
Based on this position the game_scene checks the intersection of their position with the walls. In case of hitting the wall, the scene sets a flag change to `change` the strategy for setting the direction.
At the end, the pixmap of the ghost is adjusted to its direction and the position is written to the log.
## Logging 
Logging is done in such a way that when the game is started in the normal way, it is automatically generated to the 
file that was characterized in the settings. 

### Log format
The log starts with the START label followed by the logs per tics.

* Player: 
  * [tick_order] P [direction] [x-position] [y-position]
* Ghost:
  * [tick_order] G [order_of_ghost] [direction] [x-position] [y-position]
* Key:
  * [tick_order] K


### Writing log
When logging is started, a map is automatically added to the log file. Then the START label is inserted which 
characterizes from when the logs start to be logged.
Then the events that happened during one tick start to be inserted.
When the game ends, the last entry is written to the log with an **E** label to indicate that the game is not continuing.

### Reading log
If the user chooses the playback mode, the map that was entered in the settings is ignored and the map from the log is loaded. <br>
Then, when all map components are loaded, they will play whichever mode the user chooses.
<br>
<br>
The playback options are characterised by pressing the key: 
* **Left arrow / A** - stepping forward one record at a time
* **Right arrow / D** - stepping backwards one record at a time
* **Up arrow / W** - fast forwards playback
* **Down arrow / S** - fast backwards playback 