
#ifndef RR_hpp
#define RR_hpp

#include"FCFS.h"

class RR : public Processor
{
private:
	LinkedQueue<Process*> RDY;
	int Time_Slice;
	int RTF;

public:
	RR(int n, Scheduler *ptr);
	void AddProcess(Process* p);
	bool IsEmpty();
	void move_RDY_RUN();
	void ScheduleAlgo(){}
	virtual void PrintRDY();
	int get_size();
};
#endif
