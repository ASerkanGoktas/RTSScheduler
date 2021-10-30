#include <RTSScheduler/EDFScheduler.h>

bool EDFScheduler::comparePriority(Task& lhs, Task& rhs)
{
	return lhs.getEffectiveDeadline() < rhs.getEffectiveDeadline();
}