
#include <queue>
#include <numeric>
#include <RTSScheduler/Scheduler.h>
#include <sstream>

// Utility function to find
// GCD of 'a' and 'b'
mtime_t gcd(mtime_t a, mtime_t b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

// Returns LCM of array elements
mtime_t findlcm(std::vector< mtime_t >& arr)
{
	// Initialize result
	mtime_t ans = arr[0];

	// ans contains LCM of arr[0], ..arr[i]
	// after i'th iteration,
	for (int i = 1; i < arr.size(); i++)
		ans = (((arr[i] * ans)) /
		(gcd(arr[i], ans)));

	return ans;
}

Scheduler::Scheduler() : outputStream("outputStream.txt")
{
	
}

void Scheduler::loadTasks(std::vector < TaskInfo >& tasks)
{
	for (id_t i = 0; i < tasks.size(); i++)
	{
		TaskInfo& info = tasks[i];
		std::unique_ptr<Task> m(new Task(i + 1, info));
		m_tasks[i + 1] = std::move(m);
	}
}

mtime_t Scheduler::getCurrentTime()
{
	return m_time;
}

void Scheduler::schedule(mtime_t end)
{

	if (m_tasks.size() == 0)
		return;

	// Queues hold the ids of the tasks
	std::vector< id_t > m_dispatchQueue;
	std::vector< id_t > m_activeQueue;
	std::vector< id_t > m_passiveQueue;
	id_t lastExecute = -1;
	std::string lastStatText = "";
	std::stringstream s;

	for (auto& t : m_tasks)
	{
		// every task is in dispatch queue at the beginning
		m_dispatchQueue.push_back(t.first);
	}

	for (m_time = 1; m_time < end + 1; m_time++)
	{
		// dispatch ready tasks
		for (int i = 0; i < m_dispatchQueue.size(); i++)
		{
			auto id = m_dispatchQueue.begin() + i;
			if (m_tasks[*id]->isReady(m_time))
			{
				m_activeQueue.push_back(*id);
				m_dispatchQueue.erase(id);
				i--;
			}

		}

		// dispatch ready tasks
		for (int i = 0; i < m_passiveQueue.size(); i++)
		{
			auto id = m_passiveQueue.begin() + i;
			if (m_tasks[*id]->isReady(m_time))
			{
				m_activeQueue.push_back(*id);
				m_passiveQueue.erase(id);
				i--;
			}

		}


		std::vector< id_t >::iterator it_toExecute;
		id_t toExecute;
		// find the task to be executed
		if (m_activeQueue.size() > 0)
		{
			it_toExecute = m_activeQueue.begin();

			for (int i = 1; i < m_activeQueue.size(); i++)
			{
				std::vector< id_t >::iterator f = m_activeQueue.begin() + i;
				bool isPrior = comparePriority(*m_tasks[*f], *m_tasks[*it_toExecute]);
				if (isPrior)
					it_toExecute = f;
			}

			toExecute = *it_toExecute;
		}
		else
		{
			toExecute = -1;
		}




		if (toExecute != lastExecute)
		{
			
			if (!lastStatText.empty())

			{
				

				if (lastExecute == -1)
				{
					lastStatText = "";
				}
				else
				{
					s << m_time - 1 << std::endl;
					lastStatText = s.str();
				}

				outputStream << lastStatText << std::endl;

				lastStatText = "";
				s.str(std::string());
			}

			for (auto& i : m_tasks)
			{

				s << "T" << i.first << " (" << "instance: " << i.second->getInstanceCount()
					<< ", remainingExe: " << i.second->getRemainingExe() << ", deadline: " << i.second->getEffectiveDeadline() << ") -- ";
			}

			s << "CPU: T" << toExecute << ", start: " << m_time - 1 << ", end:";
			lastStatText = s.str();

			lastExecute = toExecute;
		}

		if (toExecute != -1)
		{
			m_tasks[toExecute]->execute();

			if (m_tasks[toExecute]->isFinished())
			{
				m_passiveQueue.push_back(toExecute);
				m_activeQueue.erase(it_toExecute);
			}
		}
		

		for (auto& t : m_tasks)
		{
			if (t.second->deadlineMiss(m_time))
			{
				outputStream << "deadline miss: T" << t.first << " at time: " << m_time << std::endl;

			}
				

			t.second->cycle(m_time);
			
		}
	}


}




//float Scheduler::feasibilityCheck()
//{
//        if(m_tasks.empty())
//                return 0;
//
//        float filled = 0;
//        for(auto& t : m_tasks)
//        {
//                unsigned times = hyperperiod / t.second->m_info.period;
//                filled = filled + t.second->m_info.exeTime * times;
//        }
//
//        return filled/hyperperiod;
//}