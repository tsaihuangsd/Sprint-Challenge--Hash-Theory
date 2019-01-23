#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
  // //create a new hash table and fill the key-value pairs of the hash table with each set of weight and index of weight in weights array
  // HashTable *ht = create_hash_table(16);
  // int difference;
  // printf("Insert: \n");
  // for (int i=0; i<length; i++){
  //   // hash_table_insert(ht, weights[i], i);
  //   difference = limit - weights[i];
  //   hash_table_insert(ht, difference, i);
  // }
  // printf("\n");
  // //loop through the hash array.  check if each element of the hash array is pointing to a LinkedPair; if it does, print out the key-value set of the each element of the LinkedPair.
  // printf("Retrieve: \n");
  // for (int j=0; j<ht->capacity; j++){
  //   printf("hash_index: %d", j);
  //   if (ht->storage[j]){
  //     printf(", not null\n");
  //     LinkedPair *current_pair = ht->storage[j];
  //     LinkedPair *last_pair;
  //     int k=1;
  //     while (current_pair != NULL) {
  //       printf("Pair #: %d, key: %d, value: %d\n", k, current_pair->key, current_pair->value);
  //       last_pair = current_pair;
  //       current_pair = last_pair->next;
  //       k++;
  //     }
  //     // printf("key: %d, value: %d\n", ht->storage[j]->key, ht->storage[j]->value);
  //     //  printf("\n");
  //   }
  //   // else{
  //     printf("\n");
  //   // }
  
  //   // printf("Weight: %d, wt_index: %d\n", weights[j], hash_table_retrieve(ht, weights[j]));
  // }
  // return NULL;






  //build the hash table with each key equals the difference between limit and current weight in the weights array, and each value equals the weights index of the current weight
  HashTable *ht = create_hash_table(16);
  int difference;
  for (int i=0; i<length; i++){
    difference = limit - weights[i];
    // printf("Difference: %d\n", difference);
    // printf("current weight: %d, difference: %d, index: %d\n", weights[i], difference, i);
    int matching_index = hash_table_retrieve(ht, weights[i]);
    // printf("Matching index: %d\n", matching_index);
    if (matching_index == -1){
      hash_table_insert(ht, difference, i);
      // printf("write: wt-index: %d, ", i); 
      // for (int j=0; j<ht->capacity; j++){
      //   if (ht->storage[j]){
      //     printf("hash_index: %d, key: %d, value: %d\n", j, ht->storage[j]->key, ht->storage[j]->value);
      //   }
      // }
    }
    else{
      Answer *new_answer = malloc(sizeof(Answer*));
      int matching_index = hash_table_retrieve(ht, weights[i]);
      // printf("MATCH!!!: current weight: %d, difference: %d\n", weights[i], difference);

      if (matching_index > i ){
        new_answer->index_1 = hash_table_retrieve(ht, weights[i]);
        new_answer->index_2 = i;
      }
      else{
        new_answer->index_1 = i;
        new_answer->index_2 = hash_table_retrieve(ht, weights[i]);
      }
      return new_answer;
    }

    // printf("-------------------------\nPrint entire hash table: \n");
    // for (int j=0; j<ht->capacity; j++){
    //   printf("hash_index: %d, ", j);
    //   if (ht->storage[j]){
    //     printf("not null\n");
    //     LinkedPair *current_pair = ht->storage[j];
    //     LinkedPair *last_pair;
    //     int k=1;
    //     while (current_pair != NULL) {
    //       printf("Pair #: %d, key: %d, value: %d\n", k, current_pair->key, current_pair->value);
    //       last_pair = current_pair;
    //       current_pair = last_pair->next;
    //       k++;
    //     }
    //     // printf("key: %d, value: %d\n", ht->storage[j]->key, ht->storage[j]->value);
    //     //  printf("\n");
    //   }
    // }
    // printf("\n\n");
  }
  return NULL;
}

void print_answer(Answer *answer)
{
  if (answer != NULL) {
    printf("%d %d\n", answer->index_1, answer->index_2);
  } else {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{

  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1);  // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer* answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2);  // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer* answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3);  // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer* answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4);  // {6, 2}

  return 0;
}
#endif
