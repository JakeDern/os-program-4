/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */
#include "./537malloc.h"
#include "./types/AVLMap.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

static int init = 0;
static AVLMap *allocMap;
static AVLMap *freeMap;

AVLNode *findNodeBefore(void *ptr);
void init537Malloc();
int compareKey(void *a, void *b);

int compareKey(void *a, void *b)
{
    uintptr_t aVal = (uintptr_t)a;
    uintptr_t bVal = (uintptr_t)b;
    if (aVal > bVal)
    {
        return 1;
    }
    else if (aVal == bVal)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void init537Malloc()
{
    allocMap = newAVLMap((cmpFunc)&compareKey);
    freeMap = newAVLMap((cmpFunc)&compareKey);
    init = 1;
}

void *malloc537(size_t size)
{
    if (init == 0)
    {
        init537Malloc();
    }
    if (size == 0)
    {
        fprintf(stderr, "Warning: malloc of size 0\n");
    }
    void *returnPtr;
    if ((returnPtr = malloc(size)) == NULL)
    {
        fprintf(stderr, "Failed to malloc block of size %u\n", (unsigned int)size);
        return NULL;
    }
    size_t *tempPtr = malloc(sizeof(size_t));
    *tempPtr = size;

    AVLPut(allocMap, (void *)returnPtr, (void *)tempPtr);
    if (!(AVLSearch(freeMap, returnPtr) == NULL))
    {
        KVPair *temp;
        if (((temp = (AVLDelete(freeMap, returnPtr))) != NULL))
        {
            free(temp->val);
            free(temp);
        }
    }
    return returnPtr;
}

void free537(void *ptr)
{
    if (init == 0)
    {
        init537Malloc();
    }
    if ((AVLSearch(allocMap, ptr) == NULL))
    {
        AVLNode *temp;
        if ((temp = findNodeBefore(ptr)) != NULL)
        {
            uintptr_t tempVal = (uintptr_t)temp->kv->key + *(unsigned int*)(temp->kv->val);
            if (tempVal > (uintptr_t)ptr)
            {
                fprintf(stderr, "Error: Attempted to free memory in middle of a block\n");
                exit(-1);
            }
            fprintf(stderr, "Error: Attempted to free unallocated memory\n");
            exit(-1);
        }
        if ((AVLSearch(freeMap, (void *)ptr) != NULL))
        {
            fprintf(stderr, "Error: Double free at address %p\n", ptr);
            exit(-1);
        }
        else
        {
            fprintf(stderr, "Error: Attempted to free unallocated memory\n");
            exit(-1);
        }
    }

    uintptr_t *oldPtr = malloc(sizeof(uintptr_t));
    *oldPtr = (uintptr_t)ptr;
    KVPair *temp1 = (KVPair *)AVLDelete(allocMap, ptr);
    free(temp1->val);
    free(temp1);
    AVLPut(freeMap, (void *)ptr, (void *)oldPtr);
    free(ptr);

    return;
}

void *realloc537(void *ptr, size_t size)
{
    if (init == 0)
    {
        init537Malloc();
    }
    if (ptr == NULL)
    {
        return malloc537(size);
    }
    if ((unsigned int)size == 0)
    {
        fprintf(stderr, "Warning, reallocating memory at %p to size 0\n", ptr);
        free537(ptr);
        return NULL;
    }
    if (AVLSearch(allocMap, ptr) != NULL)
    {
        KVPair *temp = (KVPair *)AVLDelete(allocMap, ptr);
        free(temp->val);
        free(temp);
    }

    if ( (ptr = realloc(ptr, size)) == NULL) {
        fprintf(stderr, "failed to reallocate memory. Exiting...\n");
        exit(-1);
    }
    size_t *ptr1 = malloc(sizeof(size_t));
    *ptr1 = size;
    AVLPut(allocMap, ptr, (void *)ptr1);

    return ptr;
}

void memcheck537(void *ptr, size_t size)
{
    if (init == 0)
    {
        init537Malloc();
    }
    AVLNode *nodeBefore = findNodeBefore(ptr);
    uintptr_t testVal = (uintptr_t)ptr + (uintptr_t)size;
    unsigned int memVal = 0;
    if (nodeBefore != NULL)
    {
        memVal = (uintptr_t)(nodeBefore->kv->key) + *(unsigned int*)nodeBefore->kv->val;
    }
    if (testVal > memVal)
    {
        fprintf(stderr, "The memory block spanning from %p to %p is not fully included in any block allocated by malloc537\n", ptr, (char*)ptr + size);
        exit(-1);
    }
    return;
}

AVLNode *findNodeBefore(void *ptr)
{

    AVLNode *curr = allocMap->root;
    AVLNode *min = NULL;

    while (curr != NULL)
    {
        if (compareKey(ptr, curr->kv->key) == 0)
        {
            return curr;
        }
        else if (compareKey(ptr, curr->kv->key) > 0)
        {
            if (min == NULL)
            {
                min = curr;
            }
            else if (compareKey(min->kv->key, curr->kv->key) < 0)
            {
                min = curr;
            }
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    return min;
}