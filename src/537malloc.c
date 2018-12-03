#include "./537malloc.h"
#include "./types/AVLMap.h"
#include <stddef.h>
#include <stdlib.h>

static int init = 0;
static RedBlackMap *allocMap;
static RedBlackMap *freeMap;

int freeOverwrite(void *ptr);
void init537Malloc();
int compareKey(unsigned int a, unsigned int b);

int compareKey(unsigned int a, unsigned int b)
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
    RedBlackMap *allocMap = newAVLMap((cmpFunc *)&compareKey);
    RedBlackMap *freeMap = newAVLMap((cmpFunc *)&compareKey);
}

void *malloc537(size_t size)
{
    if (init == 0)
    {
        init537Malloc();
        init = 1;
    }
    if (size == 0)
    {
        fprintf(stderr, "Warning: malloc of size 0");
    }
    void *returnPtr;
    if ((returnPtr = malloc(size)) == NULL)
    {
        fprinf(stderr, "Failed to malloc block of size %zu\n", size);
        return NULL;
    }
    AVLPut(allocMap, (void *)returnPtr, (void *)size);
    if (!(AVLSearch(freeMap, returnPtr) == NULL))
    {
        KVPair *temp;
        if ((temp = ((KVPair *)AVLDelete(freeMap, returnPtr)) != NULL))
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
        init = 1;
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
        init = 1;
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
    ptr = realloc(ptr, size);
    AVLPut(allocMap, ptr, size);

    return ptr;
}

void memcheck537(void *ptr, size_t size)
{
    if (init == 0)
    {
        init537Malloc();
        init = 1;
    }
    int memBlockStart = freeOverwrite(ptr);
    AVLNode *keyBlock = (AVLNode *)AVLSearch(allocMap, memBlockStart);
    if (((unsigned int)ptr + (unsigned int)size > (unsigned int)keyBlock->kv->key + (unsigned int)keyBlock->kv->val) || memBlockStart == 0)
    {
        fprintf(stderr, "The memory block spanning from %u to %u is not fully included in any block allocated by malloc537.", (unsigned int)keyBlock->kv->key, (unsigned int)keyBlock->kv->key + (unsigned int)keyBlock->kv->val);
        exit(-1);
    }

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
            return (unsigned int)min->kv->key;
        }
    }
    return 0;
}