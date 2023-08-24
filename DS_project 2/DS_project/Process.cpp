#include "Process.h"
Process:: Process()
{
	AT = 0;
	PID = 0;
	CT = 0;
	N = 0;
	Excu_time = 0;
	IO_R = nullptr;
	IO_D = nullptr;
	left = nullptr;
	right = nullptr;

}
Process::Process(int at, int id, int ct, int n, int* io_r, int* io_d,bool child)
{

	AT = (at < 0) ? 0 : at;
	PID = (id < 0) ? 0 : id;
	CT = (ct < 0) ? 0 : ct;
	N = (n < 0) ? 0 : n;
	IO_R = io_r;
	IO_D = io_d;
	IO_index=0;
	Excu_time = 0;
	WT = 0;
	IsChild = child;
	Start = 0;
	left = nullptr;
	right = nullptr;
	RT = -1;
	TT = 0;
	TRT = 0;

}
int Process::get_AT()
{
	return AT;
}
int Process::get_N()
{
	return N;
}
int* Process::get_IO_R()
{
	return IO_R;

}
int  Process::get_IO_D_total()
{
	int IO_D_total = 0;

	for (int i = 0; i < N; i++)
	{
		IO_D_total += IO_D[i];
	}
	return IO_D_total;

}
int Process::get_TT()
{
	return TT;
}
int Process::get_TRT()
{
	return TRT;
}
int* Process::get_IO_D()
{
	return IO_D;
}
int Process::get_CT()
{
	return CT;
}
int Process::getExcu_time()
{
	return Excu_time;
}
int Process::get_PID()
{
	return PID;
}
ostream& operator<< (ostream& out,Process* ptr)
{
	out<<ptr->get_PID()<<" ";
	return out;
}

int Process::get_Priority()
{
	return INT_MAX-CT;
}


void Process::set_WT(int X)
{
	WT += X;
}
void Process::set_RT(int X)
{
	if(RT==-1)
	 RT = X;
}
int Process::get_RT()
{
	return RT;
}
void Process::update_TRT()
{
	TRT = TT - AT;
}
bool Process::check_IO_Request()
{
	if (!IO_D)
		return false;
	if(IO_index<N && Excu_time == IO_R[IO_index])
	{
		IO_index++;
		return true;
	}
	return false;
}
bool Process::IsComplete()
{
	return get_CT() == getExcu_time();
}
void Process::updateExcu_time()
{
	Excu_time++;
}

Process::~Process()
{
	if (IO_R != nullptr)
		delete[]IO_R;
	if (IO_D != nullptr)
		delete[]IO_D;
}
int Process:: get_WT()
{
	return WT;
}
int Process::getIO_index()
{
	return IO_index;
}
int Process::get_Start()
{return Start;}
bool Process::getIsChild()
{
	return IsChild;
}
void Process::set_Start(int x)
{
	Start = x;
}
void Process::set_TT(int x)
{
	TT = x;
}
void Process::setleft(Process*& l)
{
	left = l;
}
void Process::setright(Process*& r)
{
	right = r;
}
Process*& Process::getleft()
{
	return left;
}
Process*& Process::getright()
{
	return right;
}