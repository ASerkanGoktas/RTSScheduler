
#include <RTSScheduler/EDFScheduler.h>

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "example launch: application tasks.txt" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);

	int taskcount;
	mtime_t endtime;
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

	EDFScheduler sched;
	Scheduler* abssched = &sched;

	abssched->loadTasks(tasks);
	abssched->schedule(endtime);

	return 0;
}