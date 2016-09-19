#include "point.h"
#include "grid.h"

#include <stdio.h>
#include <stdlib.h>

static void set_grid_dims(struct Grid* grid, unsigned width, unsigned height) {
	grid->width = width;
	grid->height = height;
}

void set_grid(struct Grid* grid, unsigned width, unsigned height) {
	set_grid_dims(grid, width, height);

	unsigned size = width*height;
	grid->contents = malloc(size*sizeof(char));
}

void destroy_grid(struct Grid* grid) {
	free(grid->contents);
	grid->contents = NULL;

	set_grid_dims(grid, 0, 0);
}




struct Grid* new_grid(unsigned width, unsigned height) {
	struct Grid* grid = malloc(sizeof(*grid));
	set_grid(grid, width, height);
	return grid;
}

void free_grid(struct Grid* grid) {
	destroy_grid(grid);
	free(grid);
}





static char* contents_ptr_at_indices(struct Grid* grid, unsigned i, unsigned j) {
	unsigned array_index = grid->width*i+j;
	return grid->contents + array_index;
}

static char* contents_ptr_at_point(struct Grid* grid, struct Point* point) {
	return contents_ptr_at_indices(grid, point->y, point->x);
}

char char_at(struct Grid* grid, struct Point* point) {
	return *contents_ptr_at_point(grid, point);
}


void overwrite_char(struct Grid* grid, struct Point* point, char new_char) {
	char* ptr_to_char = contents_ptr_at_point(grid, point);
	*ptr_to_char = new_char;
}

void overwrite_row(struct Grid* grid, unsigned row, char new_char) {
	struct Point row_start_point;
	set_point(&row_start_point, 0, row);
	
	char* row_start = contents_ptr_at_point(grid, &row_start_point);
	
	int i;
	for (i = 0; i < grid->width; ++i) {
		*row_start = new_char;
		++row_start;
	}
}

void overwrite_col(struct Grid* grid, unsigned col, char new_char) {
	struct Point col_start_point;
	set_point(&col_start_point, col, 0);

	char* col_start = contents_ptr_at_point(grid, &col_start_point);

	int i;
	for (i = 0; i < grid->height; ++i) {
		*col_start = new_char;
		col_start += grid->width;
	}
}

void overwrite_box(
	struct Grid* grid, 
	struct Point* start, 
	unsigned width, 
	unsigned height,
	char new_char
) {
	struct Point start_copy;
	copy_point(&start_copy, start);

	int i;
	for (i = 0; i < height; ++i) {
		char* col_start = contents_ptr_at_point(grid, &start_copy);

		int j;
		for (j = 0; j < width; ++j) {
			*col_start = new_char;
			++col_start;			
		}
		++start_copy.y;
	}	
}

void print_grid(struct Grid* grid) {
	char* cur_ptr = grid->contents;
	
	int i;
	for (i = 0; i < grid->height; ++i) {
		int j;
		for (j = 0; j < grid->width; ++j) {
			printf("%c", *cur_ptr);
			++cur_ptr;
		}
		printf("\n");
	}
}

void print_grid_fixed_cursor(struct Grid* grid) {
	print_grid(grid);

	int i;
	for (i = 0; i < grid->height; ++i) {
		printf("\x1b[A");
	}
} 
