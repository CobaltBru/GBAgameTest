#pragma once

#include "span.h"
#include "trace.h"
#include "scanline_sort.h"

typedef struct scanline
{
    span *global;
    span *active;
    trace end_trace;
    span active_end;
    int y;
}scanline;

void scanline_init(scanline *self)
{
    self->global = NULL;
    self->active = &self->active_end;
    self->end_trace = (trace) {
        .dx = 0,
        .dy = 0,
        .error = 0,
        .x = 2147483647
    };
    span_init(&self->active_end, &self->end_trace, NULL, 0, 0);
    self->y = -1;
}

void scanline_remove(scanline *self, span *span_)
{
    span *const prev = span_->prev;
    span *const next = span_->next;

    next->prev = prev;
    if (prev == NULL)
        self->active = next;
    else
        prev->next = next;
}

void scanline_realign(scanline *self, span *span_) {
	int		curr_x = span_->left->x;
	span *prev = span_->prev;

	while (prev != NULL && prev->left->x > curr_x) {
		prev->next = span_->next;
		span_->prev = prev->prev;
		prev->prev = span_;
		span_->next = prev;
		prev = span_->prev;
	}
	if (prev == NULL)
		self->active = span_;
}

static
void push_front(scanline *self, span *dst, span *src) {
	span	*prev = dst->prev;

	src->prev = prev;
	src->next = dst;
	dst->prev = src;
	if (prev != NULL)
		prev->next = src;
	else
		self->active = src;
}

void scanline_splice(scanline *self, span *span_) {
	span *src = self->global;
	span *next;

	while (src != NULL && src->min_y == self->y && src->left->x < span_->left->x) {
		next = src->next;
		push_front(self, span_, src);
		src = next;
	}
	self->global = src;
}

void scanline_move(scanline *self)
{
    span *next;

    self->y += 1;
    for (span *curr = self->active; curr != &self->active_end; curr = next)
    {
        next = curr->next;
        if (curr->max_y == self->y)
        {
            scanline_remove(self, curr);
            continue;
        }
        span_move(curr);
        scanline_realign(self, curr);
        scanline_splice(self, curr);
    }
    scanline_splice(self, &self->active_end);
}

void scanline_push(scanline *self, span *span_) {
	span_->next = self->global;
	self->global = span_;
}

void scanline_sort(scanline *self) {
	merge_sort(&self->global);
}

