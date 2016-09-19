#ifndef _TAIL_H
#define _TAIL_H

#include "body_part.h"

struct Grid;

struct Tail {
	struct BodyPart part;
	struct Tail* rest;
};

struct Tail* new_tail_part(struct BodyPart* part_to_attach);

void free_tail(struct Tail* tail);

void extend_tail(struct Tail* tail);

void move_tail(struct Tail* tail, struct Point* dir);

void draw_tail(struct Tail* tail, struct Grid* environment);

int collides_with_tail(struct Tail* tail, struct Point* point);

#endif
