#ifndef _POINT_H
#define _POINT_H

struct Point {
	int x;
	int y;
};

struct Point calc_dir(struct Point* p1, struct Point* p2);

void set_point(struct Point* point, int x, int y);

struct Point* new_point(int x, int y);
void free_point(struct Point* point);


void add_point(struct Point* point, struct Point* added_point);
void subtract_point(struct Point* point, struct Point* subtracted_point);

int equals_point(struct Point* first, struct Point* second);

void copy_point(struct Point* to, struct Point* from);

void print_point(struct Point* point);

#endif
