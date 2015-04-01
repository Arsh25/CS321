#include "mapalloc.h"
#include<iostream>
size_t lastSize;

void *mapalloc( const size_t size)
{
	void * addr = mmap(nullptr,size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	lastSize = size;
	
	return addr;
}

void mapFree( void *block)
{
	int munmapSuccess = munmap( block, lastSize);
}

int main()
{
	std::cout<<"Allocating Memory"<<std::endl;
	void * mem = mapalloc(8);
	if(mem !=MAP_FAILED)
	{
		std::cout<<"mmap succeeded"<<std::endl;
	}
	mapFree(mem);
	std::cout<<"Deallocation succeeded"<<std::endl;
	return 0;
}
		
