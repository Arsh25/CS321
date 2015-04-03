/*Arsh Chauhan
  mapalloc.cpp implentation for CS321 Assignment 4 Exercise A
  Last Edited 4/1/2015
*/

#include "mapalloc.h"


#include<map> // for std::map

using std::size_t;
using std::map;


map<void *, size_t> memoryMapped;


void * Freeaddr = nullptr; // Starting Address of next free memory block



void *mapalloc( const size_t size)
{
	void * addr = mmap(Freeaddr,size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	if(addr==MAP_FAILED)
	{
		return nullptr;
	}
	else
	{ 
		Freeaddr = (void *)((char *)Freeaddr + size); // Offset the next free address pointer by 'size' bytes
		memoryMapped[addr] = size;
		return addr;
	}
}



void mapFree( void *block) 
{
	
	 int success = munmap( block, memoryMapped[block]);

}


		
