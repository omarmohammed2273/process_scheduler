
#include "Processor.h"
#include "Schedular.h"

Processor::Processor(Scheduler *ptr)
{
	Mest = ptr;
	RUN = nullptr;
	End_Time = 0;
}
Processor::~Processor()
{
	if(RUN != nullptr)
		delete RUN;
}

bool Processor::IsIdle()
{
	return !RUN;
}


int Processor::Gene_Rand()
{
	srand(time(NULL));
	return rand()%100 + 1;
}

void Processor::SimpleSimulate()
{
	int prob = Gene_Rand();
	if(IsIdle())
		return ;
	if(prob>=1 && prob<=15)
	{
		Mest->move_TO_BLK(RUN);
		RUN = nullptr;
	}else if(prob>=20 && prob<=30)
	{
		Mest->move_TO_RDY(RUN);
		RUN = nullptr;
	}else if(prob>=50 && prob<=60)
	{
		Mest->move_TO_TRM(RUN);
		RUN = nullptr;
	}

}


void Processor::PrintRUN()
{
	if(RUN)
		cout<<RUN->get_PID();
	return ;
}

int Processor::CheckRUN()
{
	if(RUN==nullptr)
		return 0;
	return 1;
}