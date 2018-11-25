#include <stdio.h>
#include <stdlib.h>

#include "./RedBlackMap.h"

int intCompare(void *int1, void *int2);

typedef int Integer;

int main() {
    RedBlackMap *tree = newRedBlackMap((cmpFunc) &intCompare);
    int *key = malloc(sizeof(int));
    *key = 5;
    int *val = malloc(sizeof(int));
    *val = 10;
    RBMPut(tree, (void*) key, (void*) val);
}

int intCompare(void *int1, void *int2) {
    return *((int *) int1) - *((int *) int2); 
}

void RBMPrint(RedBlackMap *map) {
  
}
