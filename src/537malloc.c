#include "./537malloc.h"
#include "./types/AVLMap.h"
#include <stddef.h>
#include <stdlib.h>

static int init = 0;
static AVLMap *allocMap;
static AVLMap *freeMap;

AVLNode *findNodeBefore(void *ptr);
void init537Malloc();
int compareKey(void *a, void *b);

int compareKey(void *a, void *b)
{
    if (a > b)
    {
        return 1;
    }
    else if (a == b)
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
            free(temp->key);
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
        //TODO: Fix this with new specs
        AVLNode *temp;
        if ((temp = findNodeBefore(ptr)) != NULL)
        {
            printf("found node before\n");
            unsigned int tempVal = (unsigned int)temp->kv->key + (unsigned int)*(size_t *)(temp->kv->val);
            if (tempVal > (unsigned int)ptr)
            {
                fprintf(stderr, "Attempt to clear memory in another block");
                exit(-1);
            }
            fprintf(stderr, "Attempt to clear unallocated memory");
            exit(-1);
        }
        printf("About to check freemap for item\n");
        if ((AVLSearch(freeMap, (void *)ptr) != NULL))
        {
            fprintf(stderr, "Double free");
            exit(-1);
        }
        else
        {
            fprintf(stderr, "Attempt to clear unallocated memory");
            exit(-1);
        }
    }

    KVPair *temp1 = (KVPair *)AVLDelete(allocMap, ptr);
    free(temp1->key);
    free(temp1->val);
    AVLPut(freeMap, (void *)ptr, (void *)ptr);
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
        free537(ptr);
        return NULL;
    }
    if (AVLSearch(allocMap, ptr) != NULL)
    {
        KVPair *temp = (KVPair *)AVLDelete(allocMap, ptr);
        free(temp->key);
        free(temp->val);
    }
    realloc(ptr, size);
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
    unsigned int testVal = (unsigned int)ptr + (unsigned int)size;
    unsigned int memVal = 0;
    if (nodeBefore != NULL)
    {
        memVal = (unsigned int)(nodeBefore->kv->key) + (unsigned int)*(size_t *)nodeBefore->kv->val;
    }
    if (testVal > memVal)
    {
        printf("memVal addition: %u\n", memVal);
        fprintf(stderr, "The memory block spanning from %u to %u is not fully included in any block allocated by malloc537.", (unsigned int)ptr, (unsigned int)ptr + (unsigned int)size);
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
        printf("entering while: curr: %p, ptr: %p\n", curr->kv->key, ptr);
        if (compareKey(ptr, curr->kv->key) == 0)
        {
            return curr;
        }
        else if (compareKey(ptr, curr->kv->key) > 0)
        {
            printf("entered greater than case\n");
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