#include "food.h"
#include "grid.h"

#include <stdio.h>
#include <stdlib.h>

void set_food(struct Food* food, char symbol, int energy, struct Point* pos) {
	food->symbol = symbol;
	food->energy = energy;
	copy_point(&food->pos, pos);
}

struct Food* new_food(char symbol, int energy, struct Point* pos) {
	struct Food* food = malloc(sizeof(*food));
	set_food(food, symbol, energy, pos);
}

void free_food(struct Food* food) {
	free(food);
}

int collides_with_food(struct Food* food, struct Point* point) {
	return equals_point(&food->pos, point);
}

void draw_food(struct Food* food, struct Grid* environment) {
	overwrite_char(environment, &food->pos, food->symbol);
}

void copy_food(struct Food* to, struct Food* from) {
	to->symbol = from->symbol;
	to->energy = from->energy;
	copy_point(&to->pos, &from->pos);
}
