#pragma once
#include<iostream>
using namespace std;
class Process
{
	int AT;//arrival time 
	int PID;// process id 
	int CT;// cpu time
	int N;// number of time the process request I/O
	int TT; //termination time
	int TRT; //turnaround time
	int WT; //waiting time
	int ResponseTime;
	int Start; //time of moving to ready list
	int* IO_R; int* IO_D; // N pairs of IO_R and IO_D for the process  
	Process* Child; //pointer for forking process
	int RemainTime; // remaining time of process
	bool IsInFCFS;


public:
	Process(int, int, int, int, int*, int*);
	Process();
	~Process();
	int  get_AT();
	int get_PID();
	friend ostream& operator<< (ostream& out,Process* ptr);
	void set_CT(int n);

	int get_CT();
	int get_N();
	int* get_IO_R();
	int* get_IO_D();
	int get_Priority(); //for Priority Queue

};

