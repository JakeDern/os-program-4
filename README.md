# Program 4: Safe malloc/free
A safe malloc/free library. This program operates in a similar fashion to valgrind by wrapping system calls to free, malloc, and realloc. The goal is to provide users with more detailed errors and warnings beyond the frusterating segfault. Additionally there is a provided "memcheck537" utility that will determine if if a provided starting address and range are safely within segments allocated by this library.

# Implementation
This library is implemented using two AVL trees. One tree tracks allocated pointers and the other tracks pointers which have been allocated and then freed by the library. When a system call to allocate/free is made, the library checks various error conditions like a double free by checking the list of pointers that have been freed before printing a detailed error message and exiting the program. When allocations are made the "free tree" is also checked for existing pointers with the same address which will be removed if there is a match. 

# Credits
General insertion and deletion algorithms for the tree, but not exact code, were taken from:

https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

Left/Right rotation algorithms/diagrams from this wikipedia article were used to write the code for rotations. Though no code was copied:

https://en.wikipedia.org/wiki/Tree_rotation

Additionally architecture ideas were taken from this geeksforgeeks article. Specifically the idea to return the new root of a rotated subtree from left/right rotation functions (as opposed to void return), and the idea to both delete and and fix in a top down fashion while the delete is in progress. This is in contrast to performing BST delete and then fixing from the bottom up afterwards, and makes for much neater code.

https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

