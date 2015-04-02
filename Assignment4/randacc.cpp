/*Arsh Chauhan
 * Last Modified: 04/02/2015
 * randacc.cpp : random file access using mmap 
*/



#include<iostream> // for cout, cin, endl
using std::cout;
using std::cin;
using std::endl;
#include<cstdlib> // for size_t
using std::size_t;
#include<string>
using std::string;
#include<unistd.h> // for _exit, write, close
#include<sys/mman.h> // for mmao, munmap, related constants
#include<fcntl.h> // for open, related constants
#include<sys/stat.h> // for stat, struct stat
#include<sys/types.h> // for off_t

//Possible debuggin includes only 
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
	
	cout <<"FileSize = " <<fileinfo.st_size << endl;
	return fileinfo.st_size;
	
	
}
void closeFile(int fd)
{
	cout << "Closing File"<<endl;
	int closeFailed = close(fd);
	if(closeFailed)
	{
		cout <<" Failed to close file: exiting  " <<endl;
		_exit(1);
	}
	else
	{
		cout<<" Close Suceeded " <<endl;
	}
}

void readFile(string & filepath)
{
	int record;
	off_t fileSize = getFileSize(filepath);
	int fd = open(filepath.c_str(),O_CREAT|O_RDWR,0644);
	if(fd == -1)
	{
		cout << "Could not open file" << filepath <<" exiting" <<endl;
		_exit(1);
	}
	
	int request;
	cout<< "Please enter a record index (0-99): "<<endl;
	cin >> request;
	void *addr = mmap(nullptr,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	
	if(addr == MAP_FAILED)
	{
		cout << "Failed to get memory to read file: exiting" <<endl;
		cout << "errno = " << strerror(errno) << endl;;
		closeFile(fd);
		_exit(1);
		
	}
	 
	 char *data = (char*)addr;
	 record = data[request];
	 cout<< "Requested record is: "<<record <<endl;

}

void modifyFile(string & filepath)
{
	int fd = open(filepath.c_str(),O_CREAT|O_RDWR,0644);
	if(fd == -1)
	{
		cout << "Could not open file" << filepath <<" exiting" <<endl;
		_exit(1);
	}
	
	void *addr = mmap(nullptr, getFileSize(filepath), PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	
	if(addr == MAP_FAILED)
	{
		cout << "Failed to get memory : Exiting" << endl;
		cout << "errno = " << strerror(errno) << endl;;
		_exit(1);
	}
	int request;
	int data;
	cout << "Enter Record to modify (0-99) : " << endl;
	cin >> request;
	cout << "Enter integer to be written at position " <<request << " : " << endl;
	cin >> data;
	char * p = (char *)addr;
	p[request] = data;
	
	closeFile(fd);
	int munmapResult = munmap ( addr,getFileSize(filepath) );
	
}
	
void menu(string & filepath)
{
	int choice;
	do
	{
		cout << "Please Select an action : " <<endl;
		cout << "1:Read a record" <<endl;
		cout << "2:Modify a record" <<endl;
		cout <<"3:Quit" <<endl;
		cin >>choice;
		switch (choice)
		{
		
			case 1: readFile(filepath); 
				break;
			case 2: modifyFile(filepath);
				break;
			case 3: _exit(1);
				break;
			default : cout<< "Please enter a valid choice" <<endl;
		}
	}
	while(choice!=3);
}
	
int main()
{
	string filepath = "randacc.bin";
	menu(filepath);
	
	
}
