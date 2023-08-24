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
	int RT;
	int Start; //time of moving to ready list
	int* IO_R; int* IO_D; // N pairs of IO_R and IO_D for the process  
	Process* Child; //pointer for forking process
	int Excu_time; //time when the process in Run stat
	int IO_index;
	bool IsChild;
	
	//Fork Tree
	Process* left;
	Process* right;

public:
	Process(int, int, int, int, int*, int*,bool);
	Process();
	~Process();
	friend ostream& operator<< (ostream& out,Process* ptr);

	//setters
	void set_Start(int x);
	void updateExcu_time();
	void set_TT(int x);
	void set_WT(int x);
	void update_TRT();
	void set_RT(int);
	//getters
	int  get_AT();
	int get_PID();
	int get_CT();
	int getExcu_time();
	int get_WT();
	int get_N();
	int* get_IO_R();
	int* get_IO_D();
	int get_Priority(); //for Priority Queue
	int get_Start();
	int getIO_index();
	int  get_IO_D_total();
	int get_TRT();
	int get_TT();
	int get_RT();
	// Functions used in FCFS Scheduling Algorithm
	//void updateWaitingTime(int start, int end);
	bool check_IO_Request();
	bool getIsChild();
	bool IsComplete();
	//forking
	void setleft(Process*& l);
	void setright(Process*& r);
	Process*& getleft();
	Process*& getright();
};

