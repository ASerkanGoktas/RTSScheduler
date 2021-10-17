
#include <queue>
#include <numeric>
#include <RTSScheduler/Scheduler.h>
#include <iostream>

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

void Scheduler::loadTasks(std::vector < TaskInfo >& tasks)
{
		std::vector< mtime_t > periods;
        for(id_t i = 0; i<tasks.size(); i++)
        {
                TaskInfo& info = tasks[i];
                std::unique_ptr<Task> m(new Task(i + 1, info));
                m_tasks[i+1] = std::move(m);
				periods.push_back(info.period);
        }

		hyperperiod = findlcm(periods);
}

void Scheduler::schedule()
{

	if (m_tasks.size() == 0)
		return;

        // Queues hold the ids of the tasks
        std::vector< id_t > m_dispatchQueue;
        std::vector< id_t > m_activeQueue;
        std::vector< id_t > m_passiveQueue;

        for(auto& t : m_tasks)
        {
                // every task is in dispatch queue at the beginning
                m_dispatchQueue.push_back(t.first);
        }

		std::cout << m_dispatchQueue.size() << std::endl;
        
        for(mtime_t time = 1; time < hyperperiod + 1; time++)
        {
				// dispatch ready tasks
                for(int i = 0; i < m_dispatchQueue.size(); i++)
                {
						auto id = m_dispatchQueue.begin() + i;
						std::cout << "dispatch " << i << std::endl;
						if (m_tasks[*id]->isReady(time))
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
					if (m_tasks[*id]->isReady(time))
					{
						m_activeQueue.push_back(*id);
						m_passiveQueue.erase(id);
						i--;
					}
						
				}


				std::vector< id_t >::iterator toExecute;
				
				// find the task to be executed
				if (m_activeQueue.size() > 0)
				{
					toExecute = m_activeQueue.begin();

					for (int i = 1; i < m_activeQueue.size(); i++)
					{
						std::vector< id_t >::iterator f = m_activeQueue.begin() + i;
						bool isPrior = comparePriority(*m_tasks[*f] ,*m_tasks[*toExecute]);
						if (isPrior)
							toExecute = f;
					}
				}
				else
				{
					std::cout << "executing none" << " time: " << time << std::endl;
					continue;
				}

				std::cout << "executing task" << *toExecute << " time: " << time << std::endl;
				m_tasks[*toExecute]->execute();

				if (m_tasks[*toExecute]->isFinished())
				{
					m_passiveQueue.push_back(*toExecute);
					m_activeQueue.erase(toExecute);
				}

				for (auto& t : m_tasks)
				{
					t.second->cycle(time);
				}
        }
}



float Scheduler::feasibilityCheck()
{
        if(m_tasks.empty())
                return 0;

        float filled = 0;
        for(auto& t : m_tasks)
        {
                unsigned times = hyperperiod / t.second->m_info.period;
                filled = filled + t.second->m_info.exeTime * times;
        }

        return filled/hyperperiod;
}