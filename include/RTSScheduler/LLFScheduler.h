#pragma once


#include <RTSScheduler/Scheduler.h>
class LLFScheduler : public Scheduler
{
public:
	LLFScheduler() : Scheduler()
	{}

	virtual bool comparePriority(Task& lhs, Task& rhs) override;
};