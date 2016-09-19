#include "input_handler.h"
#include "game_world.h"
#include "point.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

extern struct GameWorld game_world;

static int get_arrow_key() {
	int ch = getchar();
	if (ch != 27) {
		return 0;
	}

	ch = getchar();
	if (ch != 91) {
		return 0;
	}

	ch = getchar();
	if (ch < 65 || ch > 68) {
		return 0;
	}

	return ch;
}

static void get_new_snake_dir(struct Point* dir, int arrow_key) {
	switch (arrow_key) {
		case 65:
			set_point(dir, 0, -1);
			break;
		case 66:
			set_point(dir, 0, 1);
			break;
		case 67:
			set_point(dir, 1, 0);
			break;
		case 68:
			set_point(dir, -1, 0);
			break;
	}
}

void* handle_user_key_press() {
	while (1) {
		int arrow_key = get_arrow_key();
		if (arrow_key) {
			struct Point new_snake_dir;
			get_new_snake_dir(&new_snake_dir, arrow_key);

			pthread_mutex_lock(&game_world.lock);
			change_dir_snake(&game_world.snake, &new_snake_dir);
			pthread_mutex_unlock(&game_world.lock);
		}
	}
}
