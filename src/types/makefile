CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = runner
SCAN_BUILD_DIR = scan-build-out
EXTRA_FLAGS = 

all: RBMNode.o RedBlackMap.o rbtree_runner.o
	$(CC) -o $(EXE) rbtree_runner.o RBMNode.o RedBlackMap.o $(EXTRA_FLAGS)

rbtree_runner.o: rbtree_runner.c
	$(CC) $(WARNING_FLAGS) -c rbtree_runner.c $(EXTRA_FLAGS)

RBMNode.o: ./RBMNode.c ./RBMNode.h  
	$(CC) $(WARNING_FLAGS) -c ./RBMNode.c $(EXTRA_FLAGS)

RedBlackMap.o: ./RedBlackMap.c ./RedBlackMap.h
	$(CC) $(WARNING_FLAGS) -c ./RedBlackMap.c $(EXTRA_FLAGS)

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
