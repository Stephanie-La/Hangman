#include "my_string.h"
#include "generic.h"

typedef void* GENERIC_VECTOR;

GENERIC_VECTOR generic_vector_init_default(void(*fpAssignment)(Item* pLeft, Item right), void(*fpDestroy)(Item* phItem));

Status generic_vector_push_back(GENERIC_VECTOR hVector, Item hItem);

int generic_vector_get_size(GENERIC_VECTOR hVector);

Status generic_vector_pop_back(GENERIC_VECTOR hVector);

Item* generic_vector_at(GENERIC_VECTOR hVector, int index);

void generic_vector_destroy(GENERIC_VECTOR* phVector);

Boolean generic_vector_empty(GENERIC_VECTOR hVector);
	