
#include<fstream>
#include<iostream>
#include "SJF.h"
#include "UI.h"
using namespace std;

struct SIGKILL
{
	int time;
	int PID;
	SIGKILL(int x,int y)
	{
		time = x;
		PID = y;
	}
};
enum
{
	All_Q,FCFS_Q,RR_Q,SJF_Q
};

class Scheduler
{
	Processor** PList;
	LinkedQueue <Process*>* NEW_LIST;
	LinkedQueue <Process*>* BLK_LIST;
	LinkedQueue <Process*>* TRM_LIST;
	int FCFS_N, SJF_N, RR_N, n, k, n_process;
	int RR_TimeSlice;
	int timestep;
	int ToT_Wait; //total waiting time for calculate average of waiting time
	int ToT_TRT; //total turnaround time for calculate average of turnaround time
	UI ui;
	LinkedQueue<SIGKILL*> SIGKILLs;
	int Fork_prob; 
	int StealLimit;
	int STL;
	int RTF;
	int MaxW;
	int ProcessRTF; // number of processes migration due to RTF
	int ProcessMaxW; // number of processes migration due to MaxW
	int ProcessSteal; // number of processes moved by steal
	int ProcessForked; // number of processes forked
	int ProcessKilled; // number of processes killed
	int ToT_Response;
	int MAX_ID;

public:
	Scheduler();
	~Scheduler();
	void open_input_file();
	void output_file();
	int get_percentage(int);
	void checkArrivalTime();
	void MakeProcessors();
	void move_RDY_RUN();
	void MakeDecision();
	void Schedule_System();
	bool IsFinished();
	void WorkStealing();
	void set_process_killed(int);
	float Steal_Limit(int LQF, int SQF);
	void Calc_LQF_SQF(Processor* &Longest, Processor* &Shortest);


	void move_TO_RDY(Process* p,int i);
	void move_TO_BLK(Process* p);
	void move_BLK_TO_RDY();
	void move_TO_TRM(Process* p);
	void IO_Handl(Process* &p);
	bool migrate1(Process* &p);
	bool migrate2(Process*& p);

	//getters
	int getCurrentTime();
	int getRTF();
	int getMaxW();

	//Fork
	bool CheckForking();
	void ForkTreeAlgo(Process* parent);
};

