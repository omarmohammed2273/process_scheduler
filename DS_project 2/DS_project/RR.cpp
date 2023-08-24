//
//  RR.cpp
//  DS_Project
//
//  Created by Youssef Bahy on 11/04/2023.
//

#include "RR.h"
#include "Schedular.h"


RR::RR(int n, Scheduler *ptr):Processor(ptr)
{
	Time_Slice = n;
	counter=0;
	RTF = ptr->getRTF();
	End_Time = 0;
}

void RR::AddProcess(Process* p)
{
	RDY.enqueue(p);
	End_Time += p->get_CT() - p->getExcu_time();
	p->set_Start(Mest->getCurrentTime());
}

bool RR::IsEmpty()
{
	return RDY.isEmpty() && !RUN;
}

void RR::move_RDY_RUN()
{

	if(RDY.isEmpty())
		return ;
	if(IsFree())
	{
		counter=0;
		RDY.dequeue(RUN);
		RUN->set_RT(Mest->getCurrentTime() - RUN->get_AT());
		RUN->set_WT(Mest->getCurrentTime()-RUN->get_Start());
		End_Time -= RUN->get_CT()-RUN->getExcu_time();
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
void RR :: ScheduleAlgo()
{
	//TODO
	move_RDY_RUN();
	Mest->IO_Handl(RUN);


	move_RDY_RUN();

	move_RDY_RUN();
	if(!RUN)
		return;
	if(RUN->getExcu_time()==RUN->get_CT())
	{
		Mest->move_TO_TRM(RUN);
		
		RUN = nullptr;	
		move_RDY_RUN();
	}
	if(counter==0)
	{
		while (Mest->migrate1(RUN))
		{
			move_RDY_RUN();
		}
	}
	if(RUN)
	{
		if(counter && counter%Time_Slice==0)
		{

			AddProcess(RUN);
			RUN=nullptr;
			move_RDY_RUN();
		}else
		{
			counter++;
			RUN->updateExcu_time();
		}
	}
	if (IsIdle())
		Idle_Time++;
	else
		Busy_Time++;
}
Process* RR::StealFront()
{

	Process* Front = RDY.getFrontPtr()->getItem();
	DeleteFront(Front);
	return Front;
}
void RR::DeleteFront(Process* Front)
{

	RDY.dequeue(Front);
	End_Time -= Front->get_CT()-Front->getExcu_time();
}
bool RR::IsIdle()
{
	return !RUN && RDY.isEmpty();
}

