#ifndef INT_VECTOR
#define INT_VECTOR

#include"my_string.h"


typedef void* GENERIC_VECTOR;




GENERIC_VECTOR generic_vector_init_default();

//push_back
Status generic_vector_push_back(GENERIC_VECTOR hVector, MY_STRING item);

//Accessor functions
int generic_vector_get_size(GENERIC_VECTOR hVector);
int generic_vector_get_capacity(GENERIC_VECTOR hVector);

//clear
//set size to zero so that the vector appears to be empty

//
Boolean generic_vector_empty(GENERIC_VECTOR hVector);

//remove
Status generic_vector_pop_back(GENERIC_VECTOR hVector);

//look at items in the vector
MY_STRING* generic_vector_at(GENERIC_VECTOR hVector, unsigned int index);

void generic_vector_assignment(GENERIC_VECTOR* leftVector, GENERIC_VECTOR rightVector);

void generic_vector_destroy(GENERIC_VECTOR* phVector);



#endif
