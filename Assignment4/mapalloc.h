/*Arsh Chauhan
  mapalloc.h header for CS321 Assignment 4 Exercise A
  Last Edited 4/1/2015
*/



#ifndef MAPALLOC_H
#define MAPALLOC_H

#include<cstddef> // For std::size_t
#include<sys/mman.h> // For mmap, munmap and related constants  
using std::size_t;

// Allocate 'size' bytes using mmap
void *mapAlloc(const size_t size);

// Free previously allocated memory starting at address 'block'
void mapFree(void* block);

#endif
