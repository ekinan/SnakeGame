#include "body_part.h"
#include "food.h"
#include "grid.h" // FOR DEBUGGING
#include "tail.h"
#include "snake.h"

#include <stdlib.h>

#define INIT_REQ_ENERGY_FOR_GROWTH  1
#define REQ_ENERGY_FOR_GROWTH_INC_FACTOR 1

void init_snake(struct Snake* snake, struct Point* head_pos, struct Point* init_dir) {
	set_body_part(&snake->head, 'O', head_pos, init_dir);
	snake->tail = NULL;
	copy_point(&snake->dir, init_dir);
	snake->consumed_energy = 0;
	snake->req_energy_for_growth = INIT_REQ_ENERGY_FOR_GROWTH;	
}

void destroy_snake(struct Snake* snake) {
	free_tail(snake->tail);
}

struct Snake* new_snake(struct Point* head_pos, struct Point* init_dir) {
	struct Snake* snake = malloc(sizeof(*snake));
	init_snake(snake, head_pos, init_dir);
	return snake;
}

void free_snake(struct Snake* snake) {
	destroy_snake(snake);
	free(snake);
}


static void grow_snake(struct Snake* snake) {
	snake->req_energy_for_growth += REQ_ENERGY_FOR_GROWTH_INC_FACTOR;
	snake->consumed_energy = 0;

	if (!snake->tail) {
		snake->tail = new_tail_part(&snake->head);
		return;
	}

	extend_tail(snake->tail);
}

void eat_snake(struct Snake* snake, struct Food* food) {
	snake->consumed_energy += food->energy;

	if (snake->consumed_energy >= snake->req_energy_for_growth) {
		grow_snake(snake);
	}
}


void change_dir_snake(struct Snake* snake, struct Point* new_dir) {
	copy_point(&snake->dir, new_dir);	
}

void move_snake(struct Snake* snake) {
	struct Point old_head_dir;
	copy_point(&old_head_dir, &snake->head.dir);

	move_body_part(&snake->head, &snake->dir);
	move_tail(snake->tail, &old_head_dir);
}

void draw_snake(struct Snake* snake, struct Grid* environment) {
	draw_body_part(&snake->head, environment);
	draw_tail(snake->tail, environment);
}

int collides_with_snake(struct Snake* snake, struct Point* point) {
	return collides_with_body_part(&snake->head, point)
	    || collides_with_tail(snake->tail, point);
}

int collides_with_tail_snake(struct Snake* snake) {
	return collides_with_tail(snake->tail, &snake->head.pos);
}
