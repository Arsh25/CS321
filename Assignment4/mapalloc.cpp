#include "mapalloc.h"
#include<iostream>
#include<vector>

using std::vector;

size_t lastSize;

/* allocatedBlocks keeps track of the starting addresses of all allocated blocks
   allocatedSizes keeps track of the corresponding blocks size
*/
vector<void *> allocatedBlocks;
vector<size_t> allocatedSizes;

int count = 0;


void *mapalloc( const size_t size)
{
	void * addr = mmap(nullptr,size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	allocatedBlocks.push_back(addr); // Add starting address to vector keeping track of allocated blocks 
	allocatedSizes.push_back(size); // Add the size of the memory block into the vector keeping track of sizes
	++count;
	lastSize = size;
	
	return addr;
}

void mapFree( void *block)
{
	int munmapSuccess = munmap( block, lastSize);
}

//Function to easily run multiple test cases. Only for debugging  
void test(size_t bytes)
{
	std::cout<<"Allocating Memory"<<std::endl;
	void * mem = mapalloc(bytes);
	if(mem !=MAP_FAILED)
	{
		std::cout<<"mmap succeeded"<<std::endl;
		std::cout<<"Starting Address ="<<allocatedBlocks.back()<<std::endl;
		std::cout<<allocatedSizes[count]<<std::endl;
		
	}
	mapFree(mem);
	std::cout<<"Deallocation succeeded"<<std::endl;
}
int main()
{
	test(3);
	test(6);
	test(32);
	test(12);
	test(10);
	return 0;
}
		
