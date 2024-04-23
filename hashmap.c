#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap* map, char* key, void* value)
{
  if(map==NULL || key==NULL || value==NULL) return;
  int pos = hash(key, map->capacity);
  if(map->buckets[pos] == NULL || map->buckets[pos]->key == NULL)
  {
    map->buckets[pos] = createPair(key, value);
    map->current = pos;
  }
  else
  {
    while(map->buckets[pos] != NULL && map->buckets[pos]->key != NULL)
    {
      pos = (pos+1)%map->capacity;
    }
    map->buckets[pos] = createPair(key, value);
    map->current = pos;
  }
  map->size++;
}

void enlarge(HashMap * map) 
{
    enlarge_called = 1; //no borrar (testing purposes)

    Pair** oldArray = map->buckets;
    long oldCapacity = map->capacity;

    map->capacity *= 2;
    map->buckets = (Pair**)malloc(sizeof(Pair*)*map->capacity);
    map->size = 0;

    for(int i = 0; i < oldCapacity; i++)
    {
        if(oldArray[i] != NULL)
        {
            int pos = hash(oldArray[i]->key, map->capacity); 
          
            while(map->buckets[pos] != NULL || map->buckets[pos]->key != NULL)
            {
                pos = (pos + 1) % map->capacity;
            }

            map->buckets[pos] = createPair(oldArray[i]->key, oldArray[i]->value);
            map->size++;
        }
    }

    for(int k = 0; k < oldCapacity; k++)
    {
        free(oldArray[k]);
    }
    free(oldArray);
}

/*void enlarge(HashMap * map) 
{
  enlarge_called = 1; //no borrar (testing purposes)
  
  Pair** oldArray = map->buckets;
  long oldCapacity = map->capacity;
  
  map->capacity *= 2;
  map->buckets = (Pair**)malloc(sizeof(Pair*)*map->capacity);
  map->size = 0;
  
  for(int i = 0; i < oldCapacity; i++)
    {
      if(oldArray[i] != NULL)
      {
        int pos = hash(oldArray[i]->key, map->capacity);
        insertMap(map, oldArray[pos]->key, oldArray[pos]->value);
      }
    }
  for(int k = 0; k < oldCapacity; k++)
    {
      free(oldArray[k]);
    }
  free(oldArray);
}*/


HashMap * createMap(long capacity) 
{
  HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  map->buckets = (Pair **)calloc(capacity,sizeof(Pair*));
  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  
  return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) 
{   
  return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
