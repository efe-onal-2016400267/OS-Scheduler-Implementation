//
// Created by MacBook on 22.11.2018.
//

#ifndef CMPE322PROJECT1_SCHEDULER_H
#define CMPE322PROJECT1_SCHEDULER_H
#include<iostream>
#include<list>
#include <vector>
#include "Process.h"
#include "Code.h"
using namespace std;
class Scheduler{
public:
    //Default constructor
    Scheduler();
    //Constructor
    Scheduler(vector<Process> myProcesses, vector<Code> myCodes);
    vector<Process> myProcesses; //This vector holds the processes and given as an argument when the Scheduler instance is created.
    vector<Code> myCodes; //This vector holds the codes and given as an argument when the Scheduler instance is created.
    void Schedule(vector<Process> ProcessToQueue); // Schedule function of the scheduler.
    int TotalExeTime(Process P); // This function calculates the total execution time for a process.
    vector<string> HeadTail; // This string vector holds the HEAD--TAIL strings that will be outputted.
    vector<Process> finishedProcesses; // This vector holds the processes with the final time values after the scheduling is done.
    int currentTime; // This integers shows the current time at any instance of the execution.
};

#endif //CMPE322PROJECT1_SCHEDULER_H
