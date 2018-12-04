#include <stdio.h>
#include <stdlib.h>
#include "./AVLNode.h"
#include "./AVLMap.h"

static int isRightChild(AVLNode *n);
static AVLNode *rightRotate(AVLMap *map, AVLNode *n);
static AVLNode *leftRotate(AVLMap *map, AVLNode *n);
static void printHelper(AVLNode *n);
static AVLNode *getLeftMaximum(AVLNode *n);
static void fixInsert(AVLMap *map, AVLNode *n);
static int calcBalance(AVLNode *n);
static int calcHeight(AVLNode *n);
static AVLNode *deleteHelper(AVLMap *map, AVLNode *n, void *key);
static AVLNode *searchNode(AVLMap *map, void *key);
static void updateHeight(AVLNode *n);

static void AVLPrintInOrder(AVLMap *map)
{
    //printf("start print: ");
    printHelper(map->root);
    //printf("\n");
}

static void printHelper(AVLNode *n)
{
    if (n != NULL)
    {
        printHelper(n->left);
        //printf("%d", *((int *)(n->kv->key)));
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

/** @override */
AVLMap *newAVLMap(cmpFunc compare)
{
    AVLMap *map;
    if ((map = malloc(sizeof(AVLMap))) == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for AVLMap\n");
        exit(1);
    }

    map->size = 0;
    map->root = NULL;
    map->cmpKey = compare;

    return map;
}

/** @override */
void AVLPut(AVLMap *map, void *key, void *val)
{
    printf("adding %d\n", *((int *)key));
    // Edge: this is first insertion
    if (map->root == NULL)
    {
        map->root = newAVLNode(key, val);
        map->size = 1;
        return;
    }

    // find insertion point for new node
    AVLNode *prev = NULL;
    AVLNode *curr = map->root;
    cmpFunc compare = map->cmpKey;
    int comparison;
    while (curr != NULL)
    {
        comparison = (*compare)(key, curr->kv->key);
        prev = curr;
        if (comparison == 0)
        {
            // TODO: Throw duplicate key exception?
            return;
        }
        else if (comparison < 0)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    // increment size and link new node into tree
    AVLNode *newNode = newAVLNode(key, val);
    newNode->parent = prev;
    map->size++;
    if (comparison < 0)
    {
        prev->left = newNode;
    }
    else
    {
        prev->right = newNode;
    }

    curr = newNode;
    while (curr != NULL) {
        updateHeight(curr);
        curr = curr->parent;
    }

    // initiate fixing;
    fixInsert(map, newNode);
    map->root->parent = NULL;
}

/**
 * Adjusts the tree so that AVL properties are maintained
 * after an insertion
 * */
static void fixInsert(AVLMap *map, AVLNode *n)
{
    printf("performing fix for %d\n", *((int *)(n->kv->key)));
    AVLNode *z = n;
    int balance = 0;
    while ((balance = calcBalance(z)) >= -1 && balance <= 1)
    {
        // tree was balanced all the way to root
        if (z == NULL)
        {
            return;
        }
        // printf("balance on %d is %d\n", *((int*)(z->kv->key)), calcBalance(z));
        z = z->parent;
    }

    printf("fixing unbalanced node %d\n", *((int *)(z->kv->key)));
    if (balance > 0)
    {
        if (calcHeight(z->left->left) > calcHeight(z->left->right))
        {
            // left left case
            rightRotate(map, z);
        }
        else
        {
            // left right case
            leftRotate(map, z->left);
            rightRotate(map, z);
        }
    }
    else
    {
        if (calcHeight(z->right->right) > calcHeight(z->right->left))
        {
            // right right case
            leftRotate(map, z);
        }
        else
        {
            // right left case
            rightRotate(map, z->right);
            leftRotate(map, z);
        }
    }
}

/**
 * Calculates the balance factor of a node
 * @returns 0 iff the node is NULL, height of the
 * node otherwise
 * */
static int calcBalance(AVLNode *n)
{
    if (n == NULL)
    {
        return 0;
    }

    return calcHeight(n->left) - calcHeight(n->right);
}

/**
 * Calculates the height of a particular
 * node.
 * @returns 0 iff the node is NULL, height of the node
 * otherwise
 * */
static int calcHeight(AVLNode *n)
{
    if (n == NULL)
    {
        return 0;
    }

    return n->height;
}

/**
 * Performs a right rotation on the given node
 *
 * @see https://en.wikipedia.org/wiki/Tree_rotation
 * */
static AVLNode *rightRotate(AVLMap *map, AVLNode *n)
{
    printf("right rotate on %d\n", *((int *)(n->kv->key)));
    AVLNode *p = n->left;
    AVLNode *pRight = p->right;

    if (n->parent != NULL)
    {
        // n is not root node
        if (isRightChild(n) == 1)
        {
            n->parent->right = p;
        }
        else
        {
            n->parent->left = p;
        }
        p->parent = n->parent;
    }
    else
    {
        map->root = p;
    }

    n->left = pRight;
    p->right = n;
    n->parent = p;

    if (pRight != NULL)
    {
        pRight->parent = n;
    }

    updateHeight(n);
    updateHeight(p);

    return p;
}

static void updateHeight(AVLNode *n) {
    int rightH = calcHeight(n->right);
    int leftH = calcHeight(n->left);
    n->height = rightH > leftH ? rightH : leftH;
    n->height++;
}

/**
 * Performs a left rotation on the subtree rooted
 * at the given node
 * 
 * @see https://en.wikipedia.org/wiki/Tree_rotation
 * */
static AVLNode *leftRotate(AVLMap *map, AVLNode *n)
{
    printf("left rotate on %d\n", *((int *)(n->kv->key)));
    AVLNode *p = n->right;
    AVLNode *pLeft = p->left;

    if (n->parent != NULL)
    {
        // n is not root
        if (isRightChild(n))
        {
            n->parent->right = p;
        }
        else
        {
            n->parent->left = p;
        }
        p->parent = n->parent;
    }
    else
    {
        map->root = p;
    }

    n->right = pLeft;
    p->left = n;
    n->parent = p;

    if (pLeft != NULL)
    {
        pLeft->parent = n;
    }

    updateHeight(n);
    updateHeight(p);

    return p;
}

/**
 * Determines if the given node is a left child
 * 
 * @returns -1 iff the node is null
 *          1 iff the node is a right child
 *          0 iff the node is a left child
 * */
static int isRightChild(AVLNode *n)
{
    if (n == NULL)
    {
        return -1;
    }

    if (n->parent == NULL)
    {
        return -1;
    }

    return n->parent->left == n ? 0 : 1;
}

/** @override */
KVPair *AVLDelete(AVLMap *map, void *key)
{
    printf("calling search\n");
    AVLNode *removed = searchNode(map, key);

    if (removed == NULL)
    {
        // key was not in the tree
        printf("key not found\n");
        return NULL;
    }

    // special case of delete root as last item
    if (map->root->left == NULL && map->root->right == NULL)
    {
        KVPair *ret = map->root->kv;
        free(map->root);
        map->root = NULL;
        return ret;
    }

    KVPair *ret = removed->kv;
    map->root = deleteHelper(map, map->root, key);
    map->size--;
    map->root->parent = NULL;
    return ret;
}

/**
 * Recursively deletes the provided node from the tree and fixes the
 * tree to maintain AVL properties as it does so
 * */
static AVLNode *deleteHelper(AVLMap *map, AVLNode *n, void *key)
{
    printf("deleting %d\n", (unsigned int)key);
    if (n == NULL)
    {
        return n;
    }

    cmpFunc compare = map->cmpKey;
    int comparison = (*compare)(key, n->kv->key);
    if (comparison < 0)
    {
        n->left = deleteHelper(map, n->left, key);
    }
    else if (comparison > 0)
    {
        n->right = deleteHelper(map, n->right, key);
    }
    else
    {
        if (n->left == NULL || n->right == NULL)
        {
            // at most one child
            if (n->left == NULL && n->right == NULL)
            {
                // no children
                free(n);
                n = NULL;
            }
            else
            {
                AVLNode *parent = n->parent;
                *n = (n->left == NULL) ? *(n->right) : *(n->left);
                n->parent = parent;
            }
        }
        else
        {
            AVLNode *replacement = getLeftMaximum(n);
            n->kv = replacement->kv;
            n->left = deleteHelper(map, n->left, replacement->kv->key);
        }
    }

    // subtree of size 1
    if (n == NULL)
    {
        return n;
    }

    updateHeight(n);

    int balance = calcBalance(n);
    if (balance > 1)
    {
        if (calcBalance(n->left) >= 0)
        {
            // left left
            return rightRotate(map, n);
        }
        else
        {
            // left right
            n->left = leftRotate(map, n->left);
            return rightRotate(map, n);
        }
    }
    else if (balance < -1)
    {
        if (calcBalance(n->right) <= 0)
        {
            // right right
            return leftRotate(map, n);
        }
        else
        {
            // right left
            n->right = rightRotate(map, n->right);
            return leftRotate(map, n);
        }
    }
    else
    {
        return n;
    }
}

/**
 * Gets the maximum node of the left subtree
 * of the given node
 * */
static AVLNode *getLeftMaximum(AVLNode *n)
{
    if (n == NULL || n->left == NULL)
    {
        return NULL;
    }

    AVLNode *curr = n->left;
    while (curr->right != NULL)
    {
        curr = curr->right;
    }

    return curr;
}

/** @override */
void *AVLSearch(AVLMap *map, void *key)
{
    AVLNode *n = searchNode(map, key);
    return n == NULL ? NULL : n->kv->val;
}

/**
 * Searches for and returns the node associated with the
 * provided key in the tree if it exists
 * */
static AVLNode *searchNode(AVLMap *map, void *key)
{
    printf("Looking for %d\n", *((int *)key));
    AVLNode *curr = map->root;
    while (curr != NULL)
    {
        cmpFunc compare = map->cmpKey;
        printf("Comparing %d with %d\n", *((int *)key), *((int *)curr->kv->key));
        int comparison = (*compare)(key, curr->kv->key);
        printf("comparison was %d\n", comparison);
        if (comparison == 0)
        {
            break;
        }
        else if (comparison < 0)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    if (curr == NULL)
    {
        // key was not found
        return NULL;
    }
    else
    {
        return curr;
    }
}

/**
 * Replaces the KVPair with the same key, but the
 * new value in the tree
 * */
void *AVLReplace(AVLMap *map, void *key, void *val)
{
    AVLNode *target = AVLSearch(map, key);
    if (target == NULL)
    {
        return NULL;
    }
    void *oldVal = target->kv->val;
    AVLDelete(map, key);
    AVLPut(map, key, val);

    return oldVal;
}

/** @override */
void AVLDestroy(AVLMap *map)
{
}

/** @override */
void AVLDestroyAndFree(AVLMap *map, destructKey dKey, destructVal dVal)
{
}
