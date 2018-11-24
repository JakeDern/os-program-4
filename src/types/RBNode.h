#ifndef _RBNODE
#define _RBNODE

#include <stdio.h>

enum COLOR {BLACK=0, RED=1};

typedef struct RBNode {
  enum COLOR color;
  void *data; 
} RBNode;

/**
 * Creates and returns a pointer to a new
 * RBNode
 * 
 * @returns RBNode*
 **/
extern RBNode* newRBNode();

#endif