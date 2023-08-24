#include "UI.h"

void UI::interactive_mode(int time_step,Processor** pList, int FCFS_N, int  SJF_N, int RR_N, LinkedQueue <Process*>* BLK_LIST, LinkedQueue <Process*>* TRM_LIST)
{
	cout << "Currnt Timestep:" << time_step << endl;
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
	for (int i = 0; i < SJF_N; i++)
	{

		cout << "processor "<<k<<" [SJF]: " << pList[k]->get_size() << " RDY:";
		pList[k]->PrintRDY();		
		cout << endl;
		k++;
	}
	for (int i = 0; i < RR_N; i++)
	{

		cout << "processor "<<k<<" [RR]: " << pList[k]->get_size() << " RDY:";
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
	for(int i=0;i<FCFS_N+SJF_N+RR_N;)
	{
		if(pList[i]->CheckRUN())
		{
			cout <<" ";
			pList[i]->PrintRUN();
			cout << "(P"<<i<<")";
		}
		int temp = pList[i]->CheckRUN();
		i++;
		if (i < FCFS_N + SJF_N + RR_N)
			if (pList[i]->CheckRUN()&&temp)
				cout << ",";		
	}
	cout << endl;
	cout << "-------------" << "\t" << "TRM processes" << "\t" << "-------------" << endl;
	cout << TRM_LIST->get_size() << " TRM:";
	TRM_LIST->Print();
	cout << endl;
	cout << "PRESS ANY KEY TO MOVE TO NEXT STEP " << endl;
	char c;
	cin >> c;

}