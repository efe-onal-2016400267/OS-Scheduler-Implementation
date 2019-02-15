//
// Created by MacBook on 22.11.2018.
//

#ifndef CMPE322PROJECT1_PROCESS_H
#define CMPE322PROJECT1_PROCESS_H
#include<iostream>
#include<list>
#include <vector>
#include "Code.h"
using namespace std;
class Process{
public:
    //Default constructor
    Process(){

    }
    //The constructor for class Process
    Process(string Name, int Priority, string CodeName, int ArrivalT);
    //copy constructor
    Process(const Process &other);
    //Next four fields are the specified fields of a process in definition.txt file.
    string Name;
    int Priority;
    string CodeName;
    int ArrivalT;

    Code ProcessCode; //The code of the process.
    int InstructionIndex; //This integer shows at which instruction was the process allocated from the CPU
    int FinishTime; //This integer indicates the time when the process was terminated executing exit instruction.
    int TurnaroundTime; //The turnaround time for a process.
    int WaitingTime; //The waiting time for a process.
    int totalExeTime; //Total execution time for a process.

};

#endif //CMPE322PROJECT1_PROCESS_H
