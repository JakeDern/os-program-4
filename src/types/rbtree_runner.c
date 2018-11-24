#include <stdio.h>
#include <stdlib.h>

#include "./RedBlackTree.h"

int intCompare(void *int1, void *int2);

int main() {
    RedBlackTree *tree = newRedBlackTree((cmpFunc) &intCompare);
    printf("Construct\n");
}

int intCompare(void *int1, void *int2) {
    return *((int *) int1) - *((int *) int2); 
}