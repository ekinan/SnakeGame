# Snake Game
------------------------------------------------------------------------------------------------------------------
This is my C-based implementation of the snake game as a personal project. The key symbols are:
	"O" -> Snake head
	"o" -> Snake tail
	"X" -> Wall
	"#" -> Food
	
I wanted to write this to get a better idea of how OOP design might work in
C, and to also check out how pthreads works. That's why there's not really
any security in the program (e.g. array out of bounds checking).

The snake grows when you eat enough "#" objects, and it is game over if the
snake hits the wall, or if it is eating its own tail. Press the arrow keys
to move the snake around - note that the game will take your most recent
key press as being the next place that the snake should go.

Note there's a slight concurrency error at the end, where the input handler and the score handler
functions don't terminate before printing out the final state of the game world and the "Game over!"
part. I'm going to fix these later.

------------------------------------------------------------------------------------------------------------------
To compile the program, please type
	make clean
	make
into the command prompt.

To run the program, please type
	./a.out
into the command prompt.
