# @author Jake Dern netid: dern2 cslogin: dern
# @author Alex Dallman netid: adallman2 cslogin: adallman

CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = runner
SCAN_BUILD_DIR = scan-build-out
EXTRA_FLAGS = -g

all: AVLNode.o AVLMap.o advanced_testcase1.o 537malloc.o
	$(CC) -o $(EXE) AVLNode.o AVLMap.o 537malloc.o advanced_testcase1.o $(WARNING_FLAGS) $(EXTRA_FLAGS)

advanced_testcase1.o: ./advanced_testcase1.c
	$(CC) -c ./advanced_testcase1.c $(WARNING_FLAGS) $(EXTRA_FLAGS)

obj: 537malloc.o AVLNode.o AVLMap.o

537malloc.o: ./537malloc.c ./537malloc.h ./types/AVLMap.h
	$(CC) -c ./537malloc.c  $(WARNING_FLAGS) $(EXTRA_FLAGS)

AVLNode.o: ./types/AVLNode.c ./types/AVLNode.h  
	$(CC) -c ./types/AVLNode.c  $(WARNING_FLAGS) $(EXTRA_FLAGS)

AVLMap.o: ./types/AVLMap.c ./types/AVLMap.h
	$(CC) -c ./types/AVLMap.c $(WARNING_FLAGS) $(EXTRA_FLAGS)

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
