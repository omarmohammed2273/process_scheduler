#pragma once

#include "Processor.h"
#include "LinkedProcess.h"
class FCFS : public Processor
{
private:
	LinkedProcess RDY;
	int MaxW;
	int ForkProb;
public:
    FCFS(Scheduler *ptr);
    void AddProcess(Process* p);
	bool IsEmpty();
	void move_RDY_RUN();
	void ScheduleAlgo(){}
	bool checkExit(int id);
    void Random_Move();
	virtual void PrintRDY();
	int get_size();
};










