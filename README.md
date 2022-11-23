# cat-and-mouse

> A Command line game of Cat and mouse (2 player game).

> Before the game begins, the players should enter their usernames for referencing during the game.

> At the start of the game, the mice occupy the first 21 squares of the board.

> The player using cats selects the position where he wishes to place his cats between the 22nd and 28th squares inclusive e.g 23 27

> Pieces can move vertically, horizontally and diagonally

> To make a move, enter the initial and final position of the piece e.g 16 24

> Pieces can only move 1 square at a time except in the case the move is a cat killing a mouse in which the cat jumps over the mouse square to the next e.g 22 24

> The cat is not allowed to move into the squares 33 to 41

> Enter 9999 at any point in the game to save current state

> If a cat misses an opportunity to kill a mouse, the cat dies in it's place

> The goal of the mice is to fill up the squares 33 to 41. When this happens, the game ends and mice win

> If all cats die, the game ends and mice win (In the same way, if all mice die, cats win)

![Cat Mouse Board](https://github.com/dullbenz/cat-and-mouse/blob/master/usage-images/Screenshot%20from%202022-11-23%2010-35-00.png)

Run the ```make``` command in the project directory to build the project

Run the file ```./output/main ``` to launch the application
