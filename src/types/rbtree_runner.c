#include <stdio.h>
#include <stdlib.h>

#include "./RedBlackMap.h"

int intCompare(void *int1, void *int2);

typedef int Integer;

int main() {
    RedBlackMap *tree = newRedBlackMap((cmpFunc) &intCompare);
    int *key = malloc(sizeof(int));
    int *key2 = malloc(sizeof(int));
    int *key3 = malloc(sizeof(int));
    int *key4 = malloc(sizeof(int));
    int *key5 = malloc(sizeof(int));
    
    *key = 5;
    *key2 = 10;
    *key3 = 1;
    *key4 = 4;
    *key5 = 7;
    
    int *val = malloc(sizeof(int));
    *val = 10;

    RBMPut(tree, (void*) key, (void*) val);
    RBMPut(tree, (void*) key2, (void*) val);
    RBMPut(tree, (void*) key3, (void*) val);
    RBMPut(tree, (void*) key4, (void*) val);
    RBMPut(tree, (void*) key5, (void*) val);
}

int intCompare(void *int1, void *int2) {
    return *((int *) int1) - *((int *) int2); 
}

void RBMPrint(RedBlackMap *map) {
  
}
