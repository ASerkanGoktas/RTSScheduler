#pragma once


#include <RTSScheduler/Scheduler.h>
class LLFScheduler : public Scheduler
{
public:
	LLFScheduler() = default;
	~LLFScheduler() = default;

	virtual bool comparePriority(Task& lhs, Task& rhs) override;
};