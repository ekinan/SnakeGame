#include "Point.h"

#include <stdio.h>
#include <stdlib.h>

struct Point calc_dir(struct Point* p1, struct Point* p2) {
	struct Point dir;
	copy_point(&dir, p2);

	subtract_point(&dir, p1);

	//TODO: Convert this to a unit vector.
	return dir;
}

void set_point(struct Point* point, int x, int y) {
	point->x = x;
	point->y = y;
}


struct Point* new_point(int x, int y) {
	struct Point* point = malloc(sizeof(*point));
	set_point(point, x, y);

	return point;
}

void free_point(struct Point* point) {
	free(point);
}



void add_point(struct Point* point, struct Point* added_point) {
	point->x += added_point->x;
	point->y += added_point->y;
}

void subtract_point(struct Point* point, struct Point* subtracted_point) {
	point->x -= subtracted_point->x;
	point->y -= subtracted_point->y;
}

int equals_point(struct Point* first, struct Point* last) {
	return first->x == last->x && first->y == last->y;
}

void copy_point(struct Point* to, struct Point* from) {
	set_point(to, from->x, from->y);
}

void print_point(struct Point* point) {
	printf("(%d, %d)", point->x, point->y);
}
