#include <stdlib.h>
#include <stdio.h>
#include "generic_vector.h"
#include "generic.h"


struct generic_vector{
  int size;
  int capacity;
  Item* data;
  void (*fpAssignment)(Item* pLeft, Item right);
  void (*fpDestroy)(Item* phItem);
 
};

typedef struct generic_vector Generic_vector;

GENERIC_VECTOR generic_vector_init_default(void(*fpAssignment)(Item* pLeft, Item right),
	void(*fpDestroy)(Item* phItem)){
	Generic_vector* pVector;
	pVector = (Generic_vector*)malloc(sizeof(Generic_vector));
	int i;
	if(pVector != NULL){
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->fpAssignment = fpAssignment;
		pVector->fpDestroy = fpDestroy;
		pVector->data = (Item*)malloc(sizeof(Item)*pVector->capacity);
	 	if(pVector->data == NULL){
			free(pVector);
			return NULL;
		}
		else{
			for(i = 0; i < pVector->capacity; i++){
				pVector->data[i] = NULL;
			}
		}
	}
		return (GENERIC_VECTOR)pVector;
}

void generic_vector_destroy(GENERIC_VECTOR* phVector){
	Generic_vector* pVector = (Generic_vector*)* phVector;
	int i;
	for(i = 0; i < pVector->size; i++){
			pVector->fpDestroy(&(pVector->data[i]));
	}
	free(pVector->data);
	free(pVector);
	*phVector = NULL;
	return;	
}


Status generic_vector_push_back(GENERIC_VECTOR hVector, Item hItem){
	Generic_vector* pVector = (Generic_vector*)hVector;
	Item* pTemp; //array of void pointers
	int i;
	if(pVector->size >= pVector->capacity){
		pTemp = (Item*)malloc(sizeof(Item) * 2 * pVector->capacity);
		if(pTemp == NULL){
			return FAILURE;
		}
		pVector->capacity *= 2;
		for(i = 0; i < pVector->size; i++){
			pTemp[i] = pVector->data[i]; // copy the existing pointers
		}
		for(i = pVector->size; i < pVector->capacity; i++){
			pTemp[i] = NULL;
		}
		free(pVector->data);
		pVector->data = pTemp;
	}
	pVector->fpAssignment(&pVector->data[pVector->size], hItem);
	if (pVector->data[pVector->size] == NULL){
		return FAILURE;
	}
	pVector->size++;
	return SUCCESS;
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector){
	Generic_vector* pVector = (Generic_vector*)hVector;
	if(pVector->size <= 0){
		return FAILURE;
	}
	pVector->fpDestroy(&(pVector->data[pVector->size - 1]));
	pVector->size--;
	return SUCCESS;
}

Item* generic_vector_at(GENERIC_VECTOR hVector, int index)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
	if (index < 0 || index >= pVector->size)
	{
		return NULL;
	}
	return &(pVector->data[index]);
}
int generic_vector_get_size(GENERIC_VECTOR hVector){
	Generic_vector* pVector = (Generic_vector*)hVector;
	return pVector->size;
}

int generic_vector_get_capacity(GENERIC_VECTOR hVector){
	Generic_vector* pVector = (Generic_vector*)hVector;
	return pVector->capacity;
} 
Boolean generic_vector_empty(GENERIC_VECTOR hVector){
	Generic_vector* pVector = (Generic_vector*)hVector;
	return (Boolean)(pVector->size == 0);
}













