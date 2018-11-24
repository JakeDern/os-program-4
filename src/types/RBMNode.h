#ifndef _RBMNode
#define _RBMNode

#include <stdio.h>

enum COLOR {BLACK=0, RED=1};

typedef struct RBMNode {
  enum COLOR color;
  void *data;
  struct RBMNode *parent;
  struct RBMNode *left;
  struct RBMNode *right; 
} RBMNode;

/**
 * Creates and returns a pointer to a new
 * RBMNode of red color
 * 
 * @returns RBMNode*
 **/
extern RBMNode* newRBMNode(void *data);

#endif