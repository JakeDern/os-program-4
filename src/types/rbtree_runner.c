#include <stdio.h>
#include <stdlib.h>

#include "./RedBlackMap.h"

int intCompare(void *int1, void *int2);
static void printHelper(RBMNode *n);
static void RBMPrintInOrder(RedBlackMap *map);

typedef int Integer;

int main() {
    RedBlackMap *tree = newRedBlackMap((cmpFunc) &intCompare);
    int *key = malloc(sizeof(int));
    int *key2 = malloc(sizeof(int));
    int *key3 = malloc(sizeof(int));
    int *key4 = malloc(sizeof(int));
    int *key5 = malloc(sizeof(int));
    int *key6 = malloc(sizeof(int));
    int *key7 = malloc(sizeof(int));
    
    *key = 1;
    *key2 = 4;
    *key3 = 5;
    *key4 = 7;
    *key5 = 10;
    *key6 = 13;
    *key7 = 12;
    
    int *val = malloc(sizeof(int));
    *val = 10;

    RBMPut(tree, (void*) key, (void*) val);
    RBMPrintInOrder(tree);
    RBMPut(tree, (void*) key2, (void*) val);
    RBMPrintInOrder(tree);
    RBMPut(tree, (void*) key3, (void*) val);
    RBMPrintInOrder(tree);
    RBMPut(tree, (void*) key4, (void*) val);
    RBMPrintInOrder(tree);
    RBMPut(tree, (void*) key5, (void*) val);
    RBMPrintInOrder(tree);
    RBMPut(tree, (void*) key6, (void*) val);
    RBMPrintInOrder(tree);
    RBMPut(tree, (void*) key7, (void*) val);
    RBMPrintInOrder(tree);
    // printf("%d\n", *((int*)(tree->root->kv->key)));
    // printf("%d\n", *((int*)(tree->root->right->kv->key)));
    // printf("%d\n", *((int*)(tree->root->left->kv->key)));
    // printf("%d\n", *((int*)(tree->root->left->right->kv->key)));
    // printf("%d\n", *((int*)(tree->root->right->left->kv->key)));

    RBMPrintInOrder(tree);
}

static enum COLOR colorOf(RBMNode *n) {
    if (n == NULL) {
        return BLACK;
    } else {
        return n->color;
    }
}


int intCompare(void *int1, void *int2) {
    return *((int *) int1) - *((int *) int2); 
}

static void RBMPrintInOrder(RedBlackMap *map) {
    printf("After add: ");
    printf("ROOT is %d: ", *((int*)(map->root->kv->key)));
    printHelper(map->root);
    printf("\n");
}

static void printHelper(RBMNode *n) {
    if (n != NULL) {
        printHelper(n->left);
        char color = n->color == BLACK ? 'B' : 'R';
        printf("%d(%c)", *((int*)(n->kv->key)), color);
        if (n->parent != NULL) {
            printf("(p=%d) ", *((int*)(n->parent->kv->key)));
        } else {
            printf("(p=null) ");
        }
        printHelper(n->right);
    }
}

