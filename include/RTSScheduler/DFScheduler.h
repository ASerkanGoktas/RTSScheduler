#pragma once

#include <RTSScheduler/Scheduler.h>
class DFScheduler : public Scheduler
{
public:
	DFScheduler() : Scheduler()
	{}

	virtual ~DFScheduler() = default;

	virtual bool comparePriority(Task& lhs, Task& rhs) override;
};