#include <RTSScheduler/Scheduler.h>

class EDFScheduler : public Scheduler
{
public:
	EDFScheduler() : Scheduler()
	{}

	virtual bool comparePriority(Task& lhs, Task& rhs) override;
};