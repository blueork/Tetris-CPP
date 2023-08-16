# Tetris-CPP
A graphical Tetris game made in C++ using SFML Graphics Library

### Instructions on how to run the game
**NOTE: The following commands are to be run on Terminal** 
  1. Ensure that you have the GNU G++ Compiler, if not run the following command
     `sudo apt-get install g++`
  2. Ensure that you have the SFML Library, if not run the following command
     `sudo apt-get install libsfml-dev1
  2. Compile the game
     `g++ -c main.cpp`
  3. Link with the SFML Library
     `g++ main.o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system`
  4. Launch the game by
     `./sfml-app`
  5. Enjoy the gameplay!!

**NOTE: The game currently has a bug in which even after exiting the game either via the close button or through in-game command, the music still runs in the background, thus, the game needs to be closed manually by `Ctrl C` in the terminal.** 
  
