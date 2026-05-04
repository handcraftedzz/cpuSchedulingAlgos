/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Andrew Méndez
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_fcfs.h"


SchedulerFCFS::SchedulerFCFS()
{
    this->overallTime = 0;
}

SchedulerFCFS::~SchedulerFCFS()
{


}
void SchedulerFCFS::init(vector<PCB>& p_list) 
{
    this->processesFCFS = p_list;

    waitingTimes.resize(processesFCFS.size());
    turnAroundTimes.resize(processesFCFS.size());

}

void SchedulerFCFS::print_results()
{
    double totalTurnAroundTimes = 0;
    double totalWaitingTimes = 0;


    for (unsigned int i = 0; i < processesFCFS.size(); i++)
    {
        cout << "Running Process " << processesFCFS[i].name << " for " << processesFCFS[i].burst_time << " time units" << endl;
    }

    for (unsigned int i = 0; i < processesFCFS.size(); i++)
    {
        cout << processesFCFS[i].name << " turn-around time = " << turnAroundTimes[i] << " , waiting time = " << waitingTimes[i] << endl;   
    }

    for (unsigned int i = 0; i < processesFCFS.size(); i++)
    {
        totalTurnAroundTimes += turnAroundTimes[i];
        totalWaitingTimes += waitingTimes[i];
    }
    totalTurnAroundTimes /= processesFCFS.size();
    totalWaitingTimes /= processesFCFS.size();

    //cout << "Average turn-around time = " << fixed << setprecision(3) << totalTurnAroundTimes << ", Average waiting time = "<< fixed << setprecision(3) << totalWaitingTimes << endl;
    cout << "Average turn-around time = " << totalTurnAroundTimes << ", Average waiting time = "<< totalWaitingTimes << endl;

}

void SchedulerFCFS::simulate()
{
    unsigned int waitTime;
    waitingTimes[0] = waitTime = 0;
    for (unsigned int i = 0; i < processesFCFS.size(); i++)
    {
        overallTime += processesFCFS[i].burst_time;
    }

    for (unsigned int i = 1; i < processesFCFS.size(); i++) //we're starting to calculate the 2nd processes 
    //& the following proccess
    {
        waitTime += processesFCFS[i-1].burst_time;
        waitingTimes[i] = waitTime;
    }
    
    for (unsigned int i = 0; i < processesFCFS.size(); i++) //now time to calulcate the turn around times
    {
        turnAroundTimes[i] = processesFCFS[i].burst_time + waitingTimes[i];
    }

}