#include "./537malloc.h"
#include "./types/AVLMap.h"
#include <stddef.h>
#include <stdlib.h>

static int init = 0;
static RedBlackMap *allocMap;
static RedBlackMap *freeMap;

int freeOverwrite(void *ptr);
void init537Malloc();
int compareKey(void *a, void *b);

int compareKey(void *a, void *b)
{
    if (a > b)
    {
        return -1;
    }
    else if (a == b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void init537Malloc()
{
<<<<<<< Updated upstream
    RedBlackMap *allocMap = newAVLMap((cmpFunc *)&compareKey);
    RedBlackMap *freeMap = newAVLMap((cmpFunc *)&compareKey);
=======
    allocMap = newAVLMap((cmpFunc)&compareKey);
    freeMap = newAVLMap((cmpFunc)&compareKey);
    init = 1;
>>>>>>> Stashed changes
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
        if (freeOverwrite(ptr))
        {
            fprintf(stderr, "Attempt to clear memory in another block");
            exit(1);
        }
        fprintf(stderr, "Attempt to clear unallocated memory");
        exit(1);
    }
    if (!(AVLSearch(freeMap, ptr) == NULL))
    {
        fprintf(stderr, "Double free");
        exit(1);
    }

    KVPair *temp = (KVPair *)AVLDelete(allocMap, ptr);
    free(temp->key);
    free(temp->val);
    AVLPut(freeMap, ptr, NULL);
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
    int *memBlockStart = malloc(sizeof(int));
    *memBlockStart = freeOverwrite(ptr);
    printf("retrieved memblockstart %d\n", *memBlockStart);
    size_t *keyVal = (size_t *)AVLSearch(allocMap, (void *)memBlockStart);
    printf("retrieved keyblock, issue is with the below print statement\n");
    unsigned int testVal = (unsigned int)ptr + (unsigned int)size;
    printf("here\n");
    unsigned int memVal = (unsigned int)*memBlockStart + (unsigned int)*keyVal;
    printf("here2\n");
    if (testVal > memVal || memBlockStart == 0)
    {
        fprintf(stderr, "The memory block spanning from %u to %u is not fully included in any block allocated by malloc537.", (unsigned int)keyBlock->kv->key, (unsigned int)keyBlock->kv->key + (unsigned int)keyBlock->kv->val);
        exit(-1);
    }
    free(memBlockStart);

    return;
}

int freeOverwrite(void *ptr)
{

    AVLNode *curr = allocMap->root;
    AVLNode *min = NULL;

    while (curr != NULL)
    {
        if ((unsigned int)ptr < (unsigned int)curr->kv->key)
        {
            curr = curr->left;
        }
        else
        {
            if (min == NULL)
            {
                min = curr;
            }
            else
            {
                if ((unsigned int)min->kv->key > (unsigned int)curr->kv->key)
                {
                    min = curr;
                }
            }
            curr = curr->right;
        }
    }
    if (min != NULL)
    {
        if ((unsigned int)ptr < ((unsigned int)min->kv->key + (unsigned int)min->kv->val))
        {
            printf("returning from print overwrite with addr %u as < %u\n", (unsigned int)min->kv->key, (unsigned int)ptr);
            return (unsigned int)min->kv->key;
        }
    }
    return 0;
}