CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = runner
SCAN_BUILD_DIR = scan-build-out
EXTRA_FLAGS = -g

all: AVLNode.o AVLMap.o avltree_runner.o
	$(CC) -o $(EXE) avltree_runner.o AVLNode.o AVLMap.o $(EXTRA_FLAGS)

avltree_runner.o: avltree_runner.c
	$(CC) $(WARNING_FLAGS) -c avltree_runner.c $(EXTRA_FLAGS)

AVLNode.o: ./AVLNode.c ./AVLNode.h  
	$(CC) $(WARNING_FLAGS) -c ./AVLNode.c $(EXTRA_FLAGS)

AVLMap.o: ./AVLMap.c ./AVLMap.h
	$(CC) $(WARNING_FLAGS) -c ./AVLMap.c $(EXTRA_FLAGS)

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
