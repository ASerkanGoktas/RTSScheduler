#pragma once
#include <RTSScheduler/Scheduler.h>

class RMScheduler : public Scheduler
{
        public:
			RMScheduler() = default;

				virtual ~RMScheduler() = default;

				virtual bool comparePriority(Task& lhs, Task& rhs) override;
};