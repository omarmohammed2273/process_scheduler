#include <iostream>
#include "Schedular.h"
int main()
{

    Scheduler* Manager = new Scheduler;
    Manager->open_input_file();
    while (!Manager->IsFinished())
    {
        Manager->Schedule_System();
    }
	delete Manager;
	
    return 0;
}
