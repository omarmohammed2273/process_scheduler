//
//  SJF.hpp
//  DS_Project
//
//  Created by Youssef Bahy on 11/04/2023.
//

#ifndef SJF_hpp
#define SJF_hpp

#include"RR.h"
#include "PriorityQueue.h"
class SJF : public Processor
{
private:
    //LinkedQueue<Process*> RDY;
    ProirityQueue<Process*> RDY;

public:
    SJF(Scheduler *ptr);
    void AddProcess(Process* p);
	bool IsEmpty();
	void move_RDY_RUN();
	void ScheduleAlgo();
    virtual void PrintRDY();
    virtual Process* StealFront();
    void DeleteFront(Process* &Front);
    int get_size();
    virtual bool IsIdle();
};
#endif /* SJF_hpp */
