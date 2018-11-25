#include <stdio.h>
#include <stdlib.h>

#include "./RBMNode.h"
#include "./RedBlackMap.h"

static void leftRotate(RBMNode *n);
static void rightRotate(RBMNode *n);
static int colorOfUncle(RBMNode *n);
static int colorOfGp(RBMNode *n);
static void fixTree(RBMNode *n);

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
    // First item in tree
    if (map->root == NULL) {
        map->root = newRBMNode(key, val);
        map->root->color = BLACK;
        map->size = 1;
        return;
    }

    // find insertion point for new node
    RBMNode *prev = NULL;
    RBMNode *curr = map->root;
    cmpFunc compare = map->cmpKey;
    int comparison;
    while (curr != NULL) {
        comparison = (*compare)(key, curr->kv->key);
        prev = curr;
        if (comparison == 0) {
            // TODO: Throw duplicate key exception?
            return;
        } else if (comparison < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    // insert node and link into tree
    RBMNode *newNode = newRBMNode(key, val);
    newNode->parent = prev;
    map->size++;
    if (comparison < 0) {
        prev->left = newNode;
    } else {
        prev->right = newNode;
    }

    // initiate fixing;
    fixTree(newNode);
}

static void fixTree(RBMNode *n) {

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
void RBMDestroyAndFree(RedBlackMap *map, destructKey dKey, destructVal dVal) {

}
