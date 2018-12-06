# Program 4: Safe malloc/free
A safe malloc/free library. This program operates in a similar fashion to valgrind by wrapping system calls to free, malloc, and realloc. The goal is to provide users with more detailed errors and warnings beyond the frusterating segfault. Additionally there is a provided "memcheck537" utility that will determine if if a provided starting address and range are safely within segments allocated by this library.

# Implementation
This library is implemented using two AVL trees. One tree tracks allocated pointers and the other tracks pointers which have been allocated and then freed by the library. When a system call to allocate/free is made, the library checks various error conditions like a double free by checking the list of pointers that have been freed before printing a detailed error message and exiting the program. When allocations are made the "free tree" is also checked for existing pointers with the same address which will be removed if there is a match. 

# Unresolved Clang warnings
There is a single unresolved clang warning which points to a possible null dereference in the left rotation code in our AVL tree implementation. This warning is claiming that a dereference is possible on a null node which is the second left child of the node that the rotation is being performed on ie x->left->left. This warning is technically correct that there is a danger of a seg fault here, but this code will not be ran unless the tree is of size at least 3 (as AVL trees need a height imbalance of > 1 to do rotations). This implies that x->left->left must not be null for this imbalance to exist, and the rotation to happen, and thus will not segfault.  

# Credits
General insertion and deletion algorithms for the tree, but not exact code, were taken from:

https://www.geeksforgeeks.org/avl-tree-set-1-insertion/ &nbsp
https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

Left/Right rotation algorithms/diagrams from this wikipedia article were used to write the code for rotations. Though no code was copied:

https://en.wikipedia.org/wiki/Tree_rotation

Additionally architecture ideas were taken from this geeksforgeeks article. Specifically the idea to return the new root of a rotated subtree from left/right rotation functions (as opposed to void return), and the idea to both delete and and fix in a top down fashion while the delete is in progress. This is in contrast to performing BST delete and then fixing from the bottom up afterwards, and makes for much neater code.

https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

