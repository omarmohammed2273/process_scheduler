#pragma once
#include<iostream>
using namespace std;
#include"LinkedQueue.h"
#include"Process.h"
#include"Processor.h"


class UI
{
	int mode_number;
	void print(Node<Process*>* p);
public:
	void interactive_mode(int,Processor**, int, int, int, LinkedQueue <Process*>* , LinkedQueue <Process*>* );
	
	//phase 2
	void choose_mode();
	void UI_Mode();
	void StepByStepMode();
	void SilentMode();
};

