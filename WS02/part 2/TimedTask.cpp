/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "TimedTask.h"
namespace seneca{

    // constructor
    TimedTask::TimedTask(): m_numTasks(0){
        m_startTime = std::chrono::steady_clock::now();
        m_endTime = std::chrono::steady_clock::now();
    }
    
    void TimedTask::startClock(){
        m_startTime = std::chrono::steady_clock::now(); // start clock
    }

    void TimedTask::stopClock(){
        m_endTime = std::chrono::steady_clock::now(); // stop clock
    }

    void TimedTask::addTask(const char* taskName){ // adding task
        if(m_numTasks < MAX_TASKS){
            m_tasks[m_numTasks].m_taskName = taskName;
            m_tasks[m_numTasks].m_units = "nanoseconds";
            // store duration subtract end time from start time
            m_tasks[m_numTasks].m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);
            m_numTasks++;
        }   
    }

    // output operator
    std::ostream& operator<<(std::ostream& os, const TimedTask& task){
        os << "--------------------------\n";
        os << "Execution Times:\n";
        os << "--------------------------\n";
        
        // displays all tasks
        for (int i = 0; i < task.m_numTasks; i++) {
            os << std::left << std::setw(21) << task.m_tasks[i].m_taskName << ' '
               << std::right << std::setw(13) << task.m_tasks[i].m_duration.count() << ' '
               << task.m_tasks[i].m_units << '\n';
        }
        os << "--------------------------\n";
        
        return os; // return object
    }
}