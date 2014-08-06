#Solitaire

##Objective

Solitaire is a simple one-player board game where the player has to move pegs on a board with holes. The standard game fills the board with pegs except for one hole, but in this implementation the player can choose the initial empty hole. The objective is to empty the entire board until the player has one peg left.

![alt text](http://i.imgur.com/qQ2pD8h.gif "Example of a play")

##Play

Pegs can only move by jumping over another peg, into an empty hole two positions away. The jumped peg is then remove. The triangle board being composed of hexagonal tiles, pegs can jump orthogonally and diagonally.

In game, press ```Esc``` to quit and ```r``` to reset the board.

##Version

1.0

##Installation

 - Install the SDL2, SDL_Image, SDL_TTF libraries
 - Run ```make```

##Technologies 

* [C]
* [SDL2] - 2D and 3D video game development library

[C]:https://en.wikipedia.org/wiki/C_%28programming_language%29
[SDL2]:http://www.libsdl.org/
