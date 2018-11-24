#ifndef _REDBLACKTREE
#define _REDBLACKTREE

#include "./RBNode.h"

/**
 * This function will provide an ordering for any two
 * items contained in the red black tree and will be used
 * for the insertion/search functions.
 * 
 * If this function does not run in constant time then
 * the behavior of the tree will be negatively impacted
 * 
 * If this function does not work as defined then the
 * behavior of the tree will be undefined
 * 
 * @param void* item1 a pointer to the first item
 * @param void* item2 a pointer to the second item
 * @returns a negative iteger iff item1 < item2
 *          a positive integer iff item1 > item2
 *          0 iff item1 === item2
 **/
typedef int (*cmpFunc)(void*, void*);

typedef void (*destruct)(void*);

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
 * Destructs the provided RedBlackTree, but
 * does not free the data contained within it.
 * 
 * @param *tree the tree to destroy
 **/
extern void RBDestroy(RedBlackTree *tree);

/**
 * Destructs the provided RedBlackTree and frees all
 * data provided to it using the provided deconstructor
 *
 * @param tree the tree to destroy
 * @param destructor a function which will be called on each
 * data item in the tree to destroy it
 **/
extern void RBDestroyAndFree(RedBlackTree *tree, destruct destructor);

#endif