#include <stdio.h>
#include <stdlib.h>

#include "./RBMNode.h"

/** @override */
RBMNode* newRBMNode(void *data) {
    RBMNode *node;
    if ( (node = malloc(sizeof(RBMNode))) == NULL) {
        printf("Failed to allocate memory for RBMNode\n");
        exit(1);
    }

    node->color = RED;
    node->data = data;

    return node;
}