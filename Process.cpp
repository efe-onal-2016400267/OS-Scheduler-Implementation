//
// Created by MacBook on 22.11.2018.
//
#include "Process.h"
#include<iostream>


Process::Process(string Name, int Priority, string CodeName, int ArrivalT){
    this->Name = Name;
    this->Priority = Priority;
    this->CodeName = CodeName;
    this->ArrivalT = ArrivalT;
    Code ProcessCode;
    int InstructionIndex;
    int FinishTime;
    int TurnaroundTime;
    int WaitingTime;
    int totalExeTime;
}
Process::Process(const Process &other) {
    this->Name = other.Name;
    this->CodeName = other.CodeName;
    this->Priority = other.Priority;
    this->ArrivalT = other.ArrivalT;
    this->ProcessCode = other.ProcessCode;
    this->InstructionIndex = other.InstructionIndex;
    this->FinishTime = other.FinishTime;
    this->TurnaroundTime = other.TurnaroundTime;
    this->WaitingTime = other.WaitingTime;
    this->totalExeTime = other.totalExeTime;


}
