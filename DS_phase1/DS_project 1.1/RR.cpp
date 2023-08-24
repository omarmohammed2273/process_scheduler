
#include "RR.h"
#include "Schedular.h"


RR::RR(int n, Scheduler *ptr):Processor(ptr)
{
	Time_Slice = n;

}

void RR::AddProcess(Process* p)
{
	RDY.enqueue(p);
}

bool RR::IsEmpty()
{
	return RDY.isEmpty() && !RUN;
}

void RR::move_RDY_RUN()
{
	if(RDY.isEmpty())
		return ;
	if(IsIdle())
	{
		RDY.dequeue(RUN);
	}
}
void RR::PrintRDY()
{
	RDY.Print();
}

int RR::get_size()
{
	return RDY.get_size();
}
