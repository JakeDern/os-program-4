#ifndef _537MALLOC
#define _537MALLOC
#include <stddef.h>
#include "./types/RedBlackMap.h"

static RedBlackMap *allocMap = newRedBlackMap(NULL);
static RedBlackMap *freeMap = newRedBlackMap(NULL);

void *malloc537(size_t size);

void free537(void *ptr);

void *realloc537(void *ptr, size_t size);

void memcheck537(void *ptr, size_t size);

#endif