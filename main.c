#include "game_world.h"
#include "input_handler.h"
#include "snake.h"
#include "point.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define WIDTH 15
#define HEIGHT 15

struct GameWorld game_world;

struct termios old_configt;

void configure_terminal_for_input() {
	struct termios configt;
	tcgetattr(STDIN_FILENO, &configt);
	old_configt = configt;
	configt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &configt);	
}

int main(int argc, char* argv[]) {
	init_game_world(&game_world, WIDTH, HEIGHT);

	configure_terminal_for_input();
	pthread_t input_handler = pthread_create(
		&input_handler,
		NULL,
		handle_user_key_press,
		NULL
	);


	int game_over = 0;
	while (!game_over) {
		sleep(1);
		pthread_mutex_lock(&game_world.lock);
		game_over = !do_turn(&game_world);
		display_game_world_fixed_cursor(&game_world);
		pthread_mutex_unlock(&game_world.lock);
	}

	display_game_world(&game_world);

	tcsetattr(STDIN_FILENO, TCSANOW, &old_configt);
	return 0; 
}
