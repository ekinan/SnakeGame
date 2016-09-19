#ifndef _FOOD_H
#define _FOOD_H

#include "point.h"

struct Grid;

struct Food {
	char symbol;
	int energy;
	struct Point pos;
};

void set_food(struct Food* food, char symbol, int energy, struct Point* pos);

struct Food* new_food(char symbol, int energy, struct Point* pos);
void free_food(struct Food* food);

int collides_with_food(struct Food* food, struct Point* point);

void draw_food(struct Food* food, struct Grid* environment);

void copy_food(struct Food* to, struct Food* from);

#endif
