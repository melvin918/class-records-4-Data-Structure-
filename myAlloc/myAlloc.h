#ifndef myAlloc_H
#define myAlloc_H
#include <stddef.h>

void *myAlloc (size_t node);

void myFree(void *ptr);

#endif //myAlloc_H