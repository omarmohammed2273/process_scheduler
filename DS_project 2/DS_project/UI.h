#pragma once
#include <iostream>
using namespace std;
#include "LinkedQueue.h"
#include "Process.h"
#include "Processor.h"


class UI
{
	int flag;
	int mode_number;
	void printUI(int, Processor**, int, int, int, LinkedQueue <Process*>*, LinkedQueue <Process*>*);
	void choose_mode();
public:
	UI();
	
	void UI_Mode(int, Processor**, int, int, int, LinkedQueue <Process*>*, LinkedQueue <Process*>*);
	
};

