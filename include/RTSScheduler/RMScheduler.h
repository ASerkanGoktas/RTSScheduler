#include <RTSScheduler/Scheduler.h>

class RMScheduler : public Scheduler
{
        public:
                RMScheduler() : Scheduler()
                {}

				virtual bool comparePriority(Task& lhs, Task& rhs) override;
};