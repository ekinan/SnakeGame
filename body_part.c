#include "body_part.h"
#include "grid.h"

#include <stdio.h>
#include <stdlib.h>

void set_body_part(struct BodyPart* body_part, char symbol, struct Point *pos, struct Point* dir) {
	body_part->symbol = symbol;
	copy_point(&body_part->pos, pos);
	copy_point(&body_part->dir, dir);
}

struct BodyPart* new_body_part(char symbol, struct Point* pos, struct Point* dir) {
	struct BodyPart* body_part = malloc(sizeof(*body_part));
	set_body_part(body_part, symbol, pos, dir);

	return body_part;
}

void free_body_part(struct BodyPart* body_part) {
	free(body_part);
}

void move_body_part(struct BodyPart* body_part, struct Point* new_dir) {
	struct Point new_pos;
	copy_point(&new_pos, &body_part->pos);
	add_point(&new_pos, new_dir);

	copy_point(&body_part->dir, new_dir);
	copy_point(&body_part->pos, &new_pos);
}

void draw_body_part(struct BodyPart* body_part, struct Grid* environment) {
	overwrite_char(environment, &body_part->pos, body_part->symbol);
}

int collides_with_body_part(struct BodyPart* body_part, struct Point* point) {
	return equals_point(&body_part->pos, point);
}

void print_body_part(struct BodyPart* body_part) {
	printf("(%c, ", body_part->symbol);
	print_point(&body_part->pos);
	printf(", ");
	print_point(&body_part->dir);
	printf(")");
}
