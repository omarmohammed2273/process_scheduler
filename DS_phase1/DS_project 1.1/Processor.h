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
    int End_Time;
    Process* RUN;
	Scheduler *Mest;
	int Busy_Time; // calculate the time which Run is busy 
	int Idle_Time; // calculate the time which Run is Idle 
	int TotalTime; // calculate total time of processor
	int Load;
	int Utiliz;

public:
    Processor(Scheduler *ptr);
	~Processor();
    virtual bool IsEmpty() = 0;
    bool IsIdle();
	int Gene_Rand();
	virtual void move_RDY_RUN() = 0;
    virtual void AddProcess(Process* p) = 0;
    virtual void ScheduleAlgo()=0;
    virtual void PrintRDY() = 0;
	void PrintRUN();
	int CheckRUN();	
    virtual int get_size() = 0;
	void SimpleSimulate();
};

