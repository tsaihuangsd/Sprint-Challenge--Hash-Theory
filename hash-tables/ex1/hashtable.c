#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

LinkedPair *create_pair(int key, int value)
{
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  pair->key = key;
  pair->value = value;
  pair->next = NULL;

  return pair;
}

// djb2 hash function
unsigned int hash(unsigned int x, int max) {
  // unsigned long hash = 5381;
  // hash = x*hash;

  // x= x*5381;

  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  return x % max;
}

void destroy_pair(LinkedPair *pair)
{
  if (pair != NULL) free(pair);
}

HashTable *create_hash_table(int capacity)
{
  HashTable *ht = malloc(sizeof(HashTable));
  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(LinkedPair *));

  return ht;
}

void hash_table_insert(HashTable *ht, int key, int value)
{
  unsigned int index = hash(key, ht->capacity);

  LinkedPair *current_pair = ht->storage[index];
  LinkedPair *last_pair;

  while (current_pair != NULL && current_pair->key != key) {
    // printf("current key: %d, value: %d\n", current_pair->key, current_pair->value);
    last_pair = current_pair;
    current_pair = last_pair->next;
  }


  // if a LinkedPair is found with the key of interest, overwrite the value of the LinkedPair with the value of interest
  if (current_pair != NULL) {
    // printf("here\n");
    current_pair->value = value;  //overwrites the value corresponding to the existing matching key with new value
  } 
  else {
    LinkedPair *new_pair = create_pair(key, value);
    new_pair->next = ht->storage[index];
    ht->storage[index] = new_pair;
    // printf("hash_index: %d, key: %d, value: %d\n", index, ht->storage[index]->key, ht->storage[index]->value);
  }
  
}

void hash_table_remove(HashTable *ht, int key)
{
  unsigned int index = hash(key, ht->capacity);

  LinkedPair *current_pair = ht->storage[index];
  LinkedPair *previous_pair = NULL;

  while (current_pair != NULL && current_pair->key != key) {
    previous_pair = current_pair;
    current_pair = current_pair->next;
  }

  if (current_pair == NULL) {
    fprintf(stderr, "Unable to remove entry with key: %d\n", key);
  } else {
    if (previous_pair == NULL) {  // Removing the first element in the Linked List
      ht->storage[index] = current_pair->next;
    } else {
      previous_pair->next = current_pair->next;
    }

    destroy_pair(current_pair);
  }
}

int hash_table_retrieve(HashTable *ht, int key)
{
  unsigned int index = hash(key, ht->capacity);
  // printf("Hash_index: %d\n", index);

  LinkedPair *current_pair = ht->storage[index];

  while (current_pair != NULL) {
    // printf("Checking current pair - key: %d, difference: %d", current_pair->key, key);
    if (current_pair->key == key) {
      return current_pair->value;
    }

    current_pair = current_pair->next;
  }

  return -1;
}

void destroy_hash_table(HashTable *ht)
{
  LinkedPair *current_pair;
  LinkedPair *pair_to_destroy;

  for (int i = 0 ; i < ht->capacity; i++) {
    current_pair = ht->storage[i];
    while (current_pair != NULL) {
      pair_to_destroy = current_pair;
      current_pair = current_pair->next;
      destroy_pair(pair_to_destroy);
    }
  }

  free(ht->storage);
  free(ht);
}

HashTable *hash_table_resize(HashTable *ht)
{
  HashTable *new_ht = create_hash_table(2 * ht->capacity);

  LinkedPair *current_pair;
  for (int i = 0 ; i < ht->capacity ; i++) {
    current_pair = ht->storage[i];
    while (current_pair != NULL) {
      hash_table_insert(new_ht, current_pair->key, current_pair->value);
      current_pair = current_pair->next;
    }
  }

  destroy_hash_table(ht);
  return new_ht;
}