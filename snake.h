#ifndef _SNAKE_H
#define _SNAKE_H

#include "body_part.h"
#include "tail.h"

struct Food;
struct Point;

struct Snake {
	struct BodyPart head;
	struct Tail* tail;
	struct Point dir;
	unsigned consumed_energy;
	unsigned req_energy_for_growth;
};

void init_snake(struct Snake* snake, struct Point* head_pos, struct Point* init_dir);
void destroy_snake(struct Snake* snake);

struct Snake* new_snake(struct Point* head_pos, struct Point* init_dir);
void free_snake(struct Snake* snake);

void eat_snake(struct Snake* snake, struct Food* food);

void change_dir_snake(struct Snake* snake, struct Point* new_dir);
void move_snake(struct Snake* snake);

void draw_snake(struct Snake* snake, struct Grid* environment);

int collides_with_snake(struct Snake* snake, struct Point* point);

int collides_with_tail_snake(struct Snake* snake);


#endif
