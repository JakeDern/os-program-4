#include <stdio.h>
#include <stdlib.h>

#include "./RedBlackMap.h"

int intCompare(void *int1, void *int2);

typedef int Integer;

int main() {
    RedBlackMap *tree = newRedBlackMap((cmpFunc) &intCompare);
    printf("Construct\n");
    size_t s;
    int *i = malloc(sizeof(int));
    *i = 5;
    printf("Int is %d\n", *i);
    free(i);
}

int intCompare(void *int1, void *int2) {
    return *((int *) int1) - *((int *) int2); 
}
