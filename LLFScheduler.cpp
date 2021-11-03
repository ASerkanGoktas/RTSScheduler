#include <RTSScheduler/LLFScheduler.h>

bool LLFScheduler::comparePriority(Task& lhs, Task& rhs)
{
	return (lhs.getEffectiveDeadline() - lhs.getRemainingExe() - this->getCurrentTime()) 
			< (rhs.getEffectiveDeadline() - rhs.getRemainingExe() - this->getCurrentTime());
}