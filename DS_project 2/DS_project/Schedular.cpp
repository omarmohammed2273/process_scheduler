
#include "Schedular.h"

Scheduler::Scheduler()
{

	NEW_LIST = new LinkedQueue<Process*>;
	BLK_LIST = new LinkedQueue<Process*>;
	TRM_LIST = new LinkedQueue<Process*>;
	FCFS_N = 0;
	SJF_N = 0;
	RR_N = 0;
	n_process = 0;
	PList = nullptr;
	timestep = 1;
	k = 0;
	ProcessRTF=0; 
	ProcessMaxW=0; 
	ProcessSteal=0; 
	ProcessForked=0; 
	ProcessKilled=0; 
	MAX_ID = INT_MIN;
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

	ifstream fin("input_file7.txt");
	if (fin.fail())
	{
		cout << "can't open the file " << endl;
	}
	int* io_r = nullptr;
	int* io_d = nullptr;


	fin >> FCFS_N >> SJF_N >> RR_N;
	fin>>RR_TimeSlice;
	fin>>RTF>>MaxW>>STL>>Fork_prob;
	MakeProcessors();
	fin >> n_process;
	int at, id, ct, n;
	for (int i = 0; i < n_process; i++)
	{
		
		fin >> at >> id >> ct >> n;
		MAX_ID = max(MAX_ID, id);
		if (n > 0)
		{
			io_r = new int[n];
			io_d = new int[n];
			char t;
			for (int j = 0; j < n; j++)
			{
				fin >> t >> io_r[j] >> t >> io_d[j] >> t;
				if(j<n-1)
					fin>> t;
			}
		}

		Process* temp = new Process(at, id, ct, n, io_r, io_d,false);
		io_r = nullptr;
		io_d = nullptr;
		NEW_LIST->enqueue(temp);
	}
	int x,y;
	while(fin>>x>>y)
	{
		SIGKILL *signal = new SIGKILL(x,y);
		SIGKILLs.enqueue(signal);
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
	for (int i = 0; i < RR_N; i++)
	{
		PList[k++] = new RR(RR_TimeSlice, this);
	}
	for (int i = 0; i < SJF_N; i++)
	{
		PList[k++] = new SJF(this);
	}



}
void Scheduler::Schedule_System()
{
	checkArrivalTime(); //check if there is process arrived to move to RDY
	MakeDecision(); //make simple simulate to test the simulation
	SIGKILL *ptr;
	bool found=SIGKILLs.peek(ptr);
	if (timestep % STL == 0)
	{
		WorkStealing();
	}

	//Check
	if(found && timestep == ptr->time)
	{
		SIGKILLs.dequeue(ptr);
		for(int i=0;i<FCFS_N;i++)
		{
			((FCFS*)PList[i])->Kill(ptr->PID);
		}
	}

	move_BLK_TO_RDY(); //check if there is process in BLK and check probability to move to RDY
	ui.UI_Mode(timestep, PList, FCFS_N, SJF_N, RR_N, BLK_LIST, TRM_LIST);
	timestep++;
}
void Scheduler::WorkStealing()
{
	int LQF = INT_MIN, SQF = INT_MAX;
	Processor* Longest, * Shortest;
	Longest = PList[0];
	Shortest = PList[0];
	Calc_LQF_SQF(Longest, Shortest);
	LQF = Longest->getEnd_Time();
	SQF = Shortest->getEnd_Time();
	while (Steal_Limit(LQF, SQF) > 40)
	{
		Process *target = Longest->StealFront();
		if(target)
		{
			ProcessSteal++;
			Shortest->AddProcess(target);
			LQF = Longest->getEnd_Time();
			SQF = Shortest->getEnd_Time();
		}
		else
		{
			return;
		}
	}
}
float Scheduler::Steal_Limit(int LQF, int SQF)
{
	return ((float)(LQF - SQF) / (float)LQF) * 100;
}
void Scheduler::Calc_LQF_SQF(Processor* &Longest, Processor* &Shortest)
{
	int FinishTime;

	for (int i = 0; i < n; i++)
	{
		FinishTime = PList[i]->getEnd_Time();
		if (FinishTime > Longest->getEnd_Time())
		{
			Longest = PList[i];
		}
		if (FinishTime < Shortest->getEnd_Time())
		{
			Shortest = PList[i];
		}
	}
}
void Scheduler::checkArrivalTime()
{
	Process* p = nullptr;
	if (timestep == 75)
		int y = 0;
	while (NEW_LIST->peek(p) && timestep == p->get_AT()) //not if, pick all processes at each time step
	{
		NEW_LIST->dequeue(p);
		move_TO_RDY(p,0);
	}
}
void Scheduler::move_RDY_RUN()
{
	for(int i=0;i<n;i++)
		PList[i]->ScheduleAlgo();
}
void Scheduler::MakeDecision()
{
	for (int i = 0; i < n; i++)
		PList[i]->ScheduleAlgo();
}

//when probability 15% move from RDY to BLK

void Scheduler::move_TO_BLK(Process* p)
{
	BLK_LIST->enqueue(p);
	Process *top;
	BLK_LIST->peek(top);
	if(p!=top)
		p->set_Start(timestep);
}


void Scheduler::move_TO_RDY(Process* p,int i)
{
	int start, end;
	switch (i)
	{
	case 0: //Shortest in All Processors
		start = 0;
		end = n;
		break;
	case 1: //Shortest in only FCFS Processors
		start = 0;
		end = FCFS_N;
		break;
	case 2: //Shortest in only RR Processors
		start = FCFS_N;
		end = FCFS_N+RR_N;
		break;
	case 3: //Shortest in only SJF Processors
		start = FCFS_N + RR_N;
		end = n;
		break;
	default:
		start = 0;
		end = n;
		break;
	}
	if (!p) //if p is nullptr, ignore it
		return;
	int min_time = PList[start]->getEnd_Time();
	int i_of_list = start;
	for(int i=start+1;i<end;i++)
	{
		if(PList[i]->getEnd_Time()<min_time)
		{
			min_time = PList[i]->getEnd_Time();
			i_of_list = i;
		}
	}
	PList[i_of_list]->AddProcess(p);
	//PList[(k++) % n]->AddProcess(p);//time step %n
	p = nullptr;
}
void Scheduler::move_BLK_TO_RDY()
{
	if(BLK_LIST->isEmpty())
		return ;
	//Process* p = nullptr;

	Process* Front = BLK_LIST->getFrontPtr()->getItem();
	//IO_counter++;
	int* Dur = Front->get_IO_D();

	int i = Front->getIO_index();
	Dur[i]--;
	//TODO : check if i exceed # of IO_Request
	if (Dur[i] <= 0)
	{
		move_TO_RDY(Front,0);
		BLK_LIST->dequeue(Front);	
		BLK_LIST->peek(Front);
		Front->set_WT(timestep-Front->get_Start());
		Front = nullptr;
	}
}

void Scheduler::move_TO_TRM(Process* p)
{
	if (!p)
		return;
	Process* left = p->getleft();
	Process* right = p->getright();
	TRM_LIST->enqueue(p);
	p->set_TT(timestep);
	p->update_TRT();
	move_TO_TRM(left);
	move_TO_TRM(right);

}


void Scheduler::set_process_killed(int p)
{
	ProcessKilled = p;

}


void Scheduler::IO_Handl(Process* &p)
{
	if(p && p->check_IO_Request())
	{
		move_TO_BLK(p);
		p=NULL;
	}
	return;
}

bool Scheduler::migrate1(Process* &p)
{
	if (!p || SJF_N==0)
		return 0; //not false
	if(p->get_CT() - p->getExcu_time() < RTF)
	{
		ProcessRTF++;
		move_TO_RDY(p, SJF_Q);
		p = nullptr;
		return true;
	}
	return false;
}
bool Scheduler:: migrate2(Process*& p)
{
	if (!p || RR_N==0)
		return false;
	if (p->get_WT() > MaxW)
	{
		ProcessMaxW++;
		move_TO_RDY(p, RR_Q);
		p = nullptr;
		return true;
	}
	return false;
}





bool Scheduler::IsFinished()
{
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





int Scheduler:: getCurrentTime()
{
	return timestep;
}
int Scheduler::getMaxW()
{
	return MaxW;
}

int Scheduler:: getRTF()
{
	return RTF;
}

bool Scheduler::CheckForking()
{
	int Rand = rand() % 101;
	return (Rand < Fork_prob);
}	
void Scheduler::ForkTreeAlgo(Process* parent)
{
	if (parent->getleft() && parent->getright())
		return;
	int RT = parent->get_CT() - parent->getExcu_time();
	int unique_id = ++MAX_ID + 1000; //not always correct
	Process* child = new Process(timestep, unique_id, RT, 0, nullptr, nullptr, true);
	ProcessForked++;
	if (!parent->getleft())
	{
		parent->setleft(child);
		move_TO_RDY(child, FCFS_Q);
	}
	else if (!parent->getright())
	{
		parent->setright(child);
		move_TO_RDY(child, FCFS_Q);
	}
}
int Scheduler::get_percentage(int p)
{
	return ((float(p) / TRM_LIST->get_size()) * 100);
}
void Scheduler::output_file()
{
	ofstream fout("output_file7.txt");
	if (fout.fail())
	{
		cout << "can't open the file " << endl;
	}
	fout << "TT" << "\t" << "PID" << "\t"<<"AT"<<"\t" << "CT" << "\t" << "IO_D" << "\t" << "WT" << "\t" << "RT" << "\t" << "TRT" << endl;
	Process* temp;
	int sum_WT = 0, sum_RT = 0, sum_TRT = 0;
	int size_TRM_LIST = TRM_LIST->get_size();
	LinkedQueue <Process*>* TRM_TEMP;
	TRM_TEMP = new LinkedQueue<Process*>;
	while (TRM_LIST->dequeue(temp))
	{
		TRM_TEMP->enqueue(temp);
		sum_RT += temp->get_RT();
		sum_TRT += temp->get_TRT();
		sum_WT += temp->get_WT();
		fout << temp->get_TT();
		if (temp->get_TT() >= 10)
			fout << "\t";
		else
			fout << " \t";

		fout << temp->get_PID();
		if (temp->get_PID() >= 10)
			fout << " \t";
		else
			fout << "  \t";

		fout << temp->get_AT();
		if (temp->get_AT() >= 10)
			fout << "\t";
		else
			fout << " \t";
		fout << temp->get_CT();
		if (temp->get_CT() >= 10)
			fout << "\t";
		else
			fout << " \t";

		fout << temp->get_IO_D_total();
		if (temp->get_IO_D_total() >= 10)
			fout << "  \t";
		else
			fout << "   \t";
		fout << temp->get_WT();
		if (temp->get_WT() >= 10)
			fout << "\t";
		else
			fout << " \t";
		
		int test= temp->get_RT();
		int test2 = temp->get_PID();
		int test3 = temp->get_AT();
		fout << temp->get_RT();
		if (temp->get_RT() >= 10)
			fout << "\t";
		else
			fout << " \t";
		fout << temp->get_TRT();
		fout << endl;

	}
	while(!TRM_TEMP->isEmpty())
	{
		TRM_TEMP->dequeue(temp);
		TRM_LIST->enqueue(temp);
	}
	fout << endl;
	fout << "Processes: " << TRM_LIST->get_size() << endl;
	fout << "Ave WT = " << sum_WT / size_TRM_LIST << ", \t";
	fout << "Ave RT = " << sum_RT / size_TRM_LIST << ", \t";
	fout << "Ave TRT = " << sum_TRT / size_TRM_LIST << endl;
	fout << "Migration %: \t";
	fout << "RTF = " << get_percentage(ProcessRTF)<<"%, \t";
	fout << "MaxW = " << get_percentage(ProcessMaxW) << "%" << endl;
	fout << "Work Steal%: " << get_percentage(ProcessSteal) << "%" << endl;
	fout << "Forked Process: " << get_percentage(ProcessForked) << "%" << endl;
	fout << "Killed Process: " << get_percentage(ProcessKilled) << "%"<<endl<<endl;
	fout << "Processors:" << FCFS_N + SJF_N + RR_N << " [" << FCFS_N << " FCFS, " << SJF_N << " SJF, " << RR_N << " RR]" << endl;
	fout << "Processors Load" << endl;
	for (int i = 0; i < FCFS_N + SJF_N + RR_N; i++)
	{
		
		fout << "p" << i+1 << "=" << (float(PList[i]->get_BUSY_time())/(sum_TRT))*100<< "%, \t";
	}
	fout << endl << endl;
	fout << "Processors Utiliz" << endl;
	int sum = 0;
	for (int i = 0; i < (FCFS_N + SJF_N + RR_N); i++)
	{
		int pUtil = (float(PList[i]->get_BUSY_time()) / (PList[i]->get_IDLE_time() + PList[i]->get_BUSY_time())) * 100;
		sum += pUtil;
		fout << "p" << i+1 << "=" <<pUtil << "%, \t";
	}

	fout <<endl<< "Avg Utilization = " << sum/ (FCFS_N + SJF_N + RR_N) <<"%"<<endl;
	while (!TRM_LIST->isEmpty())
	{
		TRM_LIST->dequeue(temp);
	}



}