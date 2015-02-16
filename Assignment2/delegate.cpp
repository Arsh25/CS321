
#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

#include"sa2a.h"

using std::thread;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::mutex;

vector<thread> workers(6);
vector<unsigned int> sequence;

void run(int n )
{

}

int main()
{
	
	
	unsigned int lastNum;
	
	do 
	{
		cout << "Enter a positive integer (or 0 to end input) : "; 
		cin >> lastNum;
		cout << endl;
		if(lastNum >0 )
			sequence.push_back(lastNum);
	}
	while(lastNum>0); //FIXME: Handle Negative values 

	for(int i = 0;i < workers.size(); i++)
	{
		try
		{
			workers[i] = thread(run,i);
		}
	
		catch(...)
		{
			cout <<"ERROR: Thread Creation Failed";
			exit(1);
		}
	}
	return 0;
}