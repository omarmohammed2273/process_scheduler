
#include "Schedular.h"

Scheduler::Scheduler()
{
	NEW_LIST = new LinkedQueue<Process*>;
	BLK_LIST = new LinkedQueue<Process*>;
	TRM_LIST = new LinkedQueue<Process*>;
	IO_Serv = nullptr;
	FCFS_N = 0;
	SJF_N = 0;
	RR_N = 0;
	n_process = 0;
	PList = nullptr;
	timestep = 1;
	k = 0;

}
Scheduler::~Scheduler()
{
	Process *del;
	while(!NEW_LIST->isEmpty())
	{
		NEW_LIST->dequeue(del);
		delete del;
	}
	delete NEW_LIST;
	while(!BLK_LIST->isEmpty())
	{
		BLK_LIST->dequeue(del);
		delete del;
	}
	delete BLK_LIST;
	while(!TRM_LIST->isEmpty())
	{
		TRM_LIST->dequeue(del);
		delete del;
	}
	delete TRM_LIST;
	for(int i=0;i<n;i++)
		delete PList[i];
	if(PList != nullptr)
		delete []PList;
}

void Scheduler::open_input_file()
{

	ifstream fin("input_file.txt");
	if (fin.fail())
	{
		cout << "can't open the file " << endl;
	}
	int* io_r = nullptr;
	int* io_d = nullptr;


	fin >> FCFS_N >> SJF_N >> RR_N;
	fin>>RR_TimeSlice;
	MakeProcessors();
	fin >> n_process;
	for (int i = 0; i < n_process; i++)
	{
		int at, id, ct, n;
		fin >> at >> id >> ct >> n;

		if (n > 0)
		{
			io_r = new int[n];
			io_d = new int[n];
			char t;
			for (int i = 0; i < n; i++)
			{
				fin >> t >> io_r[i] >> t >> io_d[i] >> t >> t;
			}
		}

		Process* temp = new Process(at, id, ct, n, io_r, io_d);
		io_r = nullptr;
		io_d = nullptr;
		NEW_LIST->enqueue(temp );
	}





}
//make processors form input file
void Scheduler::MakeProcessors()
{
	int k = 0;
	n = FCFS_N + SJF_N + RR_N;
	if(n<=0)
		return ;
	PList = new Processor * [n];
	for (int i = 0; i < FCFS_N; i++)
	{
		PList[k++] = new FCFS(this);
	}
	for (int i = 0; i < SJF_N; i++)
	{
		PList[k++] = new SJF(this);
	}
	for (int i = 0; i < RR_N; i++)
	{
		PList[k++] = new RR(RR_TimeSlice,this);
	}

}


void Scheduler::Schedule_System()
{

	checkArrivalTime(); //check if there is process arrived to move to RDY

	move_RDY_RUN(); //check if there is process in RDY and RUN is idle
	MakeDecision(); //make simple simulate to test the simulation
	move_BLK_TO_RDY(); //check if there is process in BLK and check probability to move to RDY
	Random_Kill(); // get random Id in RDY to termination
	ui.interactive_mode(timestep, PList, FCFS_N, SJF_N, RR_N, BLK_LIST, TRM_LIST);
	timestep++;
}

void Scheduler::checkArrivalTime()
{
	Process* p = nullptr;
	while (NEW_LIST->peek(p) && timestep == p->get_AT()) //not if, pick all processes at each time step
	{
		NEW_LIST->dequeue(p);
		move_TO_RDY(p);
	}
}
void Scheduler::move_RDY_RUN()
{
	for(int i=0;i<n;i++)
		PList[i]->move_RDY_RUN();
}
void Scheduler::MakeDecision()
{
	for(int i=0;i<n;i++)
		PList[i]->SimpleSimulate();
}

//when probability 15% move from RDY to BLK

void Scheduler::move_TO_BLK(Process* p)
{
	BLK_LIST->enqueue(p);
}


void Scheduler::move_TO_RDY(Process* p)
{

	if (!p) //if p is nullptr, ignore it
		return;
	PList[(k++) % n]->AddProcess(p);//time step %n
	p = nullptr;
}
void Scheduler::move_BLK_TO_RDY()
{
	if(BLK_LIST->isEmpty())
		return ;
	Process* p = nullptr;
	int prob = rand()%100+1;
	if (prob <= 10)
	{
		BLK_LIST->dequeue(p);
		move_TO_RDY(p);
		p = nullptr;
	}
}

void Scheduler::move_TO_TRM(Process* p)
{
	TRM_LIST->enqueue(p);
}

void Scheduler::Random_Kill()
{
	for(int i=0;i<FCFS_N;i++)
		((FCFS*)PList[i])->Random_Move();
}


bool Scheduler::IsFinished()
{
	//check RDYLIST , BLKLIST , NEWLIST ,TRMLIST

	//check all RDYLISTS
	if(n==0)
		return true;
	for (int i = 0; i < n; i++)
	{
		if (!PList[i]->IsEmpty())
			return false;
	}
	bool check1 = BLK_LIST->isEmpty() && NEW_LIST->isEmpty() && !TRM_LIST->isEmpty();
	bool check2 =  BLK_LIST->isEmpty() && NEW_LIST->isEmpty() && TRM_LIST->isEmpty();
	return check1||check2;
}	
