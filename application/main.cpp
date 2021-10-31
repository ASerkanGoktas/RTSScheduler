
#include <RTSScheduler/EDFScheduler.h> //earliest deadline first
#include <RTSScheduler/DFScheduler.h> // Deadline first
#include <RTSScheduler/RMScheduler.h> // Rate Monotonic
#include <RTSScheduler/LLFScheduler.h> // Least Laxity first
#include <RTSScheduler/Scheduler.h>

#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "example launch: application tasks.txt" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);

	std::string schedulerName;
	int taskcount;
	mtime_t endtime;

	std::getline(input, schedulerName);
	input >> taskcount;
	input >> endtime;

	std::vector<TaskInfo> tasks;

	for (int i = 0; i < taskcount; i++)
	{
		TaskInfo t;
		input >> t.dispatchTime;
		input >> t.period;
		input >> t.exeTime;
		input >> t.deadline;
		tasks.push_back(t);
	}


	Scheduler* abssched;

	if (schedulerName == "EDF")
	{
		abssched = dynamic_cast<Scheduler*>(new EDFScheduler());
	}
	else if (schedulerName == "LLF")
	{
		abssched = dynamic_cast<Scheduler*>(new LLFScheduler());
	}
	else if (schedulerName == "RM")
	{
		abssched = dynamic_cast<Scheduler*>(new RMScheduler());
	}
	else if (schedulerName == "DF")
	{
		abssched = dynamic_cast<Scheduler*>(new DFScheduler());
	}
	else
	{
		std::cout << "unknown scheduler name!: " << schedulerName << std::endl;
		return 1;
	}

	abssched->loadTasks(tasks);
	abssched->schedule(endtime);

	delete abssched;

	return 0;
}