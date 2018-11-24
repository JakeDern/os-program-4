#ifndef _REDBLACKTREE
#define _REDBLACKTREE

#include "./RBNode.h"

typedef int (*cmpFunc)(void*, void*);

typedef struct RedBlackTree {
    int size;
    RBNode *root;
    cmpFunc compare;
} RedBlackTree;

/**
 * Allocates memmory for and returns a pointer
 * to a new RedBlackTree
 * 
 * @param comparison function
 * @returns RedBlackTree*
 **/
extern RedBlackTree* newRedBlackTree(cmpFunc compare);

/**
 * Inserts a new item into this redblack tree
 * 
 * @param tree the RedBlackTree
 * @param void *data the data
 **/
extern void RBInsert(RedBlackTree *tree, void *data);

/**
 * Deletes the given data from the tree
 * 
 * @param tree the RedBlackTree
 * @param data the data to delete 
 **/
extern void RBDelete(RedBlackTree *tree, void *data);

/**
 * Searches for the given data in the tree
 * 
 * @param tree the tree to search
 * @param data the data to search for
 * @returns void* ptr to the data if found, NULL otherwise
 **/
extern void* RBSearch(RedBlackTree *tree, void *data);

/**
 * Frees all nodes and data from the RedBlackTRee
 * 
 * @param *tree the tree to free
 **/
extern void RBFree(RedBlackTree *tree);

#endif