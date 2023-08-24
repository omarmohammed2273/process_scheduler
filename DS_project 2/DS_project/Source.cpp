 //
//  main.cpp
//  DS_Project
//
//  Created by Youssef Bahy on 11/04/2023.
//


#include <iostream>
#include "Schedular.h"
int main()
{
	srand(time(NULL));
    Scheduler* Manager = new Scheduler;
    Manager->open_input_file();
	int counter = 0;
    while (!Manager->IsFinished())
    {
        Manager->Schedule_System();
		counter++;

    }


    Manager->output_file();
	delete Manager;
	
    return 0;
}
