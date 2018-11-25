#include <stdio.h>
#include <stdlib.h>

#include "./RBMNode.h"
#include "./RedBlackMap.h"

static void fixTree(RBMNode *n);
static RBMNode* uncleOf(RBMNode *n);
static RBMNode* gpOf(RBMNode *n);
static enum COLOR colorOf(RBMNode *n);

/** @override */
RedBlackMap* newRedBlackMap(cmpFunc compare) {
    RedBlackMap *map;
    if ( (map = malloc(sizeof(RedBlackMap))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for RedBlackMap\n");
        exit(1);
    }

    map->size   = 0;
    map->root   = NULL;
    map->cmpKey = compare;

    return map;
}

/** @override */
void RBMPut(RedBlackMap *map, void *key, void *val) {
    // Edge: this is first insertion
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

    // increment size and link new node into tree
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
    // Fixing is complete to the root
    if (n == NULL) {
        return;
    }

    // nothing to fix
    if (colorOf(n->parent) == BLACK) {
        return;
    }

    /** CASE 1: Red uncle recolor */
    RBMNode *uncle = uncleOf(n);
    if (colorOf(uncle) == RED) {
        // recolor parent and uncle
        n->parent->color = BLACK;
        uncle->color = BLACK;
        
        // recolor grandparent if not root
        RBMNode *gp = gpOf(n);
        if (gp->parent != NULL) {
            gp->color = RED;
        }

        // recursively fix grandparent and return
        fixTree(gp);
        return;
    }
}

/**
 * @returns n->color iff n is not NULL, BLACK otherwise
 **/
static enum COLOR colorOf(RBMNode *n) {
    if (n == NULL) {
        return BLACK;
    } else {
        return n->color;
    }
}

/**
 * @returns uncle of this node or NULL iff the
 * uncle does not exist
 **/
static RBMNode* uncleOf(RBMNode *n) {
    // fetch parent
    RBMNode *parent = n->parent;
    if (parent == NULL) {
        return NULL;
    }

    // fetch grandparent
    RBMNode *gp = parent->parent;
    if (gp == NULL) {
        return NULL;
    }

    // get sibling of parent
    if (gp->right == parent) {
        return gp->left;
    } else {
        return gp->right;
    }
}

/**
 * @returns grandparent of this node or NULL iff the
 * grandparent does not exist
 **/
static RBMNode* gpOf(RBMNode *n) {
    RBMNode *parent = n->parent;
    if (parent == NULL) {
        return NULL;
    } else {
        return parent->parent;
    }
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
