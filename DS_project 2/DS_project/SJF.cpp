//
//  SJF.cpp
//  DS_Project
//
//  Created by Youssef Bahy on 11/04/2023.
//

#include "SJF.h"
#include "Schedular.h"

SJF::SJF(Scheduler *ptr): Processor(ptr)
{
	
}
void SJF::ScheduleAlgo()
{
	//TODO
	move_RDY_RUN();
	Mest->IO_Handl(RUN);



	move_RDY_RUN();
	while(RUN && RUN->get_CT()==RUN->getExcu_time())
	{
		Mest->move_TO_TRM(RUN);
		RUN = NULL;
		move_RDY_RUN();
	}
	if(RUN)
	{
		RUN->updateExcu_time();
	}
	if (IsIdle())
		Idle_Time++;
	else
		Busy_Time++;
}


void SJF::AddProcess(Process* p)
{
	RDY.Insert(p,p->get_Priority());
	p->set_Start(Mest->getCurrentTime());
	End_Time += p->get_CT() - p->getExcu_time();
}

bool SJF::IsEmpty()
{
	return RDY.IsEmpty() && !RUN;
}

void SJF::move_RDY_RUN()
{
	if(RDY.IsEmpty())
		return ;
	if(IsFree())
	{
		RUN=RDY.Extract_Max().Item;
		RUN->set_RT(Mest->getCurrentTime() - RUN->get_AT());
		RUN->set_WT(Mest->getCurrentTime()-RUN->get_Start());
		End_Time -= RUN->get_CT()-RUN->getExcu_time();
	}
}
void SJF::PrintRDY()
{
	RDY.Print();
}

int SJF::get_size()
{
	return RDY.get_size();
}
Process* SJF::StealFront()
{
	Process* Front;
	DeleteFront(Front);
	return Front;
}
void SJF::DeleteFront(Process* &Front)
{
	priority_node<Process*>f;
	f=RDY.Extract_Max();
	Front = f.Item;
	End_Time -= Front->get_CT()-Front->getExcu_time();
}
bool SJF::IsIdle()
{
	return !RUN && RDY.IsEmpty();
}