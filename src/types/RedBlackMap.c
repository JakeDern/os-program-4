#include <stdio.h>
#include <stdlib.h>

#include "./RBMNode.h"
#include "./RedBlackMap.h"

static void fixTree(RedBlackMap *map, RBMNode *n);
static RBMNode* uncleOf(RBMNode *n);
static RBMNode* gpOf(RBMNode *n);
static enum COLOR colorOf(RBMNode *n);
static int isLeftChild(RBMNode *n);
static int isRightChild(RBMNode *n);
static void doLeftLeft(RedBlackMap *map, RBMNode *n);
static void doRightRight(RedBlackMap *map, RBMNode *n);
static void doLeftRight(RedBlackMap *map, RBMNode *n);
static void doRightLeft(RedBlackMap *map, RBMNode *n);
static void rightRotate(RedBlackMap *map, RBMNode *n);
static void leftRotate(RedBlackMap *map, RBMNode *n);
static void printHelper(RBMNode *n);

static void RBMPrintInOrder(RedBlackMap *map) {
    printf("start print: ");
    printHelper(map->root);
    printf("\n");
}

static void printHelper(RBMNode *n) {
    if (n != NULL) {
        printHelper(n->left);
        char color = colorOf(n) == BLACK ? 'B' : 'R';
        printf("%d(%c)", *((int*)(n->kv->key)), color);
        if (n->parent != NULL) {
            printf("(p=%d) ", *((int*)(n->parent->kv->key)));
        } else {
            printf("(p=null) ");
        }
        printHelper(n->right);
    }
}


