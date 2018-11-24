#include <stdio.h>
#include <stdlib.h>

#include "./RedBlackTree.h"

int testCompare(void *data1, void* data2);

int main() {
  printf("main\n");
}

/** @override */
RedBlackTree* newRedBlackTree(cmpFunc compare) {
    RedBlackTree *tree;
    if ( (tree = malloc(sizeof(RedBlackTree))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for RedBlackTree\n");
        exit(1);
    }

    tree->size = 0;
    tree->root = NULL;
    tree->compare = compare;

    return tree;
}

/** @override */
void RBInsert(RedBlackTree *tree, void *data) {
    printf("insert\n");
}

/** @override */
void RBDelete(RedBlackTree *tree, void *data) {

}

/** @override */
void* RBSearch(RedBlackTree *tree, void *data) {
  return NULL;
}

/** @override */
void RBDestroy(RedBlackTree *tree) {

}

void RBDestroyAndFree(RedBlackTree *tree, destruct destructor) {

}

int testCompare(void *data1, void* data2) {
    printf("testCompare\n");
    return *((int*) data1) - *((int*) data2);
}