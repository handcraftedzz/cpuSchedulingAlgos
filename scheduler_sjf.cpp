/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Andrew Méndez
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <sstream>
#include "scheduler_sjf.h"

SchedulerSJF::SchedulerSJF()
{
    this->overallTime = 0;
}

SchedulerSJF::~SchedulerSJF()
{

}
void SchedulerSJF::init(vector<PCB>& p_list) 
{
    this->processesSJF = p_list;
    waitingTimes.resize(processesSJF.size());
    turnAroundTimes.resize(processesSJF.size());
}

void SchedulerSJF::print_results()
{
    double totalTurnAroundTimes = 0;
    double totalWaitingTimes = 0;
    unsigned int targetIndex, currentIndex;

    for (unsigned int i = 0; i < processesSJF.size(); i++)
    {
        cout << "Running Process " << processesSJF[i].name << " for " << processesSJF[i].burst_time << " time units" << endl;
    }
 
 
    for (targetIndex = 0; targetIndex < processesSJF.size(); targetIndex++)//s might turn into c for current burst index (c).
    {
        unsigned int processTurnAroundTime = 0;
        unsigned int processWaitingTime = 0;
        unsigned int numInDesiredProcess = targetIndex+1;
        cout << "T" << numInDesiredProcess << " turn-around time = ";
        
        stringstream targetBurstProcess;
        char TBPletter;
        unsigned int TBPintVal;

        string temp = processesSJF[targetIndex].name;
        targetBurstProcess << temp;
        targetBurstProcess >> TBPletter;
        targetBurstProcess >> TBPintVal; 
        
        bool found = false; ///variable that detmerines whether the same T process is found or not.
        //use break somewhere?? *ended up using the found != true which was smoother :). cuz break sorta just like cuts. boolean var tracks.
        //T6 is in CBPletter. processesSJF[0] contains the info of process T6.
        
        for (currentIndex = 0; found != true; currentIndex++)
        {
            stringstream currentBurstProcess;
            char CBPletter;
            unsigned int CBPintVal;
            string tempp = processesSJF[currentIndex].name;
            currentBurstProcess << tempp;
            currentBurstProcess >> CBPletter;
            currentBurstProcess >> CBPintVal;
            if (CBPintVal == numInDesiredProcess)
            {
                processTurnAroundTime += processesSJF[currentIndex].burst_time;
                processWaitingTime = processTurnAroundTime; //line 78
                processWaitingTime -= processesSJF[currentIndex].burst_time;
                turnAroundTimes[targetIndex] = processTurnAroundTime;
                waitingTimes[targetIndex] = processWaitingTime;
                cout << turnAroundTimes[targetIndex]; // "endl; *placeholder* reminder"
                cout << ", waiting time = " << waitingTimes[targetIndex] << endl;
                totalTurnAroundTimes += turnAroundTimes[targetIndex];
                totalWaitingTimes += waitingTimes[targetIndex];
                found = true;
            }
            else if (CBPintVal != numInDesiredProcess && found == false)
            {   
                processTurnAroundTime += processesSJF[currentIndex].burst_time;
                //don't really got to be adding all the burst times to stor into processWaitingTime since I get the final result at line 78. 
                //Would be redudant if i do += for processWaitingTime. 
                //I just subtract current process' burst time from all all the burst times to get the wait time for that process in the vector.
            }

        }
    } 
    totalTurnAroundTimes /= processesSJF.size();
    totalWaitingTimes /= processesSJF.size();
    //does setprecision need to be 2, ?? "Average turn-around time = 82.5, Average waiting time =61.25 for sjf example.out", 
    //me just did 3 just in case to be safe, however potential extra 0s at the end may make it look weird.

    cout << "Average turn-around time = " << totalTurnAroundTimes << ", Average waiting time = " << totalWaitingTimes << endl;
    //Oohh, just realized fix set precision isn't really needed :p  .
}

void SchedulerSJF::simulate() 
{
    unsigned int j, k, smallestIndex, smallestBurst;
    unsigned int currentBurst, currentIndex;
    smallestIndex = 0;
    //I'll be using selection sort for SJF, ordering the burst times from smallest to largest.
    for (j = 0; j < processesSJF.size(); j++)
    { 
        smallestIndex = j;
        smallestBurst = processesSJF[smallestIndex].burst_time; 
        bool alreadySwapped = false;
        for (k = j+1; k < processesSJF.size(); k++) //processesSJF.size() *n* - 1 since we have one less val since we start 1 PCB ahead at the beginning with k = j+1
        {
            currentBurst = processesSJF[k].burst_time;
            if (currentBurst < smallestBurst)
            {
                smallestIndex = k;
                smallestBurst = processesSJF[smallestIndex].burst_time;
            }
           if (smallestBurst == currentBurst)
           {
            stringstream smallBurstProcess, currentBurstProcess;
            char SBPletter, CBPletter;
            unsigned int SBPintVal, CBPintVal;
            smallBurstProcess << processesSJF[smallestIndex].name;
            smallBurstProcess >> SBPletter;
            smallBurstProcess >> SBPintVal;
            
            currentBurstProcess << processesSJF[k].name;
            currentBurstProcess >> CBPletter;
            currentBurstProcess >> CBPintVal;
            if (CBPintVal < SBPintVal)
            {
              smallestIndex = k;
            }
           }
        }
    PCB temp = processesSJF[j]; 
    processesSJF[j] = processesSJF[smallestIndex];
    processesSJF[smallestIndex] = temp;       
    }
}
// TODO: add implementation of SchedulerSJF constructor, destrcutor and 
// member functions init, print_results, and simulate here
