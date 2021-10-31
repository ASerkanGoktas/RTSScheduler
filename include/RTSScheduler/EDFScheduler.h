#pragma once

#include <RTSScheduler/Scheduler.h>

class EDFScheduler : public Scheduler
{
public:
	EDFScheduler() : Scheduler()
	{}

	virtual ~EDFScheduler() = default;

	virtual bool comparePriority(Task& lhs, Task& rhs) override;
};