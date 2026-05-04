/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Andrew Méndez
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_rr.h"

SchedulerRR::SchedulerRR(int time_q)
{
    this->timeQuantum = time_q;
    this->front = 0; //index that will hold the oldest element stored in the circ. queue.
    this->rear = this->capacity-1; //index that will hold the newest element stored in the circ. queue.
    this->size = 0; //current size of the circ. queue.
    this->capacity = 0;
}

SchedulerRR::~SchedulerRR()
{

}

void SchedulerRR::init(vector<PCB>& p_list)
{
    this->processesRR = p_list;

    turnAroundTimes.resize(p_list.size());
    waitingTimes.resize(p_list.size());

    rrCircularQueue = processesRR;
    this->capacity = rrCircularQueue.size();

    for (int q = 0; q < p_list.size(); q++)
    {
        rrCircularQueue[q] = processesRR[q];
    }

    originalBT.resize(p_list.size());

    for (int u = 0; u < p_list.size(); u++)
    {
        originalBT[u] = p_list[u].burst_time;
    }
    this->size = p_list.size();
}

void SchedulerRR::print_results() 
{
  double totalTurnAround, totalWaiting;
  totalTurnAround = totalWaiting = 0;

  double avgT, avgW;
  avgT = avgW = 0;


  int k;
  for (k = 0; k < processesRR.size(); k++)
  {
    cout << processesRR[k].name << " turn-around time = " << turnAroundTimes[k] << ", waiting time = " << waitingTimes[k] << endl;
    totalTurnAround += turnAroundTimes[k];
    totalWaiting += waitingTimes[k];
  }

  avgT = totalTurnAround / processesRR.size();
  avgW = totalWaiting / processesRR.size();

  cout << "Average turn-around time = " << avgT << ", Average waiting time = " << avgW << endl;

}


void SchedulerRR::simulate() 
{
    unsigned int currentT;
    currentT = 0;

    while (this->size > 0)
    {   
        PCB theFrontProcess = rrCircularQueue[this->front];
        this->front = (this->front + 1) % this->capacity;
        this->size--; //decerment by 1

        unsigned int tempTime;

        if (theFrontProcess.burst_time > timeQuantum) //still more time avaliable to cut from the burst
        {
            tempTime = timeQuantum;
        }
        else
        {
            tempTime = theFrontProcess.burst_time; //othewise, u get the remainder, which would be less than 6 (for out time Q in this case of 6)
        }

        cout << "Running Process " << theFrontProcess.name << " for " << tempTime << " time units " << endl;

        theFrontProcess.burst_time -= tempTime;
        currentT += tempTime;

        if (theFrontProcess.burst_time > 0)
        {
            this->rear = (this->rear + 1) % this->capacity;
            rrCircularQueue[this->rear] = theFrontProcess;
            this->size++;
        }

        else
        {
            turnAroundTimes[theFrontProcess.id] = currentT;
            waitingTimes[theFrontProcess.id] = turnAroundTimes[theFrontProcess.id] - originalBT[theFrontProcess.id];
        }

    }

}