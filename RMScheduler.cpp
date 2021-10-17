#include <RTSScheduler/RMScheduler.h>


bool RMScheduler::comparePriority(Task& lhs, Task& rhs)
{
	return lhs.m_info.period < rhs.m_info.period;
}