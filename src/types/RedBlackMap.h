#ifndef _RedBlackMap
#define _RedBlackMap

#include "./RBMNode.h"

/**
 * This function will provide an ordering for any keys
 * contained in the red black tree map and will be used
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
 
typedef void (*destructKey)(void*);

typedef void (*destructVal)(void*);

typedef struct RedBlackMap {
    int size;
    RBMNode *root;
    cmpFunc cmpKey;
    destructKey dKey;
} RedBlackMap;

/**
 * Allocates memmory for and returns a pointer
 * to a new RedBlackMap
 * 
 * @param comparison function
 * @returns RedBlackMap*
 **/
extern RedBlackMap* newRedBlackMap(cmpFunc compare);

/**
 * Inserts a new item into this redblack tree
 * 
 * @param tree the RedBlackMap
 * @param void *data the data
 **/
extern void RBMPut(RedBlackMap *tree, void *key);

/**
 * Deletes the given data from the tree
 * 
 * @param tree the RedBlackMap
 * @param data the data to delete 
 **/
extern void RBMDelete(RedBlackMap *tree, void *key);

/**
 * Searches for the given data in the tree
 * 
 * @param tree the tree to search
 * @param data the data to search for
 * @returns void* ptr to the data if found, NULL otherwise
 **/
extern void* RBMSearch(RedBlackMap *tree, void *key);

extern void RBMReplace(RedBlackMap *map, void *key, void *val);

extern void RBMDestructKey(RedBlackMap *map, destructKey dKey);

/**
 * Destructs the provided RedBlackMap, but
 * does not free the data contained within it.
 * 
 * @param *tree the tree to destroy
 **/
extern void RBMDestroy(RedBlackMap *tree);

/**
 * Destructs the provided RedBlackMap and frees all
 * data provided to it using the provided deconstructor
 *
 * @param tree the tree to destroy
 * @param destructor a function which will be called on each
 * data item in the tree to destroy it
 **/
extern void RBMDestroyAndFree(RedBlackMap *tree, destructVal destructVal);

#endif