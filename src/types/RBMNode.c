#include <stdio.h>
#include <stdlib.h>

#include "./RBMNode.h"

/** @override */
RBMNode* newRBMNode(void *key, void *val) {
    RBMNode *node;
    if ( (node = malloc(sizeof(RBMNode))) == NULL) {
        printf("Failed to allocate memory for RBMNode\n");
        exit(1);
    }

    if ( (node->kv = malloc(sizeof(KVPair))) == NULL) {
        printf("Failed to allocate memory for RBMNode");
        exit(1);
    }

    node->color   = RED;
    node->kv->key = key;
    node->kv->val = val;
    node->parent  = NULL;
    node->right   = NULL;
    node->left    = NULL;

    return node;
}