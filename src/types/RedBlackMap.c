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
    map->dKey = NULL;

    return map;
}

void RBMDestructKey(RedBlackMap *map, destructKey dKey) {
    map->dKey = dKey;
}

/** @override */
void RBMPut(RedBlackMap *map, void *data) {
    printf("insert\n");
}

/** @override */
void RBMDelete(RedBlackMap *map, void *data) {

}

/** @override */
void* RBMSearch(RedBlackMap *map, void *key) {
  return NULL;
}

void RBMReplace(RedBlackMap *map, void *key, void *val) {

}

/** @override */
void RBMDestroy(RedBlackMap *map) {

}

/** @override */
void RBDestroyAndFree(RedBlackMap *map, destructVal dVal) {

}