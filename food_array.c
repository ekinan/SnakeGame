#include "food_array.h"
#include "food.h"
#include "grid.h"
#include "point.h"

#include <stdio.h> // For debugging
#include <stdlib.h>

void init_food_array(struct FoodArray* food_array, int max) {
	food_array->max = max;
	food_array->count = 0;

	food_array->food = malloc(food_array->max*sizeof(*food_array->food));
}

void destroy_food_array(struct FoodArray* food_array) {
	free(food_array->food);
}

// Not worrying about security here
struct Food food_at(struct FoodArray* food_array, int index) {
	return food_array->food[index];
}

void add_food(struct FoodArray* food_array, struct Food* food) {
	copy_food(&food_array->food[food_array->count++], food);
}

void remove_food(struct FoodArray* food_array, int index) {
	int i;
	for (i = index; i < (food_array->count-1); ++i) {
		copy_food(&food_array->food[i], &food_array->food[i+1]);	
	}

	--food_array->count;
}

int collides_with_food_array(struct FoodArray* food_array, struct Point* point) {
	int i;
	for (i = 0; i < food_array->count; ++i) {
		if (collides_with_food(&food_array->food[i], point)) {
			return i;
		}
	}	

	return -1;
}

void draw_food_array(struct FoodArray* food_array, struct Grid* environment) {
	int i;
	for (i = 0; i < food_array->count; ++i) {
		draw_food(&food_array->food[i], environment);
	}
}
