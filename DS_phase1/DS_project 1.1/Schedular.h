
#include<fstream>
#include<iostream>
#include "SJF.h"
#include"UI.h";
using namespace std;

struct SIGKILL
{
	int time;
	int PID;
};


class Scheduler
{
	Processor** PList;
	LinkedQueue <Process*>* NEW_LIST;
	LinkedQueue <Process*>* BLK_LIST;
	Process* IO_Serv;
	LinkedQueue <Process*>* TRM_LIST;
	int FCFS_N, SJF_N, RR_N, n, k, n_process;
	int RR_TimeSlice;
	int timestep;
	int ToT_Wait; //total waiting time for calculate average of waiting time
	int ToT_TRT; //total turnaround time for calculate average of turnaround time
	int ToT_Response;
	UI ui;
	LinkedQueue<SIGKILL> SIGKILLs;
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

public:
	Scheduler();
	~Scheduler();
	void open_input_file();
	void checkArrivalTime();
	void MakeProcessors();
	void move_RDY_RUN();
	void MakeDecision();
	void Schedule_System();
	bool IsFinished();

	void Random_Kill();

	void move_TO_RDY(Process* p);
	void move_BLK_RDY();
	void move_TO_BLK(Process* p);
	void move_BLK_TO_RDY();
	void move_TO_TRM(Process* p);

};

