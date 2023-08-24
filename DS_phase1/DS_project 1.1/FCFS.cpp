#include "FCFS.h"
#include "Schedular.h"

FCFS::FCFS(Scheduler *ptr) : Processor(ptr)
{}

void FCFS::AddProcess(Process* p) //add process to linkedlist
{
	RDY.enqueue(p);
}
bool FCFS::IsEmpty()
{
	bool val = RDY.isEmpty() && !RUN;
	return val;
}
void FCFS::move_RDY_RUN()
{
	if(RDY.isEmpty())
		return ;
	if(IsIdle())
	{
		RDY.dequeue(RUN);
	}
}

void FCFS::Random_Move()
{
	if(RDY.isEmpty())
		return ;
	Process* killed;
	int Rand_Id = rand()%100+1;
	while(!RDY.DeleteById(Rand_Id,killed))
		Rand_Id = rand()%100+1;
	Mest->move_TO_TRM(killed);

}
void FCFS::PrintRDY()
{
	RDY.Print();
}

int FCFS::get_size()
{
	return RDY.get_size();
}
