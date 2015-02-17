
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
vector<int> results;


int iteration = 0;

mutex shared;

void run(int n )
{
	while(iteration<workers.size()-1)
	{
		shared.lock();
		results.push_back(sa2a(sequence[iteration]));
		iteration+=1;
		shared.unlock();
	}

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
	while(iteration<workers.size()-1)
	{
		shared.lock();
		if(results.size()!=0)
		{
			cout <<"sa2a (" << sequence[iteration] <<") = "<<results[iteration];
		}
		results.pop_back();
		shared.unlock();
	}
	for(int i = 0; i<workers.size()-1; i++)
	{
		workers[i].join();
	}
	return 0;
}