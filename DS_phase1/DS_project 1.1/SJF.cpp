
#include "SJF.h"
#include "Schedular.h"

SJF::SJF(Scheduler *ptr): Processor(ptr)
{

}
void SJF::AddProcess(Process* p)
{
	RDY.Insert(p,p->get_Priority());
}

bool SJF::IsEmpty()
{
	return RDY.IsEmpty() && !RUN;
}

void SJF::move_RDY_RUN()
{
	if(RDY.IsEmpty())
		return ;
	if(IsIdle())
	{
		RUN=RDY.Extract_Max().Item;
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
