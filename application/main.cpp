
#include <RTSScheduler/RMScheduler.h>

int main()
{
	TaskInfo t1 = { 0 };
	t1.period = 5;
	t1.exeTime = 2;
	
	TaskInfo t2 = { 0 };
	t2.period = 10;
	t2.exeTime = 3;

	TaskInfo t3 = { 0 };
	t3.period = 4;
	t3.exeTime = 1;

	std::vector<TaskInfo> tasks = { t1, t2, t3 };
	RMScheduler sched;
	Scheduler* abssched = &sched;

	abssched->loadTasks(tasks);
	float check = abssched->feasibilityCheck();
	abssched->schedule();

	return 0;
}