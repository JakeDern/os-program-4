#include <stdio.h>
#include <stdlib.h>

#include "./AVLNode.h"

/** @override */
AVLNode* newAVLNode(void *key, void *val) {
    AVLNode *node;
    if ( (node = malloc(sizeof(AVLNode))) == NULL) {
        printf("Failed to allocate memory for AVLNode\n");
        exit(1);
    }

    if ( (node->kv = malloc(sizeof(KVPair))) == NULL) {
        printf("Failed to allocate memory for AVLNode");
        exit(1);
    }

    node->height  = 0;
    node->kv->key = key;
    node->kv->val = val;
    node->parent  = NULL;
    node->right   = NULL;
    node->left    = NULL;

    return node;
}