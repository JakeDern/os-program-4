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

/**
 * A function for destructing keys in this map
 * 
 * @param void* the key to destruct
 **/
typedef void (*destructKey)(void*);

/**
 * A function for destructing values in this map
 * 
 * @param void* the value to destruct
 **/
typedef void (*destructVal)(void*);

typedef struct RedBlackMap {
    int size;
    RBMNode *root;
    cmpFunc cmpKey;
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
extern void RBMPut(RedBlackMap *map, void *key, void *val);

/**
 * Deletes the given data from the tree
 * 
 * @param tree the RedBlackMap
 * @param data the data to delete
 * @returns KVPair* of the deleted data
 **/
extern KVPair* RBMDelete(RedBlackMap *map, void *key);

/**
 * Searches for the given data in the tree
 * 
 * @param tree the tree to search
 * @param data the data to search for
 * @returns void* ptr to the data if found, NULL otherwise
 **/
extern void* RBMSearch(RedBlackMap *map, void *key);

/**
 * Replaces the given key with the given value in the tree,
 * or if the key doesn't exist, does nothing.
 * 
 * @param map the map
 * @param key the key
 * @param value the value
 * @returns pointer to the old value contained in the map or NULL
 * if the key was not found
 **/
extern void* RBMReplace(RedBlackMap *map, void *key, void *val);

/**
 * Destructs the provided RedBlackMap, but
 * does not free the keys or values contained
 * within it
 * 
 * @param *tree the tree to destroy
 **/
extern void RBMDestroy(RedBlackMap *map);

/**
 * Destructs the provided RedBlackMap and frees all
 * data provided to it using the provided deconstructors
 *
 * @param tree the tree to destroy
 * @param destructor a function which will be called on each
 * data item in the tree to destroy it
 **/
extern void RBMDestroyAndFree(RedBlackMap *map, destructKey dKey, destructVal dVal);

#endif