/** @override */
RedBlackMap* newRedBlackMap(cmpFunc compare) {
    RedBlackMap *map;
    if ( (map = malloc(sizeof(RedBlackMap))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for RedBlackMap\n");
        exit(1);
    }

    map->size   = 0;
    map->root   = NULL;
    map->cmpKey = compare;

    return map;
}

/** @override */
void RBMPut(RedBlackMap *map, void *key, void *val) {
    printf("adding %d\n", *((int*)key));
    // Edge: this is first insertion
    if (map->root == NULL) {
        map->root = newRBMNode(key, val);
        map->root->color = BLACK;
        map->size = 1;
        return;
    }

    // find insertion point for new node
    RBMNode *prev = NULL;
    RBMNode *curr = map->root;
    cmpFunc compare = map->cmpKey;
    int comparison;
    while (curr != NULL) {
        comparison = (*compare)(key, curr->kv->key);
        prev = curr;
        if (comparison == 0) {
            // TODO: Throw duplicate key exception?
            return;
        } else if (comparison < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    // increment size and link new node into tree
    RBMNode *newNode = newRBMNode(key, val);
    newNode->parent = prev;
    map->size++;
    if (comparison < 0) {
        prev->left = newNode;
    } else {
        prev->right = newNode;
    }

    // initiate fixing;
    fixTree(map, newNode);
}

static void fixTree(RedBlackMap *map, RBMNode *n) {
    // Fixing is complete to the root
    if (n == NULL) {
        return;
    }

    // nothing to fix
    if (colorOf(n->parent) == BLACK) {
        return;
    }

    /** CASE 1: Red uncle recolor */
    RBMNode *uncle = uncleOf(n);
    if (colorOf(uncle) == RED) {
        // recolor parent and uncle
        n->parent->color = BLACK;
        uncle->color = BLACK;
        
        // recolor grandparent if not root
        RBMNode *gp = gpOf(n);
        if (gp->parent != NULL) {
            gp->color = RED;
        }

        // recursively fix grandparent and return
        fixTree(map, gp);
        map->root->color = BLACK;
        map->root->parent = NULL;
        return;
    }

    /** CASE 2: rotations */
    if (isLeftChild(n->parent) == 1) {
        if (isLeftChild(n) == 1) {
            // left left case
            doLeftLeft(map, n);
        } else {
            // left right case
            doLeftRight(map, n);
        }
    } else {
        if (isRightChild(n) == 1) {
            // right right case
            doRightRight(map, n);
        } else {
            // right left case
            doRightLeft(map, n);
        }
    }
}

static void doLeftLeft(RedBlackMap *map, RBMNode *n) {
    printf("applying LeftLeft to %d\n", *((int*)(n->kv->key)));
    RBMNode *g = gpOf(n);
    RBMNode *p = n->parent;
    rightRotate(map, g);

    enum COLOR tmp = colorOf(g);
    g->color = colorOf(p);
    p->color = tmp;

    map->root->color = BLACK;
    map->root->parent = NULL;
}

static void doRightRight(RedBlackMap *map, RBMNode *n) {
    printf("applying RightRight to %d\n", *((int*)(n->kv->key)));
    RBMNode *g = gpOf(n);
    RBMNode *p = n->parent;
    leftRotate(map, g);

    enum COLOR tmp = colorOf(g);
    g->color = colorOf(p);
    p->color = tmp;

    map->root->parent = NULL;
    map->root->color = BLACK;
}

static void doLeftRight(RedBlackMap *map, RBMNode *n) {
    printf("applying LeftRight to %d\n", *((int*)(n->kv->key)));
    RBMNode *g = gpOf(n);
    RBMNode *p = n->parent;
    leftRotate(map, n->parent);
    doLeftLeft(map, p);
}

static void doRightLeft(RedBlackMap *map, RBMNode *n) {
    printf("applying RightLeft to %d\n", *((int*)(n->kv->key)));
    RBMNode *g = gpOf(n);
    RBMNode *p = n->parent;
    rightRotate(map, p);

    printf("after right: ");
    RBMPrintInOrder(map);
    
    doRightRight(map, p);
}

static void rightRotate(RedBlackMap *map, RBMNode *n) {
    printf("right rotate on %d\n", *((int*)(n->kv->key)));
    RBMNode *p = n->left;
    RBMNode *pRight = p->right;
    RBMNode *x = n->left->left;
    RBMNode *u = n->right;
    if (n->parent != NULL) {
        // n is not root node
        if (isRightChild(n) == 1) {
            n->parent->right = p;
        } else {
            n->parent->left = p;
        }
        p->parent = n->parent;
    } else {
        map->root = p;
    }

    n->left = pRight;
    p->right = n;
    n->parent = p;

    if (pRight != NULL) {
        pRight->parent = n;
    }
}

static void leftRotate(RedBlackMap *map, RBMNode *n) {
    printf("left rotate on %d\n", *((int*)(n->kv->key)));
    RBMNode *u = n->left;
    RBMNode *p = n->right;
    RBMNode *x = n->right->right;
    RBMNode *pLeft = p->left;

    if (n->parent != NULL) {
        // n is not root
        if (isRightChild(n)) {
            n->parent->right = p;
        } else {
            n->parent->left = p;
        }
        p->parent = n->parent;
    } else {
        map->root = p;
    }

    n->right = pLeft;
    p->left = n;
    
    n->parent = p;
    

    if (pLeft != NULL) {
        pLeft->parent = n; 
    }
}

static int isLeftChild(RBMNode *n) {
    if (n == NULL) {
        return -1;
    }

    if (n->parent == NULL) {
        return -1;
    }

    return n->parent->left == n ? 1 : 0;
}

static int isRightChild(RBMNode *n) {
    if (n == NULL) {
        return -1;
    }

    if (n->parent == NULL) {
        return -1;
    }

    return n->parent->left == n ? 0 : 1;
}

/**
 * @returns n->color iff n is not NULL, BLACK otherwise
 **/
static enum COLOR colorOf(RBMNode *n) {
    if (n == NULL) {
        return BLACK;
    } else {
        return n->color;
    }
}

/**
 * @returns uncle of this node or NULL iff the
 * uncle does not exist
 **/
static RBMNode* uncleOf(RBMNode *n) {
    // fetch parent
    RBMNode *parent = n->parent;
    if (parent == NULL) {
        return NULL;
    }

    // fetch grandparent
    RBMNode *gp = parent->parent;
    if (gp == NULL) {
        return NULL;
    }

    // get sibling of parent
    if (gp->right == parent) {
        return gp->left;
    } else {
        return gp->right;
    }
}

/**
 * @returns grandparent of this node or NULL iff the
 * grandparent does not exist
 **/
static RBMNode* gpOf(RBMNode *n) {
    RBMNode *parent = n->parent;
    if (parent == NULL) {
        return NULL;
    } else {
        return parent->parent;
    }
}

/** @override */
KVPair* RBMDelete(RedBlackMap *map, void *key) {

}

/** @override */
void* RBMSearch(RedBlackMap *map, void *key) {
  return NULL;
}

void* RBMReplace(RedBlackMap *map, void *key, void *val) {

}

/** @override */
void RBMDestroy(RedBlackMap *map) {

}

/** @override */
void RBMDestroyAndFree(RedBlackMap *map, destructKey dKey, destructVal dVal) {

}
