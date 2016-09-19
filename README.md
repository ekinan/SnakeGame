# Snake Game
------------------------------------------------------------------------------------------------------------------
This is my C-based implementation of the snake game as a personal project. It is 
incomplete, but so far the user has the ability to move a snake-like creature
around and eat some of the food around the game map. The key symbols are:
	"O" -> Snake head
	"o" -> Snake tail
	"X" -> Wall
	"#" -> Food
	
I wanted to write this to get a better idea of how OOP design might work in
C, and to also check out how pthreads works. That's why there's not really
any security in the program (e.g. array out of bounds checking).

The snake grows each time you eat a "#" object, and it is game over if the
snake hits the wall, or if it is eating its own tail. Press the arrow keys
to move the snake around - note that the game will take your most recent
key press as being the next place that the snake should go.

I hope to add a feature to track the user's score, and to let the game world
periodically generate the food objects (right now it generates them once, and
doesn't do it again). Also, there is a slight bug with the snake's growth.
I will fix these in due time. But the game is playable in its present form!

------------------------------------------------------------------------------------------------------------------
Please run the program on a Linux machine with pthreads capabilities.

To compile the program, please type
	make clean
	make
into the command prompt.

To run the program, please type
	./a.out
into the command prompt.

