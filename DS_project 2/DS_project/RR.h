//
//  RR.hpp
//  DS_Project
//
//  Created by Youssef Bahy on 11/04/2023.
//

#ifndef RR_hpp
#define RR_hpp

#include"FCFS.h"

class RR : public Processor
{
private:
    LinkedQueue<Process*> RDY;
	int Time_Slice;
	int RTF;
	int counter;  //Count Executed Time at RR RUN
public:
	RR(int n, Scheduler *ptr);
    void AddProcess(Process* p);
	bool IsEmpty();
	void move_RDY_RUN();
	void ScheduleAlgo();
	virtual void PrintRDY();
	int get_size();
	virtual Process* StealFront();
	void DeleteFront(Process* Front);
	virtual bool IsIdle();
};
#endif
