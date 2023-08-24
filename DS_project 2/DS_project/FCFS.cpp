
#include "FCFS.h"
#include "Schedular.h"
FCFS :: FCFS(Scheduler *ptr) : Processor(ptr)
{
	MaxW = ptr->getMaxW();
	processkilled = 0; 
}

void FCFS::AddProcess(Process* p) //add process to linkedlist
{
	RDY.enqueue(p);
	End_Time += p->get_CT()-p->getExcu_time();
	p->set_Start(Mest->getCurrentTime());
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
	if(IsFree())
	{
		RDY.dequeue(RUN);
		int test = Mest->getCurrentTime() - RUN->get_AT();
		RUN->set_RT(Mest->getCurrentTime() - RUN->get_AT());
		RUN->set_WT(Mest->getCurrentTime()-RUN->get_Start());
		End_Time -= RUN->get_CT()-RUN->getExcu_time();
	}
}

void FCFS::PrintRDY()
{
	RDY.Print();
}

int FCFS::get_size()
{
	return RDY.get_size();
}
void FCFS:: ScheduleAlgo()
{
	//TODO
	move_RDY_RUN();
	Mest->IO_Handl(RUN);
	move_RDY_RUN();
	
	if (RUN && RUN->IsComplete())
	{
		//Add to TRM List  Process Completion
		Mest->move_TO_TRM(RUN);
		
		RUN = nullptr;	
		move_RDY_RUN();
	}
	if (RUN && Mest->CheckForking())
		Mest->ForkTreeAlgo(RUN);
	while (Mest->migrate2(RUN))
	{
		move_RDY_RUN();
	}
	if (RUN)
	{
		RUN->updateExcu_time();
	}
	if (IsIdle())
	{
		Idle_Time++;
	}
	else
	{
		Busy_Time++;

	}
}


void FCFS::Kill(int Killed_Id)
{
	if(RUN && RUN->get_PID()==Killed_Id)
	{
		Mest->move_TO_TRM(RUN);
		RUN = NULL;
	}
	Process *p = NULL;
	if(RDY.DeleteById(Killed_Id,p))
	{
		End_Time -= p->get_CT()-p->getExcu_time();
		p->set_WT(Mest->getCurrentTime()-p->get_Start());
		Mest->move_TO_TRM(p);
	}
	processkilled++;
	Mest->set_process_killed(processkilled);
}
Process* FCFS::StealFront()
{

	Process* Front= RDY.getFisrtUnForked();
	if(Front)
	{
		DeleteFront(Front);
		return Front;
	}
	return NULL;
}
void FCFS::DeleteFront(Process* Front)
{
	RDY.dequeue(Front);
	End_Time -= Front->get_CT();
}
bool FCFS::IsIdle()
{

	return !RUN && RDY.isEmpty();
}