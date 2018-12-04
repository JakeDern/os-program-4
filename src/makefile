CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = runner
SCAN_BUILD_DIR = scan-build-out
EXTRA_FLAGS = 

all: AVLNode.o AVLMap.o avltree_runner.o advanced_testcase1.o 537malloc.o
	$(CC) -o $(EXE) avltree_runner.o AVLNode.o AVLMap.o 537malloc.o advanced_testcase1.o $(EXTRA_FLAGS)

advanced_testcase1.o: ./advanced_testcase1.c
	$(CC) $(WARNING_FLAGS) -c ./advanced_testcase1.c $(EXTRA_FLAGS)

537malloc.o: ./537malloc.c ./537malloc.h
	$(CC) $(WARNING_FLAGS) -c ./537malloc.c $(EXTRA_FLAGS)

avltree_runner.o: ./types/avltree_runner.c
	$(CC) $(WARNING_FLAGS) -c ./types/avltree_runner.c $(EXTRA_FLAGS)

AVLNode.o: ./types/AVLNode.c ./types/AVLNode.h  
	$(CC) $(WARNING_FLAGS) -c ./types/AVLNode.c $(EXTRA_FLAGS)

AVLMap.o: ./types/AVLMap.c ./types/AVLMap.h
	$(CC) $(WARNING_FLAGS) -c ./types/AVLMap.c $(EXTRA_FLAGS)

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
