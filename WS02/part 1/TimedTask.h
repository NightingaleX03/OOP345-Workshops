/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <chrono>

#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

namespace seneca{

    static const int MAX_TASKS = 10;

    struct Task
    {
        std::string m_taskName;
        std::string m_units;
        std::chrono::steady_clock::time_point m_duration;
    };

    class TimedTask
    {
        int m_numTasks;
        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_endTime;
        Task m_tasks[MAX_TASKS];

    public:
        TimedTask();
        void startClock();
        void stopClock();
        void addTask();
        friend std::ostream &operator<<(std::ostream &os, const TimedTask &timedTask);
    };
}
#endif // TIMEDTASK_H
