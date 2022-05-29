#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"my_string.h"
#include"generic_vector.h"
#include"tree.h"

#define MAX 100

void clear_buffer();

int main(){
  int i, size, wordLen, guesses;
  int j = 0;
  int winloss;
  int largest = 0;
  char opt, temp, play;
  char* charGuess;
  GENERIC_VECTOR hVector[30];
  GENERIC_VECTOR hVectorCurr = NULL;
  MY_STRING hString = NULL;
  MY_STRING display = NULL;
  MY_STRING new_key = NULL;
  MY_STRING largestKey = NULL;
  tNode* root = NULL;

  do{

    FILE* fp = fopen("dictionary.txt", "r");
    hString = my_string_init_default();
    
    for(i = 0; i < 30; i++){
      hVector[i] = NULL;
    }
    
    for(i = 0 ; i < 30; i++){
      hVector[i] = generic_vector_init_default();
    }
    
    while(!feof(fp)){
      my_string_extraction(hString, fp);
      size = my_string_get_size(hString);
      generic_vector_push_back(hVector[size], hString);    
    }
     

    my_string_destroy(&hString);
    
    printf("Enter a word length: ");
    scanf("%d", &wordLen);
    clear_buffer();
    while(wordLen > 29 || wordLen < 1 || generic_vector_get_size(hVector[wordLen]) == 0){
      printf("Invalid number\nEnter a word length: ");
      scanf("%d", &wordLen);
      clear_buffer();
    }
    
    hVectorCurr = generic_vector_init_default();
    generic_vector_assignment(&hVectorCurr, hVector[wordLen]);
    
    
    for(i = 0; i < 30; i++){
      generic_vector_destroy(&hVector[i]);
    }

    fclose(fp);
    
    display = my_string_init_default();
    
    for(i = 0; i < wordLen; i++){
      my_string_push_back(display, '-');
    }
    
    printf("Enter how many guesses you would like to make: ");
    scanf("%d", &guesses);
    clear_buffer();
    while(guesses <= 0){
      printf("Invalid number\nEnter how many guesses you would like to make: ");
      scanf("%d", &guesses);
      clear_buffer();
    }
    
    printf("Do you want to know the remaining total number of words of that length? [y/n] ");
    scanf("%c", &opt);
    clear_buffer();
    
    while(opt != 'y' && opt != 'Y' && opt != 'n' && opt != 'N'){
      printf("Invalid choice\nDo you want to know the remaining total number of words of that length? [y/n] ");
      scanf("%c", &opt);
      clear_buffer();
    }

    if(opt == 'y' || opt == 'Y'){
      printf("Number of words of word length %d is %d\n", wordLen, generic_vector_get_size(hVectorCurr));
    }

    charGuess = (char*) malloc(sizeof(char) * MAX);
    
    while(guesses > 0){
      printf("You have %d guesses left\n", guesses);
      printf("Used letters: ");

      for(i = 0; i < j; i++){
	printf("%c ", charGuess[i]);
      }
      
      printf("\n");
      printf("Word: ");
      my_string_insertion(display, stdout);
      printf("\nEnter guess: ");
      scanf("%c", &temp);
      clear_buffer();

      while(temp){
	if(isalpha(temp) == 0){
	  printf("Invalid choice. Enter guess: ");
	  scanf("%c", &temp);
	  clear_buffer();
	  continue;
	}
	for(i = 0; i < j; i++){
	  if(temp == charGuess[i]){
	    break;
	  }
	}
	if(temp == charGuess[i]){
	  printf("Invalid choice. Enter guess: ");
	  scanf("%c", &temp);
	  clear_buffer();
	}
	else{
	  break;
	}
      }
      
      /* for(i = 0; i < j; i++){
	while(temp == charGuess[i]){
	  printf("Invalid choice. Enter guess: ");
	  scanf("%c", &temp);
	  clear_buffer();
	}
      }
      
      while(isalpha(temp) == 0){
	printf("Invalid choice. Enter guess: ");
	scanf("%c", &temp);
	clear_buffer();
	}*/
      
      charGuess[j] = tolower(temp);
      
      for(i = 0; i < generic_vector_get_size(hVectorCurr); i++){
	new_key = my_string_init_default();
	get_word_key_value(display, new_key, *(generic_vector_at(hVectorCurr, i)), charGuess[j]);
	root = insertNodes(root, new_key);
	my_string_destroy(&new_key);
      }
      
      for(i = 0; i < generic_vector_get_size(hVectorCurr); i++){
	new_key = my_string_init_default();
	get_word_key_value(display, new_key, *(generic_vector_at(hVectorCurr, i)), charGuess[j]);
	preorderTraversal(root, new_key, *(generic_vector_at(hVectorCurr, i)));
	my_string_destroy(&new_key);
      }
      
      largestKey = my_string_init_default();
      inorderTraversal(root, &largest);
      traverse(root, largest, hVectorCurr, largestKey);
      
      if(my_string_compare(display, largestKey) == 0){
	printf("There is no %c in the word\n", charGuess[j]);
	guesses--;
      }
      else{
	printf("There is a %c in the word\n", charGuess[j]);
	my_string_assignment(&display, largestKey);
      }

      my_string_destroy(&largestKey);
      treeDestroy(root);
      root = NULL;
      largest = 0;

      j++;
    
      for(i = 0; i < wordLen; i++){
	if(*(my_string_at(display, i)) != '-'){
	  winloss++;
	}
      }
      if(winloss == wordLen){
	printf("Congratulations! You Won! The word is ");
	my_string_insertion(*(generic_vector_at(hVectorCurr, 0)), stdout);
	break;
      }
      winloss = 0;

      if(j == 27){
	printf("You have used up the alphabet! You lost! The word was ");
	my_string_insertion(*(generic_vector_at(hVectorCurr, 0)), stdout);
	break;
      }
    }
    
    if(guesses == 0 && winloss != wordLen){
      printf("You lost! The word was ");
      my_string_insertion(*(generic_vector_at(hVectorCurr, 0)), stdout);
    }

    my_string_destroy(&display);
    generic_vector_destroy(&hVectorCurr);
    j = 0;
    free(charGuess);
    
    printf("\nDo you want to play again? [y/n]");
    scanf("%c", &play);
    clear_buffer();
    
    while(play != 'y' && play != 'Y' && play != 'n' && play != 'N'){
      printf("Invalid choice\nDo you want to play again? [y/n] ");
      scanf("%c", &play);
      clear_buffer();
    }
    
  }while(play == 'y' || play == 'Y');
  
  return 0;
}

void clear_buffer(){
  char ch;
  scanf("%c", &ch);
  while(ch != '\n'){
    scanf("%c", &ch);
  }
  return;
}
