#include <stdio.h>
#include <stdlib.h>

#include "./AVLMap.h"

int intCompare(void *int1, void *int2);
static void printHelper(AVLNode *n);
static void AVLPrintInOrder(AVLMap *map);

typedef int Integer;

// int main()
// {
//     AVLMap *tree = newAVLMap((cmpFunc)&intCompare);
//     int *key = malloc(sizeof(int));
//     int *key2 = malloc(sizeof(int));
//     int *key3 = malloc(sizeof(int));
//     int *key4 = malloc(sizeof(int));
//     int *key5 = malloc(sizeof(int));
//     int *key6 = malloc(sizeof(int));
//     int *key7 = malloc(sizeof(int));

//     *key = 1;
//     *key2 = 4;
//     *key3 = 5;
//     *key4 = 7;
//     *key5 = 10;
//     *key6 = 13;
//     *key7 = 12;

//     int *del = 17;
//     AVLDelete(tree, key4);
//     AVLPrintInOrder(tree);
//     AVLDelete(tree, key3);
//     AVLPrintInOrder(tree);
//     AVLDelete(tree, key);
//     AVLPrintInOrder(tree);
//     AVLDelete(tree, key2);
//     AVLPrintInOrder(tree);
//     AVLDelete(tree, key5);
//     AVLPrintInOrder(tree);
//     AVLDelete(tree, key6);
//     AVLPrintInOrder(tree);
//     AVLDelete(tree, key7);
//     //AVLPrintInOrder(tree);
//     (unsigned int)*((size_t *)val);
// }

int intCompare(void *int1, void *int2)
{
    return *((int *)int1) - *((int *)int2);
}

static void AVLPrintInOrder(AVLMap *map)
{
    printf("ROOT is %d: ", *((int *)(map->root->kv->key)));
    printHelper(map->root);
    printf("\n");
}

static void printHelper(AVLNode *n)
{
    if (n != NULL)
    {
        printHelper(n->left);
        printf("%d", *((int *)(n->kv->key)));
        if (n->parent != NULL)
        {
            printf("(p=%d) ", *((int *)(n->parent->kv->key)));
        }
        else
        {
            printf("(p=null) ");
        }
        printHelper(n->right);
    }
}
