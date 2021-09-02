#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 10
typedef struct tag{
   char word[50];
   struct tag* next;
} node;
void menu(void) {
  printf("\n\n\t\t------------- Menu to USE --------------\n");
  printf("\n\t\t 1. Insert a word to Hash Table\n"); 
  printf("\n\t\t 2. Delete a word from Hash Table\n"); 
  printf("\n\t\t 3. Search a word in hash table\n");
	printf("\n\t\t 4. Compute Load Factor\n");
	printf("\n\t\t 5. QUIT\n");
	printf("\n\t\t---------------------------------------\n");
	printf("\n\t\t Your choice please: ");						
}
int Hash_function(char* word) {
  int p = 31, i, result = 0;
  for(i = 0; word[i] != '\0'; i++) {
    result += word[i]*pow(p, i);
  }
  result %= SIZE;
  return result;
}
int inset_word(node** HT, int* N, char* ToAdd, int location) {
  node* temp = (node*)malloc(sizeof(node));
  strcpy(temp->word, ToAdd);
  temp->next = NULL;
  int count = 1;
  if(*N == SIZE)
    return -1;
  else {
    if(HT[location]->next == NULL)
        HT[location]->next = temp;
    else
    {
      
      temp->next = HT[location]->next;
      HT[location]->next = temp;
        
    }
    (*N)++;
    return count;
  }
} 
int search_word(node** HT, char* word_X, int location) {
  int count = 1;
  node* temp = HT[location]->next;
  while(temp != NULL) {
    if(strcmp(temp->word, word_X) == 0)
      return count;
    temp = temp->next;
    count++;
  }
  return -1;
}
int delete_word(node** HT, int* N, char* word_X, int location) {
  int count, tries;
  node* temp1, *temp2;
  count = search_word(HT, word_X, location);
  if(count == -1)
    return -1;
  else {
      temp1 = HT[location];
      for(tries = 1; tries != count; tries++) {
        temp1 = temp1->next;
      }
      temp2 = temp1->next;
      temp1->next = temp2->next;
      free(temp2);
      (*N)--;
      return count;
  }
}
double compute_load_factor(int N) {
  return ((N * 1.0) / SIZE);
}
void initialize_HT(node** HT) {
  int i;
  for(i = 0; i < SIZE; i++) {
    HT[i] = (node*)malloc(sizeof(node));
    HT[i]->next = NULL;
  } 
}


int main(void) {
  int choice, N = 0, location, status;
  char word_X[50], ToAdd[50];
  node* words[SIZE];
  node* temp = malloc(sizeof(node));
  double load_factor;
  initialize_HT(words);
  do {
    menu();
    scanf("%d", &choice);
    switch(choice) {
      case 1:
        printf("\n\t\tInput a word you wish to insert to your hash table: ");
        scanf("%s", ToAdd);
        location = Hash_function(ToAdd);
        status = inset_word(words, &N, ToAdd, location);
        if(status == -1)
          printf("\n\t\tCould not add %s: HT is full.", ToAdd);
        else
          printf("\n\t\t%s is added at HT[%d] in the spot number %d.\n", ToAdd, location, status);
        break;
      case 2:
        if(N == 0) {
          printf("\n\t\tInsert a word first!\n");
          break;
        }
        printf("\n\t\tEnter the word you wish to delete: ");
        scanf("%s", word_X);
        location = Hash_function(word_X);
        status = delete_word(words, &N, word_X, location);
        if(status == -1)
          printf("\n\t\t%s was not found!\n", word_X);
        else
          printf("\n\t\t%s was deleted from postion %d.\n", word_X, status);
			  break;
      case 3:
        printf("\n\t\tEnter the word you wish to search for: ");
        scanf("%s", word_X);
        location = Hash_function(word_X);
        status = search_word(words, word_X, location);
        if(status == -1)
          printf("\n\t\t%s was not found!\n", word_X);
        else
          printf("\n\t\t%s was found at position %d at index %d.\n", word_X, status, location);
        break;
      case 4: 
        load_factor = compute_load_factor(N);
        printf("\n\t\tLoad Factor is: %.2f\n", load_factor); 
			break;
      case 5:
        printf("\n\t\tGoodbye!\n");
        break;
      default:
        printf("\n\t\tError! Try again.\n");
    }
  } while(choice != 5);
  return 0;
}
