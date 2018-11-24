#include <stdio.h>
#include <stdlib.h>

#include "./RBNode.h"

/** @override */
RBNode* newRBNode(void *data) {
    RBNode *node;
    if ( (node = malloc(sizeof(RBNode))) == NULL) {
      printf("Failed to allocate memory for RBNode\n");
      exit(1);
    }

    node->color = RED;
    node->data = data;

    return node;
}