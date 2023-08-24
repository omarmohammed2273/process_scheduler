#include "Process.h"
Process::Process()
{
	AT = 0;
	PID = 0;
	CT = 0;
	N = 0;
	IO_R = nullptr;
	IO_D = nullptr;
}
Process::Process(int at, int id, int ct, int n, int* io_r, int* io_d)
{

	AT = (at < 0) ? 0 : at;
	PID = (id < 0) ? 0 : id;
	CT = (ct < 0) ? 0 : ct;
	N = (n < 0) ? 0 : n;
	IO_R = io_r;
	IO_D = io_d;




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

int* Process::get_IO_D()
{
	return IO_D;
}
void Process::set_CT(int n)
{
	CT = n;
}
int Process::get_CT()
{
	return CT;
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


Process::~Process()
{
	if (IO_R != nullptr)
		delete[]IO_R;
	if (IO_D != nullptr)
		delete[]IO_D;
}


