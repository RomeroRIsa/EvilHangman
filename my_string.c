#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "my_string.h"

typedef struct string1{
  int size;
  int capacity;
  char* data;
}STRING1;


MY_STRING my_string_init_default(void){
  STRING1* mystring = (STRING1*) malloc(sizeof(STRING1));

  if(mystring == NULL){
    return NULL;
  }

  mystring->size = 0;
  mystring->capacity = 31;
  mystring->data = (char*)malloc(sizeof(char)*mystring->capacity);

  return (MY_STRING)mystring;

}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp){
  STRING1* string = (STRING1*) hMy_string;
  int check, len = 0;
  char temp[40];
  //char c;

  /*while((c = fgetc(fp))){
    if(c == ' ' || c == '\n'){
      break;
    }
    string->data[string->size] = c;
    string->size += 1;
    if(string->size >= string->capacity){
      string->data = (char*)realloc(string->data, sizeof(char)*string->capacity*2);
      if(string->data == NULL){
	return FAILURE;
      }
    string->capacity = string->capacity * 2;
    }
  }
  ungetc(c, fp)
    temp = fgetc(fp);

  if(feof(fp)){
    return FAILURE;
  }
  else{
    return SUCCESS;
    }*/
  
  check = fscanf(fp, "%s", temp);
  while(temp[len] != '\0' ){
    len++;
  }

  string->size = len;
  
  if(string->size >= string->capacity){
    string->data = (char*)realloc(string->data, sizeof(char)*string->capacity*2);
    if(string->data == NULL){
      return FAILURE;
    }
    string->capacity = string->capacity * 2;
  }

  strcpy(string->data, temp);

  if(string->data == NULL){
    return FAILURE;
  }
  
  if(check == EOF){
    return FAILURE;
  }
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp){
  STRING1* string = (STRING1*) hMy_string;
  fprintf(fp, "%s", string->data);
  if(fp == NULL){
    return FAILURE;
  }
  else{
    return SUCCESS;
  }
}
int my_string_get_capacity(MY_STRING hMy_string){
  STRING1* mystring = (STRING1*)hMy_string;
  return mystring->capacity;
}

int my_string_get_size(MY_STRING hMy_string){
  STRING1* mystring = (STRING1*)hMy_string;
  return mystring->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string){
  STRING1* str1 = (STRING1*)hLeft_string;
  STRING1* str2 = (STRING1*)hRight_string;
  int i = strcmp(str1->data, str2->data);

  return i;
}

MY_STRING my_string_init_c_string(const char* c_string){
  STRING1* mystring = (STRING1*) malloc(sizeof(STRING1));
  int len = 0;
  
  while(c_string[len] != '\0'){
    len++;
  }
  
  mystring->size = len;
  mystring->capacity = len + 1;
  
  mystring->data = (char*)malloc(sizeof(char)*mystring->capacity);
  
  
  if(mystring->data == NULL){
    return NULL;
  }

  strcpy(mystring->data, c_string);
  
  return (MY_STRING)mystring;

}

void my_string_destroy(Item* phMy_string){
  STRING1* str = (STRING1*)*phMy_string;
  free(str->data);
  free(str);
  str = NULL;
  return;
}

Status my_string_push_back(MY_STRING hMy_string, char item){
  STRING1* mystring = (STRING1*) hMy_string;
  
  if (mystring->data == NULL){
    return FAILURE;
  }

  if(mystring->size + 1 >= mystring->capacity){
    mystring->capacity = mystring->capacity * 2;
    mystring->data = (char*)realloc(mystring->data, sizeof(char)*mystring->capacity);
    if(mystring->data == NULL){
      return FAILURE;
    }
  }

  mystring->data[mystring->size] = item;
  mystring->data[mystring->size + 1] = '\0';
  mystring->size++;
  
 
    
  return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string){
  STRING1* mystring = (STRING1*) hMy_string;
  if(mystring->data == NULL){
    return FAILURE;
  }

  mystring->size = mystring->size - 1;
  mystring->data[mystring->size] = '\0';



  return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index){
  STRING1* mystring = (STRING1*) hMy_string;
  if(mystring->data == NULL){
    return NULL;
  }
  if(index >= mystring->size){
    return NULL;
  }
  return &mystring->data[index];
}

char* my_string_c_str(MY_STRING hMy_string){
  STRING1* mystring = (STRING1*) hMy_string;
  if(mystring->data == NULL){
    return NULL;
  }
  if(mystring->capacity <= mystring->size){
    mystring->capacity += 1;
    mystring->data = (char*)realloc(mystring->data, sizeof(char)*mystring->capacity);
    if(mystring->data == NULL){
      return NULL;
    }
  }

  mystring->data[mystring->size] = '\0';
  
  return &mystring->data[0];
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend){
  STRING1* mystring1 = (STRING1*) hResult;
  STRING1* mystring2 = (STRING1*) hAppend;
  if((mystring1->data == NULL) || (mystring2->data == NULL)){
    return FAILURE;
  }
  mystring1->size += mystring2->size;
  mystring1->capacity += mystring2->capacity;
  mystring1->data = (char*)realloc(mystring1->data, sizeof(char)*mystring1->capacity);
  if(mystring1->data == NULL){
    return FAILURE;
  }

  strcat(mystring1->data, mystring2->data);
  
  return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string){
  STRING1* mystring = (STRING1*) hMy_string;
  if(mystring->data[0] == '\0'){
    return TRUE;
  }

  return FALSE;
}

void my_string_assignment(Item* pLeft, Item Right){
  STRING1* mystring1 = (STRING1*) *pLeft;
  STRING1* mystring2 = (STRING1*) Right;
  // int i;

  if(mystring1 == NULL){
    *pLeft = my_string_init_c_string(mystring2->data);
  }
  else{
    if(mystring2->size >= mystring1->capacity){
      mystring1->data = (char*)realloc(mystring1->data, sizeof(char)*mystring2->capacity);
      if(mystring1->data != NULL){
	mystring1->capacity = mystring2->capacity;
      }
    }
    
    mystring1->size = mystring2->size;
    strcpy(mystring1->data, mystring2->data);
  }
    
  
  return;
}

void my_string_print(MY_STRING hString){
  STRING1* mystring = (STRING1*) hString;
  int i;
  for(i = 0; i < mystring->size; i++){
    printf("%c", mystring->data[i]); 
  }
  return;
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess){
  int i;
  STRING1* testWord = (STRING1*) word;
  for(i = 0; i < testWord->size; i++){
    if(*(my_string_at(word, i)) == guess || *(my_string_at(word, i)) == (guess - 32)){
      if(guess >= 65 && guess <= 90){
	my_string_push_back(new_key, guess+32);
      }
      else{
	my_string_push_back(new_key, guess);
      }
    }
    else{
      my_string_push_back(new_key, *(my_string_at(current_word_family, i)));
    }
  }
  return SUCCESS;
}
