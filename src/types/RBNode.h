#ifndef _RBNODE
#define _RBNODE

#include <stdio.h>

enum COLOR {BLACK=0, RED=1};

typedef struct RBNode {
  enum COLOR color;
  void *data;
  struct RBNode *parent;
  struct RBNode *left;
  struct RBNode *right; 
} RBNode;

/**
 * Creates and returns a pointer to a new
 * RBNode of red color
 * 
 * @returns RBNode*
 **/
extern RBNode* newRBNode(void *data);

#endif