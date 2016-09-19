#ifndef _BODY_PART_H
#define _BODY_PART_H

#include "point.h"

struct Grid;

struct BodyPart {
	char symbol;
	struct Point pos;
	struct Point dir;
};

void set_body_part(
	struct BodyPart* body_part, 
	char symbol, 
	struct Point *pos, 
	struct Point* dir
);

struct BodyPart* new_body_part(
	char symbol, 
	struct Point* pos, 
	struct Point* dir
);

void free_body_part(struct BodyPart* body_part);

void move_body_part(struct BodyPart* body_part, struct Point* dir);

void draw_body_part(struct BodyPart* body_part, struct Grid* environment);

int collides_with_body_part(struct BodyPart* body_part, struct Point* point);

void print_body_part(struct BodyPart* body_part);

#endif
