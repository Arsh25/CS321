#include "mapalloc.h"
#include<iostream>
#include<vector>
#include<map> // for std::map

using std::size_t;
using std::map;



/*struct memoryAllocated
{
	void * _startAddress;
	size_t _size;
};

using std::vector;*/




int count = 0;
//vector <memoryAllocated> memoryMapped;
//vector<memoryAllocated>::iterator it;
map<void *, size_t> memoryMapped;


void * Freeaddr = nullptr;



void *mapalloc( const size_t size)
{
	void * addr = mmap(Freeaddr,size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	if(addr==MAP_FAILED)
	{
		return nullptr;
	}
	else
	{ 
		Freeaddr = (void *)((char *)Freeaddr + size);
		memoryMapped[addr] = size;
		return addr;
	}
	
	
	
	
}



void mapFree( void *block) // Change the memory size
{
	
	 int success = munmap( block, memoryMapped[block]);
	 if(!success) std::cout << "Deallocation Succeeded" <<std::endl;
}

//Function to easily run multiple test cases. Only for debugging  
void test(size_t bytes)
{
	std::cout<<"Allocating Memory"<<std::endl;
	void * mem = mapalloc(bytes);
	if(mem !=nullptr)
	{
		std::cout<<"mmap succeeded"<<std::endl;
		std::cout<<"Starting Address ="<<Freeaddr<<std::endl;
	}
	mapFree(mem);
}
int main()
{
	for(int i=0;i<100000;i++)
	{
		test(i);
	}
	return 0;
}
		
