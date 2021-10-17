

#include <RTSScheduler/Task.h>
#include <map>
#include <vector>
#include <memory>

// Abstract class for all schedulers
class Scheduler
{
public:
        // loads the tasks.
        void loadTasks(std::vector < TaskInfo >&); 

        // returns 0 if there are no tasks
        float feasibilityCheck(); 

        // 
        void schedule();

                
        virtual bool comparePriority(Task& lhs, Task& rhs) = 0;

                

private:

        std::map<id_t, std::unique_ptr<Task> > m_tasks;
        mtime_t hyperperiod;
};