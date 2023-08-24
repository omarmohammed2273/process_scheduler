#include "UI.h"
#include"windows.h"
void UI::choose_mode()
{
	cout << "Choose Mode" << endl;
	cout << "1)Interactive Mode" << endl;
	cout << "2)Step By Step Mode" << endl;
	cout << "3)Silent Mode" << endl;
	cin >> mode_number;
}

UI::UI()
{
	flag = 0;
	choose_mode();
}

void UI::printUI(int time_step,Processor** pList, int FCFS_N, int  SJF_N, int RR_N, LinkedQueue <Process*>* BLK_LIST, LinkedQueue <Process*>* TRM_LIST)
	{
	cout << "Currnt Timestep:" << time_step << endl;
	if (time_step == 57)
		int x = 0;
	cout << "-------------" << "\t" << "RDY processes" << "\t"<< "-------------" << endl;
	int k = 0;
	int n_trm = 0;
	for (int i = 0; i < FCFS_N; i++)
		{

		cout << "processor "<<k<<" [FCFS]: "<< pList[k]->get_size() << " RDY:";
		pList[k]->PrintRDY();
		
		cout << endl;
		k++;
		}
	for (int i = 0; i < RR_N; i++)
	{

		cout << "processor " << k << " [RR]: " << pList[k]->get_size() << " RDY:";
		pList[k]->PrintRDY();
		
		cout << endl;
		k++;
	}
	for (int i = 0; i < SJF_N; i++)
		{
		
		cout << "processor "<<k<<" [SJF]: " << pList[k]->get_size() << " RDY:";
		pList[k]->PrintRDY();
	
		cout << endl;
	
		k++;
		}
	

	cout << "-------------" << "\t" << "BLK processes" << "\t" << "-------------" << endl;
	cout << BLK_LIST->get_size() << " BLK:"; 
	BLK_LIST->Print();

	cout << endl;
	for(int i=0;i<FCFS_N+SJF_N+RR_N;i++)
		n_trm += pList[i]->CheckRUN();
	k = 0;
	cout << "-------------" << "\t" << "RUN processes" << "\t" << "-------------" << endl;
	cout << n_trm << " RUN:";
	for (int i = 0; i < FCFS_N + SJF_N + RR_N; i++)
	{
		if (pList[i]->CheckRUN())
		{
			cout << " ";
			pList[i]->PrintRUN();
			cout << "(P" << i+1 << ")";
		}
	}

		cout << endl;


	cout << "-------------" << "\t" << "TRM processes" << "\t" << "-------------" << endl;
	cout << TRM_LIST->get_size() << " TRM:";
	TRM_LIST->Print();

	cout << endl;
	

	}

void UI::UI_Mode(int time_step, Processor** pList, int FCFS_N, int  SJF_N, int RR_N, LinkedQueue <Process*>* BLK_LIST, LinkedQueue <Process*>* TRM_LIST)
{
	if (mode_number == 1)
	{
		//cout << "PRESS ANY KEY TO MOVE TO NEXT STEP " << endl;
		printUI(time_step, pList, FCFS_N, SJF_N, RR_N, BLK_LIST, TRM_LIST);
		
		cout << "PRESS ANY KEY TO MOVE TO NEXT STEP " << endl;
		char c;
		cin >> c;
	}
	else if (mode_number == 2)
	{
		printUI(time_step, pList, FCFS_N, SJF_N, RR_N, BLK_LIST, TRM_LIST);
		Sleep(1000);
	}
	else
	{
		if (!flag)
		{
			cout << "Silent Mode................ \t Simulation Starts..." << endl;
			cout << "Simulation ends, Output file created" << endl;
		}
		flag = 1;
	}
}