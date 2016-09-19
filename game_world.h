#ifndef _GAME_WORLD_H
#define _GAME_WORLD_H

#include "grid.h"
#include "snake.h"
#include "food_array.h"

#include <pthread.h>

struct GameWorld {
	struct Grid environment;
	struct Snake snake;
	struct FoodArray food_array;
	pthread_mutex_t lock;
};

void init_game_world(struct GameWorld* game_world, unsigned width, unsigned height);
void destroy_game_world(struct GameWorld* game_world);

int do_turn(struct GameWorld* game_world);

void display_game_world(struct GameWorld* game_world);
void display_game_world_fixed_cursor(struct GameWorld* game_world);



#endif
