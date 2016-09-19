#ifndef _GRID_H
#define _GRID_H

struct Point;

struct Grid {
	char* contents;
	unsigned width;
	unsigned height;
};

void set_grid(struct Grid* grid, unsigned width, unsigned height);
void destroy_grid(struct Grid* grid);

struct Grid* new_grid(unsigned width, unsigned height);
void free_grid(struct Grid* grid);

char char_at(struct Grid* grid, struct Point* point);

void overwrite_char(struct Grid* grid, struct Point* point, char new_char);
void overwrite_row(struct Grid* grid, unsigned row, char new_char);
void overwrite_col(struct Grid* grid, unsigned col, char new_char);
void overwrite_box(
	struct Grid* grid, 
	struct Point* start, 
	unsigned width, 
	unsigned height, 
	char new_char
);

void print_grid(struct Grid* grid);
void print_grid_fixed_cursor(struct Grid* grid);

#endif
