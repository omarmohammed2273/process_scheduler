
#ifndef SJF_hpp
#define SJF_hpp

#include"RR.h"
#include "PriorityQueue.h"
class SJF : public Processor
{
private:
    ProirityQueue<Process*> RDY;

public:
    SJF(Scheduler *ptr);
    void AddProcess(Process* p);
	bool IsEmpty();
	void move_RDY_RUN();
	void ScheduleAlgo(){}
    virtual void PrintRDY();
	
    int get_size();
};
#endif /* SJF_hpp */
