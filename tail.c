#include "tail.h"
#include "grid.h" // <-- Debugging.


#include <stdio.h> // <-- Debugging.
#include <stdlib.h>

static void attach_tail(struct Tail* tail, struct BodyPart* part_to_attach) {
	struct Point attached_part_pos;
	copy_point(&attached_part_pos, &part_to_attach->pos);
	subtract_point(&attached_part_pos, &part_to_attach->dir);

	set_body_part(&tail->part, 'o', &attached_part_pos, &part_to_attach->dir);
}

struct Tail* new_tail_part(struct BodyPart* part_to_attach) {
	struct Tail* tail = malloc(sizeof(*tail));

	attach_tail(tail, part_to_attach);
	tail->rest = NULL;

	return tail; 	
}


void free_tail(struct Tail* tail) {
	struct Tail* cur_tail_node = tail;
	while (cur_tail_node) {
		struct Tail* next_tail_node = cur_tail_node->rest;
		free(cur_tail_node);
		cur_tail_node = next_tail_node;
	}

	free(tail);
}

void extend_tail(struct Tail* tail) {
	struct Tail* cur_tail_node = tail;
	while (cur_tail_node->rest) {
		cur_tail_node = cur_tail_node->rest;
	}

	cur_tail_node->rest = new_tail_part(&cur_tail_node->part);	
}


void move_tail(struct Tail* tail, struct Point* dir) {
	struct Tail* cur_tail_node = tail;
	while (cur_tail_node) {
		struct Point old_dir;
		copy_point(&old_dir, &cur_tail_node->part.dir);

		move_body_part(&cur_tail_node->part, dir);

		copy_point(dir, &old_dir);
		cur_tail_node = cur_tail_node->rest;
	}
}

void draw_tail(struct Tail* tail, struct Grid* environment) {
	struct Tail* cur_tail_node = tail;
	while (cur_tail_node) {
		draw_body_part(&cur_tail_node->part, environment);
		cur_tail_node = cur_tail_node->rest;
	}
}

int collides_with_tail(struct Tail* tail, struct Point* point) {
	struct Tail* cur_tail_node = tail;
	while (cur_tail_node) {
		if (collides_with_body_part(&cur_tail_node->part, point)) {
			return 1;
		}
		cur_tail_node = cur_tail_node->rest;
	}

	return 0;
}
