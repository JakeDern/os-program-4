CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = runner
SCAN_BUILD_DIR = scan-build-out
EXTRA_FLAGS = -g

all: AVLNode.o AVLMap.o advanced_testcase2.o 537malloc.o
	$(CC) -o $(EXE) AVLNode.o AVLMap.o 537malloc.o advanced_testcase2.o $(EXTRA_FLAGS)

advanced_testcase2.o: ./advanced_testcase2.c
	$(CC) $(WARNING_FLAGS) -c ./advanced_testcase2.c $(EXTRA_FLAGS)

537malloc.o: ./537malloc.c ./537malloc.h
	$(CC) $(WARNING_FLAGS) -c ./537malloc.c $(EXTRA_FLAGS)

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
