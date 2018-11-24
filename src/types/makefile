CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = runner
SCAN_BUILD_DIR = scan-build-out
EXTRA_FLAGS = 

all: RBNode.o RedBlackTree.o rbtree_runner.o
	$(CC) -o $(EXE) rbtree_runner.o RBNode.o RedBlackTree.o $(EXTRA_FLAGS)

rbtree_runner.o: rbtree_runner.c
	$(CC) $(WARNING_FLAGS) -c rbtree_runner.c $(EXTRA_FLAGS)

RBNode.o: ./RBNode.c ./RBNode.h  
	$(CC) $(WARNING_FLAGS) -c ./RBNode.c $(EXTRA_FLAGS)

RedBlackTree.o: ./RedBlackTree.c ./RedBlackTree.h
	$(CC) $(WARNING_FLAGS) -c ./RedBlackTree.c $(EXTRA_FLAGS)

clean:
	rm $(EXE) *.o

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
