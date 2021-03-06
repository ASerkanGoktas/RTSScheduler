#pragma once

typedef unsigned id_t;
typedef unsigned mtime_t;

struct TaskInfo
{
        mtime_t period = 0;
        mtime_t deadline = 0;
        mtime_t exeTime = 0;
        mtime_t dispatchTime = 0;
};

class Task
{

public:
		const TaskInfo m_info;
        Task(id_t taskid, TaskInfo info) : m_id(taskid), m_info(info)
        {
			remainingExe = info.exeTime;
			effectiveDeadline = (m_info.deadline == 0 ? m_info.period : m_info.deadline);
		}

        void cycle(mtime_t current_time)
        {    

                if((current_time % m_info.period) == 0)
                {
						instanceCount++;
                        remainingExe = m_info.exeTime;
						effectiveDeadline = current_time + (m_info.deadline == 0 ? m_info.period : m_info.deadline);
                }
        }

        void execute()
        {
                remainingExe--;
        }

        bool isFinished()
        {
                return remainingExe == 0;
        }

        bool isReady(mtime_t time)
        {
                return !isFinished() && (time > m_info.dispatchTime);
        }

		bool deadlineMiss(mtime_t time)
		{
			return (time > effectiveDeadline) && !isFinished();
		}

		unsigned getInstanceCount()
		{
			return instanceCount;
		}

		mtime_t getRemainingExe()
		{
			return remainingExe;
		}

		mtime_t getEffectiveDeadline()
		{
			return effectiveDeadline;
		}

		mtime_t getLaxity()
		{
			return laxity;
		}

private:
        id_t m_id;
        unsigned instanceCount = 0;
        mtime_t remainingExe = 0;
		mtime_t effectiveDeadline = 0;
		mtime_t laxity = 0;
};