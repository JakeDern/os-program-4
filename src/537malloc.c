#include "./537malloc.h"
#include <stddef.h>

extern RedBlackMap *allocMap = newRedBlackMap(NULL);
extern RedBlackMap *freeMap = newRedBlackMap(NULL);

int freeOverwrite(void *ptr);

void *malloc537(size_t size)
{
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
    RBMPut(allocMap, (void *)returnPtr, (void *)size);
    if (!(RBMSearch(freeMap, returnPtr) == NULL))
    {
        KVPair *temp;
        if ((temp = RBMDelete(freeMap, returnPtr)) != NULL)
        {
            free(temp->key);
        }
    }
    return returnPtr;
}

void free537(void *ptr)
{
    if ((RBMSearch(allocMap, ptr) == NULL))
    {
        if (freeOverwrite(ptr))
        {
            fprintf(stderr, "Attempt to clear memory in another block");
            exit(1);
        }
        fprintf(stderr, "Attempt to clear unallocated memory");
        exit(1);
    }
    if (!(RBMSearch(freeMap, ptr) == NULL))
    {
        fprintf(stderr, "Double free");
        exit(1);
    }

    KVPair *temp = RBMDelete(allocMap, ptr);
    free(temp->key);
    free(temp->val);
    RBMPut(freeMap, ptr, NULL);
    free(ptr);

    return;
}

void *realloc537(void *ptr, size_t size)
{
    return NULL;
}

void memcheck537(void *ptr, size_t size)
{
    return;
}

int freeOverwrite(void *ptr)
{
    RBMNode *curr = allocMap->root;
    RBMNode *min = NULL;

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
            return 1;
        }
    }
    return 0;
}