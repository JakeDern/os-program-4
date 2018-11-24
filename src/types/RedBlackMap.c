#include <stdio.h>
#include <stdlib.h>

#include "./RBMNode.h"
#include "./RedBlackMap.h"

/** @override */
RedBlackMap* newRedBlackMap(cmpFunc compare) {
    RedBlackMap *map;
    if ( (map = malloc(sizeof(RedBlackMap))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for RedBlackMap\n");
        exit(1);
    }

    map->size = 0;
    map->root = NULL;
    map->cmpKey = compare;

    return map;
}

/** @override */
void RBMPut(RedBlackMap *map, void *key, void *val) {
    printf("insert\n");
}

/** @override */
KVPair* RBMDelete(RedBlackMap *map, void *key) {

}

/** @override */
void* RBMSearch(RedBlackMap *map, void *key) {
  return NULL;
}

void* RBMReplace(RedBlackMap *map, void *key, void *val) {

}

/** @override */
void RBMDestroy(RedBlackMap *map) {

}

/** @override */
void RBDestroyAndFree(RedBlackMap *map, destructVal dVal) {

}