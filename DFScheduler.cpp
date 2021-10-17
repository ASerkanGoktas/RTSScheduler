#include <RTSScheduler/DFScheduler.h>

bool DFScheduler::comparePriority(Task& lhs, Task& rhs)
{
	mtime_t lhs_deadline = lhs.m_info.deadline == 0 ? lhs.m_info.period : lhs.m_info.deadline;
	mtime_t rhs_deadline = rhs.m_info.deadline == 0 ? rhs.m_info.period : rhs.m_info.deadline;
	return lhs_deadline < rhs_deadline;
}