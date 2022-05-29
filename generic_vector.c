#include <stdlib.h>
#include "generic_vector.h"
#include "my_string.h"

//The KNOWN TYPE
struct vector
{
  int size;
  int capacity;
  MY_STRING* data;
};
typedef struct vector Vector;

GENERIC_VECTOR generic_vector_init_default()
{
	int i;
	Vector* pVector = (Vector*) malloc(sizeof(Vector));
	
		//worked
	pVector->size = 0;
	pVector->capacity = 1;
	pVector->data = (MY_STRING*)malloc(sizeof(MY_STRING) * pVector->capacity);
	if (pVector->data == NULL)
	  {
	    free(pVector);
	    return NULL;
	  }
	for (i = 0; i < pVector->capacity; i++)
	  {
	    pVector->data[i] = my_string_init_default();
	  }
	
	return (GENERIC_VECTOR)pVector;
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, MY_STRING item) 
{
	Vector* pVector = (Vector*) hVector;
	//MY_STRING* temp;
	int i;
	
	
	if (pVector->size >= pVector->capacity) //no room
	{
	  pVector->data = (MY_STRING*) realloc(pVector->data, sizeof(MY_STRING) * pVector->capacity * 2);
	  if(pVector->data == NULL){
	    return FAILURE;
	  }
	  for(i = pVector->size; i < pVector->capacity * 2; i++){
	    pVector->data[i] = my_string_init_default();
	  }
	  /*temp = (MY_STRING*) malloc(sizeof(MY_STRING)* pVector->capacity * 2);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pVector->size; i++)
		{
			temp[i] = pVector->data[i];
			}*/  //BUG IS HERE.  We have copied all the old data but what is in the 
		   //rest of the array?  We expect it to be filled with NULL values but
		   //they are uninitialized instead.
		/*for (i; i < pVector->capacity * 2; i++)
		{
			temp[i] = NULL;
			}*/
	  //free(pVector->data);
	  //pVector->data = temp;
	  pVector->capacity *= 2;
	}
	
	my_string_assignment(&pVector->data[pVector->size], item);
	
	pVector->size += 1;

	
	return SUCCESS;
}

int generic_vector_get_size(GENERIC_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->size;
}
int generic_vector_get_capacity(GENERIC_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->capacity;
}

Boolean generic_vector_empty(GENERIC_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;

	return (Boolean) (pVector->size == 0);
}

MY_STRING* generic_vector_at(GENERIC_VECTOR hVector, unsigned int index)
{
	Vector* pVector = (Vector*)hVector;

	if (index >= pVector->size) //out of bounds!
	{
		//printf("vector subscript out of range.\n");
		return NULL;
	}

	//my_string_insertion(pVector->data[index], stdout);
	
	return &(pVector->data[index]);
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;

	if (pVector->size == 0)
	{
		return FAILURE;
	}
	free(pVector->data[pVector->size-1]);
	pVector->size--;
	return SUCCESS;
}

void generic_vector_destroy(GENERIC_VECTOR* phVector)
{
	Vector* pVector = (Vector*) *phVector;
	int i;
	for(i = 0; i < pVector->size; i++){
	  my_string_destroy(&pVector->data[i]);
	}
	free(pVector->data);
	free(pVector);
	*phVector = NULL;
	return;
}

void generic_vector_assignment(GENERIC_VECTOR* leftVector, GENERIC_VECTOR rightVector){
  Vector* pVector1 = (Vector*)*leftVector;
  Vector* pVector2 = (Vector*)rightVector;
  int i;
  
  pVector1->size = pVector2->size;
  pVector1->capacity = pVector2->capacity;
  pVector1->data = (MY_STRING*) realloc(pVector1->data, sizeof(MY_STRING) * pVector2->capacity);
  for(i = 0; i < pVector1->size; i++){
    if(pVector1->data[i] == NULL){
      pVector1->data[i] = my_string_init_default();
    }
  }
  for(i = 0; i < pVector1->size; i++){
    my_string_assignment(&pVector1->data[i], pVector2->data[i]);
  }
 
  
  return;
}
