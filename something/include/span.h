#pragma once

#include "trace.h"

typedef struct span span;
struct span {
	span *prev;
	span *next;
	trace *left;
	trace *right;
	int	min_y;
	int	max_y;
};

void span_init(span *self, trace *left, trace *right, int min_y, int max_y) {
	self->prev = NULL;
	self->next = NULL;
	self->left = left;
	self->right = right;
	self->min_y = min_y;
	self->max_y = max_y;
}

void span_move(span *self) {
	trace_move(self->left);
	trace_move(self->right);
}