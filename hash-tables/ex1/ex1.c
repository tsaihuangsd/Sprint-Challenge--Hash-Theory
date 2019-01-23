#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
  HashTable *ht = create_hash_table(17);
  int difference;
  for (int i=0; i<length; i++){
    difference = limit - weights[i];
    hash_table_insert(ht, difference, i);
  }

  for (int j=0; j<length; j++){
    printf("hash_index: %d", j);
    if (ht->storage[j]){
      printf("not null\n");
      LinkedPair *current_pair = ht->storage[j];
      LinkedPair *last_pair;
      int k=1;
      while (current_pair != NULL) {
        printf("Pair #: %d, key: %d, value: %d", k, current_pair->key, current_pair->value);
        last_pair = current_pair;
        current_pair = last_pair->next;
      }
      // printf("key: %d, value: %d\n", ht->storage[j]->key, ht->storage[j]->value);
       printf("\n");
    }
    // else{
      printf("\n");
    // }
  
    // printf("Weight: %d, wt_index: %d\n", weights[j], hash_table_retrieve(ht, weights[j]));
  }
  return NULL;






  // //build the hash table with each key equals the difference between limit and current weight in the weights array, and each value equals the weights index of the current weight
  // HashTable *ht = create_hash_table(16);
  // int difference;
  // for (int i=0; i<length; i++){
  //   difference = limit - weights[i];
  //   printf("Difference: %d\n", difference);
  //   // printf("current weight: %d, difference: %d, index: %d\n", weights[i], difference, i);
  //   int matching_index = hash_table_retrieve(ht, difference);
  //   // printf("Matching index: %d\n", matching_index);
  //   if (matching_index == -1){
  //     hash_table_insert(ht, difference, i);
  //     printf("write: difference: %d, index: %d\n", difference, i); 
  //     for (int j=0; j<length; j++){
  //       if (ht->storage[j]){
  //         printf("Index: %d, key: %d, value: %d\n", j, ht->storage[j]->key, ht->storage[j]->value);
  //       }
  //     }
  //   }
  //   else{
  //     Answer *new_answer = malloc(sizeof(Answer*));
  //     int matching_index = hash_table_retrieve(ht, weights[i]);
  //     printf("match: current weight: %d, difference: %d\n", weights[i], difference);

  //     if (matching_index > i ){
  //       new_answer->index_1 = hash_table_retrieve(ht, weights[i]);
  //       new_answer->index_2 = i;
  //     }
  //     else{
  //       new_answer->index_1 = i;
  //       new_answer->index_2 = hash_table_retrieve(ht, weights[i]);
  //     }
  //     return new_answer;
  //   }
  // }
  // return NULL;
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

  // // TEST 1
  // int weights_1 = {9};
  // Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  // print_answer(answer_1);  // NULL

  // // TEST 2
  // int weights_2[] = {4, 4};
  // Answer* answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  // print_answer(answer_2);  // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer* answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3);  // {3, 1}

  // // TEST 4
  // int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  // Answer* answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  // print_answer(answer_4);  // {6, 2}

  return 0;
}
#endif
