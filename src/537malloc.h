#ifndef _537MALLOC
#define _537MALLOC
#include <stddef.h>
#include "./types/AVLMap.h"

void *malloc537(size_t size);

void free537(void *ptr);

void *realloc537(void *ptr, size_t size);

void memcheck537(void *ptr, size_t size);

#endif