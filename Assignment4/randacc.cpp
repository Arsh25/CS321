/*Arsh Chauhan
 * Last Modified: 04/02/2015
 * randacc.cpp : random file access using mmap 
 * CS321 Assignment 4 Exercise B
*/



#include<iostream> // for cout, cin, endl
using std::cout;
using std::cin;
using std::endl;

#include<cstdlib> // for size_t
using std::size_t;

#include<string> // for std::string 
using std::string;

#include<unistd.h> // for _exit, write, close
#include<sys/mman.h> // for mmap, munmap, related constants
#include<fcntl.h> // for open, related constants
#include<sys/stat.h> // for stat, struct stat
#include<sys/types.h> // for off_t, ssize_t
#include<cerrno> // for errno 
#include<string.h> // for strerror



off_t getFileSize(const string & filepath)
{
	struct stat fileinfo;
	
	int fileSize = stat(filepath.c_str(), &fileinfo);
	
	if(fileSize == -1)
	{
		return -1;
	}
	
	return fileinfo.st_size;
	
	
}

// Close the file 
void closeFile(int fd)
{
	cout << "Closing File"<<endl;
	int closeFailed = close(fd);
	if(closeFailed)
	{
		cout <<" Failed to close file due to error: " << strerror(errno) << " Exiting"  <<endl;
		_exit(1);
	}
	else
	{
		cout<<" Close Suceeded " <<endl;
	}
}

//Read the requested records
void readFile(string & filepath)
{
	int record;
	off_t fileSize = getFileSize(filepath);
	int fd = open(filepath.c_str(),O_CREAT|O_RDONLY,0644);
	if(fd == -1)
	{
		cout << "Could not open file" << filepath <<" due to error: " << strerror(errno) << " Exiting"  <<endl;
		_exit(1);
	}
	
	int request;
	cout<< "Please enter a record index (0-99): "<<endl;
	cin >> request;
	void *addr = mmap(nullptr,fileSize,PROT_READ,MAP_SHARED,fd,0);
	
	
	if(addr == MAP_FAILED)
	{
		cout << "Failed to get memory to read file: exiting" <<endl;
		cout << "errno = " << strerror(errno) << endl;;
		closeFile(fd);
		_exit(1);
		
	}
	 
	 char*data = (char*)addr;
	 cout<< "Requested record is: "<<data[request]<<data[request+1] <<endl;
	 
	 closeFile(fd);
	
}

//Modify the requested record 
void modifyFile(string & filepath)
{
	const int SIZE = 200; //Size to write in bytes
	ssize_t dummy; 
	int fd = open(filepath.c_str(),O_CREAT|O_RDWR|O_APPEND,0644);
	if(fd == -1)
	{
		cout << "Could not open file" << filepath <<" due to error: " << strerror(errno) << " Exiting"  <<endl;
		_exit(1);
	}
	
	//Write intial content of file, If exits, then append to end of file 
	for(size_t i = 0;i < SIZE+10 ; i++)
	{
		dummy = write(fd, "-", 1);
	}
	dummy = write(fd, "\n", 1);
	
	
	void *addr = mmap(nullptr, getFileSize(filepath), PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	
	if(addr == MAP_FAILED)
	{
		cout << "Failed to get memory : Exiting" << endl;
		cout << "errno = " << strerror(errno) << endl;
		_exit(1);
	}
	
	off_t request; // User's requested index
	int data; // Record to be stored in the the requested index
	
	cout << "Enter Record to modify (0-99) : " << endl;
	cin >> request;
	cout << "Enter integer to be written at position " <<request << " : " << endl;
	cin >> data;
	
	
	if(request ==0)
	{
		off_t offset = lseek(fd, request, SEEK_SET); // + 1 as starting byte does not apply to first record (starts starts at byte 0)
	}
	
	off_t offset = lseek(fd, request+1, SEEK_SET); // seek to offset request+1 (2 bytes/ record -> starting byte of each record is record+1)
	
	write(fd,&data , 2);
	
	int munmapResult = munmap ( addr,getFileSize(filepath) );
	closeFile(fd);
	
}
	
// Display the actions menu 	
void menu(string & filepath)
{
	int choice;
	do
	{
		cout << "Please Select an action : " << endl;
		cout << "1:Read a record" << endl;
		cout << "2:Modify a record" << endl;
		cout <<"3:Quit" << endl;
		cin >>choice;
		switch (choice)
		{
		
			case 1: readFile(filepath); 
				break;
			case 2: modifyFile(filepath);
				break;
			case 3: _exit(1);
				break;
			default : cout<< "Please enter a valid choice" <<endl <<endl;
				break;
		}
	}
	while(choice!=3);
}
	
int main()
{
	string filepath = "randacc.txt";
	menu(filepath);

}
