#ifndef _FOOD_ARRAY_H
#define _FOOD_ARRAY_H

struct Food;
struct Point;
struct Grid;

struct FoodArray {
	struct Food* food;
	int max;
	int count;
};

void init_food_array(struct FoodArray* food_array, int max);
void destroy_food_array(struct FoodArray* food_array);

struct Food food_at(struct FoodArray* food_array, int index);

void add_food(struct FoodArray* food_array, struct Food* food);
void remove_food(struct FoodArray* food_array, int index);

int collides_with_food_array(struct FoodArray* food_array, struct Point* point);

void draw_food_array(struct FoodArray* food_array, struct Grid* environment);

#endif
