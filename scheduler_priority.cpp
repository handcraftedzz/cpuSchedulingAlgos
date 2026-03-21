/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Andrew Méndez
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <sstream>
#include "scheduler_priority.h"


SchedulerPriority::SchedulerPriority()
{

}

SchedulerPriority::~SchedulerPriority()
{

}

void SchedulerPriority::init(vector<PCB>& p_list)
{   
    this->processesPri = p_list;
    turnAroundTimes.resize(processesPri.size());
    waitingTimes.resize(processesPri.size());
}

void SchedulerPriority::print_results()
{
    unsigned int i, targetIndex, currentIndex;
    double totalTurnAroundTimes, totalWaitingTimes;
    totalTurnAroundTimes = totalWaitingTimes = 0;

    for (i = 0; i < processesPri.size(); i++)
    {
        cout << "Running Process " << processesPri[i].name << " for " << processesPri[i].burst_time << " time units" << endl;
    }

    for (targetIndex = 0; targetIndex < processesPri.size(); targetIndex++)//s might turn into c for current burst index (c).
    {
        unsigned int processTurnAroundTime = 0;
        unsigned int processWaitingTime = 0;
        unsigned int numInDesiredProcess = targetIndex+1;
        cout << "T" << numInDesiredProcess << " turn-around time = ";
        
        stringstream targetBurstProcess;
        char TBPletter;
        unsigned int TBPintVal;

        string temp = processesPri[targetIndex].name;
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
            string tempp = processesPri[currentIndex].name;
            currentBurstProcess << tempp;
            currentBurstProcess >> CBPletter;
            currentBurstProcess >> CBPintVal;
            if (CBPintVal == numInDesiredProcess)
            {
                processTurnAroundTime += processesPri[currentIndex].burst_time;
                processWaitingTime = processTurnAroundTime; //line 78
                processWaitingTime -= processesPri[currentIndex].burst_time;
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
                processTurnAroundTime += processesPri[currentIndex].burst_time;
                //don't really got to be adding all the burst times to stor into processWaitingTime since I get the final result at line 78. 
                //Would be redudant if i do += for processWaitingTime. 
                //I just subtract current process' burst time from all all the burst times to get the wait time for that process in the vector.
            }

        }
    } 
    totalTurnAroundTimes /= processesPri.size();
    totalWaitingTimes /= processesPri.size();
    //does setprecision need to be 2, ?? "Average turn-around time = 82.5, Average waiting time =61.25 for sjf example.out", 
    //me just did 3 just in case to be safe, however potential extra 0s at the end may make it look weird.

    cout << "Average turn-around time = " << totalTurnAroundTimes << ", Average waiting time = " << totalWaitingTimes << endl;
    //Oohh, just realized fix set precision isn't really needed :p  .
}

void SchedulerPriority::simulate()
{
    //prioritize priority number, then if two processes have the same priority.
    /*
    for (int l = 0; l < processesPri.size(); l++) //The one that gets printed first will be one with smaller num in the process name "T1, T2, T3".
    {


    }
    */


    unsigned int j, k, unsortedIndex, unsortedPri;
    unsigned int currentPri, currentIndex;
    unsortedIndex = 0;

    //I'll be using selection sort for Priority, ordering the burst times from smallest to largest. Here i go again with Selection sort.
    //Small changes, instead of smallest burst and current burst. smallest priority and current priority instead now.
    //j will be u instead & k will be c for current... ?? potential idea.
    for (j = 0; j < processesPri.size(); j++)
    { 
        unsortedIndex = j; //the value at that index contains the number in the array that hasn't been sorted to fit into the array
        //based off of, from largest (left most number) to smallest (right most) once the array gets organized based off of highest pri num.
        unsortedPri = processesPri[unsortedIndex].priority; 
        bool alreadySwapped = false;
        for (k = j+1; k < processesPri.size(); k++) //processesSJF.size() *n* - 1 since we have one less val since we start 1 PCB ahead at the beginning with k = j+1
        {
            currentPri = processesPri[k].priority;
            if (currentPri > unsortedPri)
            {
                unsortedIndex = k;
                unsortedPri = processesPri[unsortedIndex].priority;
            }
           if (unsortedPri == currentPri)
           {
            stringstream smallerPriProcess, currentPriProcess;
            char SPPletter, CPPletter;
            unsigned int SPPintVal, CPPintVal;
            smallerPriProcess << processesPri[unsortedIndex].name;
            smallerPriProcess >> SPPletter;
            smallerPriProcess >> SPPintVal;
            
            currentPriProcess << processesPri[k].name;
            currentPriProcess >> CPPletter;
            currentPriProcess >> CPPintVal;
            if (CPPintVal < SPPintVal)
            {
              unsortedIndex = k;
            }
           }
        }
    PCB temp = processesPri[j]; 
    processesPri[j] = processesPri[unsortedIndex];
    processesPri[unsortedIndex] = temp;       
    }
}
// TODO: add implementation of SchedulerPriority constructor, destrcutor and 
// member functions init, print_results, and simulate here