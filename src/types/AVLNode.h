/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */
#ifndef _AVLNode
#define _AVLNode

#include <stdio.h>

typedef struct KVPair {
    void *key;
    void *val;
} KVPair;

typedef struct AVLNode {
    int height;
    KVPair *kv;
    struct AVLNode *parent;
    struct AVLNode *left;
    struct AVLNode *right; 
} AVLNode;

/**
 * Creates and returns a pointer to a new
 * AVLNode of red color
 * 
 * @returns AVLNode*
 **/
extern AVLNode* newAVLNode(void *key, void *val);

#endif