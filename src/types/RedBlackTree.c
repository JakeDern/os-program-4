#include <stdio.h>
#include <stdlib.h>

#include "./RBNode.h"
#include "./RedBlackTree.h"

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