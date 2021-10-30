#include <RTSScheduler/LLFScheduler.h>

bool LLFScheduler::comparePriority(Task& lhs, Task& rhs)
{
	return lhs.getEffectiveDeadline() < rhs.getEffectiveDeadline();
}