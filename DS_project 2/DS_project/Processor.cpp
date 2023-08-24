
#include "Processor.h"
#include "Schedular.h"

Processor::Processor(Scheduler *ptr)
{
	Idle_Time = 0;
	Busy_Time = 0;

	Mest = ptr;
	RUN = nullptr;
	End_Time = 0;
}
Processor::~Processor()
{
	if(RUN != nullptr)
		delete RUN;
}

int Processor::get_IDLE_time()
{
	return Idle_Time;
}
int Processor::get_BUSY_time()
{
	return Busy_Time;
}

bool Processor::IsFree()
{
	return !RUN;
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


int Processor::getEnd_Time()
{
	return End_Time;
}

