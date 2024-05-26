#include "TimedTask.h"
namespace seneca{

    TimedTask::TimedTask(){
        m_numTasks = 0;
    }
    
    void TimedTask::startClock(){
        m_startTime = std::chrono::steady_clock::now();
    }

    void TimedTask::stopClock(){
        m_endTime = std::chrono::steady_clock::now();
    }

    void TimedTask::addTask(const char* taskName){
        if(m_numTasks < MAX_TASKS){
            m_tasks[m_numTasks].m_taskName = taskName;
            m_tasks[m_numTasks].m_units = "nanoseconds";
            m_tasks[m_numTasks].m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);
            m_numTasks++;
        }   
    }

    std::ostream& seneca::operator<<(std::ostream& os, const TimedTask& task){
        os << "Execution Times:\n";
        os << "--------------------------\n";
        
        for (int i = 0; i < task.m_numTasks; i++) {
            os << std::left << std::setw(21) << task.m_tasks[i].m_taskName << ' '
               << std::right << std::setw(13) << task.m_tasks[i].m_duration.count() << ' '
               << task.m_tasks[i].m_units << '\n';
        }
        os << "--------------------------\n";
        
        return os;
    }
}