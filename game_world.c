#include "game_world.h"
#include "food.h"
#include "point.h"

#include <stdio.h>
#include <stdlib.h>

#define FOOD_FRACTION 20
#define FOOD_GEN_FREQ 4

static int turns_passed = 0;

static void update_environment(struct GameWorld* game_world);

static void init_game_environment(struct Grid* environment, unsigned width, unsigned height) {
	set_grid(environment, width, height);

	// Draw the walls
	overwrite_row(environment, 0, 'X');
	overwrite_col(environment, 0, 'X');
	overwrite_row(environment, height-1, 'X');
	overwrite_col(environment, width-1, 'X');

	// Draw the remaining space
	struct Point space_start;
	set_point(&space_start, 1, 1);
	overwrite_box(
		environment,
		&space_start,
		environment->width-2,
		environment->height-2,
		' '
		
	);
}

static void init_game_snake(struct GameWorld* game_world, unsigned width, unsigned height) {
	struct Point snake_start;
	set_point(&snake_start, width/2, height/2);

	struct Point init_snake_dir;
	set_point(&init_snake_dir, 1, 0);

	init_snake(&game_world->snake, &snake_start, &init_snake_dir);
}

static int is_outside_environment(struct Point* point, struct Grid* environment) {
	return point->x <= 0 || point->x >= (environment->width-1)
	    || point->y <= 0 || point->y >= (environment->height-1);
}

// For now, only one food object will exist.
static int randomly_generate_food(struct GameWorld* game_world) {
	struct Point food_pos;
	set_point(
			&food_pos, 
			rand() % game_world->environment.width,
			rand() % game_world->environment.height
	);

	if (
		collides_with_snake(&game_world->snake, &food_pos) ||
		collides_with_food_array(&game_world->food_array, &food_pos) >= 0 ||
		is_outside_environment(&food_pos, &game_world->environment)
	)  {
		return 0;
	}

	struct Food food;
	set_food(&food, '#', 1, &food_pos);

	add_food(&game_world->food_array, &food);
}

static void init_game_food(struct GameWorld* game_world, unsigned width, unsigned height) {
	init_food_array(&game_world->food_array, (width*height)/FOOD_FRACTION);

	int i;
	for (i = 0; i < game_world->food_array.max/2; ++i) {
		while (!randomly_generate_food(game_world));
	}
}

void init_game_world(struct GameWorld* game_world, unsigned width, unsigned height) {
	init_game_environment(&game_world->environment, width, height);
	init_game_snake(game_world, width, height);
	init_game_food(game_world, width, height);

	pthread_mutex_init(&game_world->lock, NULL);

	update_environment(game_world);
}

void destroy_game_world(struct GameWorld* game_world) {
	destroy_grid(&game_world->environment);
	destroy_snake(&game_world->snake);
	destroy_food_array(&game_world->food_array);

	pthread_mutex_destroy(&game_world->lock);
}

static int check_snake_loc(struct GameWorld* game_world) {
	char char_at_snake_head = char_at(&game_world->environment, &game_world->snake.head.pos);
	if (char_at_snake_head == 'X') { // Game over, hit a wall
		return 0;
	}

	if (collides_with_tail_snake(&game_world->snake)) {
		return 0;
	}

	int collision_index = collides_with_food_array(
		&game_world->food_array, 
		&game_world->snake.head.pos
	);
	if (collision_index >= 0) { // Feed snake
		struct Food food = food_at(&game_world->food_array, collision_index);
		food_at(&game_world->food_array, collision_index);
		remove_food(&game_world->food_array, collision_index);
		eat_snake(&game_world->snake, &food);
	}

	return 1;
}

static void clear_game_world(struct GameWorld* game_world) {
	struct Point environment_start;
	set_point(&environment_start, 1, 1);

	overwrite_box(
		&game_world->environment,
		&environment_start,
		game_world->environment.width - 2,
		game_world->environment.height - 2,
		' '
		
	);
}

static void update_environment(struct GameWorld* game_world) {
	clear_game_world(game_world);
	draw_snake(&game_world->snake, &game_world->environment);
	draw_food_array(&game_world->food_array, &game_world->environment);
}

int do_turn(struct GameWorld* game_world) {
	if (!(turns_passed % FOOD_GEN_FREQ)) {
		randomly_generate_food(game_world);	
	}
	move_snake(&game_world->snake);

	int turn_successful = check_snake_loc(game_world);
	update_environment(game_world);
	++turns_passed;

	return turn_successful;
}

void display_game_world(struct GameWorld* game_world) {
	print_grid(&game_world->environment);
}

void display_game_world_fixed_cursor(struct GameWorld* game_world) {
	print_grid_fixed_cursor(&game_world->environment);		
}
