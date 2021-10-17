

typedef unsigned id_t;
typedef unsigned mtime_t;

struct TaskInfo
{
        mtime_t releaseTime;
        mtime_t period;
        mtime_t deadline;
        mtime_t exeTime;
        mtime_t dispatchTime;
};

class Task
{

public:
		const TaskInfo m_info;
        Task(id_t taskid, TaskInfo info) : m_id(taskid), m_info(info)
        {
			remainingExe = info.exeTime;
		}

        void cycle(mtime_t current_time)
        {
                if(remainingExe == 0)
                        instanceCount++;

                if((current_time % m_info.period) == 0)
                {
                        remainingExe = m_info.exeTime;
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
                return !isFinished() && (time >= m_info.dispatchTime);
        }

private:
        id_t m_id;
        unsigned instanceCount = 0;
        mtime_t remainingExe = 0;
};