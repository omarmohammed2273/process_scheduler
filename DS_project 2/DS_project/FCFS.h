//
//  FCFS.hpp
//  DS_Project
//
//  Created by Youssef Bahy on 11/04/2023.
//
#pragma once

#include "Processor.h"
#include "LinkedProcess.h"
class FCFS : public Processor
{
private:
	LinkedProcess RDY;
	int MaxW;
	int ForkProb;
	int processkilled;
public:
	int RTF;
	FCFS(Scheduler *ptr);
	void AddProcess(Process* p);
	bool IsEmpty();
	void move_RDY_RUN();
	void ScheduleAlgo();
	bool checkExit(int id);
	virtual void PrintRDY();
	int get_size();
	void Kill(int Killed_Id);
	void DeleteFront(Process* Front);
	virtual Process* FCFS::StealFront();
	virtual bool IsIdle();
};










