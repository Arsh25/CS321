/*
	Arsh Chauhan
	CS321 Assignment 2
	delegate.cpp: Multithreaded Implementation for sa2a.h
	Modified: 2/17/2015

*/


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
using std::lock_guard;

vector<thread> workers(6);
vector<unsigned int> sequence;
vector<int> results;


int iteration = 1;
int totalIterations;
bool print = false;

mutex shared;

void run(int n )
{
	lock_guard<mutex> count_guard(shared);{
	while(iteration!=totalIterations)
	{
		{
			
			results[iteration-1] = (sa2a(sequence[iteration-1]));
			cout <<"sa2a (" << sequence[iteration-1] <<") = "<<results[iteration-1]<<endl;;
			if(iteration<totalIterations)iteration++;
			print = true;
		}
	}}

}

int main()
{
	
	
	int lastNum;
	
	do 
	{
		
		cout << "Enter a positive integer (or 0 to end input) : "; 
		cin >> lastNum;
		cout << endl;
		if(lastNum >0 )
			sequence.push_back(lastNum);
		if(lastNum<0)
			cout<<" Only Positive numbers allowed " << endl;
	}
	while(lastNum!=0); 
	//cout <<"Size of seqence :"<<sequence.size();
	totalIterations = sequence.size();
	results.resize(totalIterations);
	for(int i = 1;i < workers.size(); i++)
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
	static int outputsPrinted = 0;
	lock_guard<mutex> count_guard(shared);{
	while(outputsPrinted!=totalIterations){
	if(print)
	{
		
		
		
			{
				cout <<"sa2a (" << sequence[iteration-1] <<") = "<<results[iteration-1];
				print = false;
				outputsPrinted++;
			}
			
		}}}
	
	for(int i = 1; i<workers.size(); i++)
	{
		workers[i].join();
	}
	return 0;
}