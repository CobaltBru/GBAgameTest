#pragma once
#include "scanline.h"

static
int	compare(span const *a, span const *b) {
	return (a->min_y < b->min_y || (a->min_y == b->min_y && a->left->x < b->left->x));
}

static
void split(span *head, span **a, span **b) {
	span *slow = head;
	span *fast = head->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
}

static
span *merge(span *a, span *b) {
	span *result = NULL;
	span **tmp = &result;

	while (a != NULL && b != NULL) {
		if (compare(a, b)) {
			*tmp = a;
			tmp = &a->next;
			a = a->next;
		} else {
			*tmp = b;
			tmp = &b->next;
			b = b->next;
		}
	}
	while (a != NULL) {
		*tmp = a;
		tmp = &a->next;
		a = a->next;
	}
	while (b != NULL) {
		*tmp = b;
		tmp = &b->next;
		b = b->next;
	}
	*tmp = NULL;
	return (result);
}

static
void merge_sort(span **head_ref) {
	span	*head = *head_ref;
	span	*a;
	span	*b;

	if (head == NULL || head->next == NULL)
		return ; //base case
	split(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*head_ref = merge(a, b);
}
