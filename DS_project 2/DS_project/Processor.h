//
//  Processor.hpp
//  DS_Project
//
//  Created by Youssef Bahy on 11/04/2023.
//
#pragma once


class Scheduler;

#include "PriorityQueue.h"
#include "Process.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>



class Processor
{
protected:
	//LinkedQueue<Process*>* RDY;
	int End_Time;
	Process* RUN;
	Scheduler *Mest;
	int Busy_Time;
	int Idle_Time;
	int TotalTime; // calculate total time of processor
	int Load;
	int Utiliz;
	


public:

	Processor(Scheduler *ptr);
	~Processor();
	int get_IDLE_time();
	int get_BUSY_time();

	virtual bool IsEmpty() = 0;
	virtual bool IsIdle()=0;
	bool IsFree();
	virtual void move_RDY_RUN() = 0;
	virtual void AddProcess(Process* p) = 0;
	virtual void ScheduleAlgo()=0;
	virtual void PrintRDY() = 0;
	void PrintRUN();
	int CheckRUN();
	int get_putil();
	virtual int get_size() = 0;

	int getEnd_Time();
	virtual Process* StealFront() = 0;
};

