//
// Created by MacBook on 22.11.2018.
//
#include <iostream>
#include "Scheduler.h"
#include <queue>



Scheduler::Scheduler(vector<Process> myProcesses, vector<Code> myCodes) {
    this->myProcesses = myProcesses;
    this->myCodes = myCodes;
    vector<string> HeadTail;
    vector<Process> finishedProcesses;
    int currentTime;
}
//Here we override the "<" operator so that we can compare the process according to their priorities.
//If the processes have the same priority, they are compared according to the arrival time (FCFS).
//If the processes have the same priorities and the arrival times, they are compared according to the execution times.
//Faster process is executed first.
bool operator<(const Process &Process1, const Process &Process2){
    if(Process1.Priority != Process2.Priority){
    return Process1.Priority > Process2.Priority;
    }
    else if(Process1.Priority == Process2.Priority && Process1.ArrivalT != Process2.ArrivalT){
        return Process1.ArrivalT > Process2.ArrivalT;
    }
    else if(Process1.Priority == Process2.Priority && Process1.ArrivalT == Process2.ArrivalT){
        int Process1MaxTime = 0; //This holds the total execution time of the process that just arrives.
        int Process2MaxTime = 0; //This holds the total execution time of the process that will be following.
        for(int i = 0; i<Process1.ProcessCode.InstructionExeT.size(); i++){
            Process1MaxTime = Process1MaxTime + Process1.ProcessCode.InstructionExeT[i];
        }
        for(int j = 0; j<Process2.ProcessCode.InstructionExeT.size(); j++){
            Process2MaxTime = Process2MaxTime + Process2.ProcessCode.InstructionExeT[j];
        }
        return Process1MaxTime > Process2MaxTime;
    }
}
//This function calculates the total execution time of a process.
int FindTotalExeTime(Process P){
    int TotalExeTime  = 0;
    for(int i = 0; i<P.ProcessCode.InstructionExeT.size(); i++){
        TotalExeTime = TotalExeTime + P.ProcessCode.InstructionExeT[i];
    }
    return TotalExeTime;
}

//Schedule method of the Scheduler. This is the essential function.
void Scheduler::Schedule(vector<Process> ProcessToQueue){
    int waitingTime; //waiting time of the Processes.
    currentTime = myProcesses[0].ArrivalT; //currentTime of the system is initally equal to first process's arrival time.
    Code lelCode; //This code object is going to be used throughout the computations as temporary Code.
    Process tempProcess; //Temp process will also be used throughout the computations as temporary Process.
    bool sameArrival = false; //This boolean value evaluates to true if the next two processes arrive at the same moment.
    Process lelProcess; //This process process will also be used throughout the computations as temporary Process.
    priority_queue<Process> myQueue; //A priority queue is used in order to make the scheduling.
    string myString = "HEAD-"; //String to be pushed to HeadTail vector which then will be printed as the output.
    priority_queue<Process> SecondQueue = myQueue; //A temporary Queue that will be used throughout the computations.

    //If there are no processes with ArrivalT = 0, we push "HEAD--TAIL" into our vector HeadTail.
    if(myProcesses[0].ArrivalT != 0){
        HeadTail.push_back("0:" + myString + "-TAIL");
    }

    //We initialize all of the InstructionIndexes of the processes that will be processes.
    for(int i = 0; i<myProcesses.size(); i++){
        myProcesses[i].InstructionIndex = 0;
    }

    //This while loop where all the calculations are made.
    //It executes either if there are processes that havent arrived yet
    // OR, if there are still some processes to be processes but also arrived.
    while(myProcesses.empty() == false || myQueue.empty() == false){

        // If the processor is in idle state, we make current time equal to the arrival time of the next processes to be arrived.
        if(myQueue.size()==0 && myProcesses.size()!=0){
            currentTime = myProcesses[0].ArrivalT;
        }

        //In this if/else statement we determine if two processes arrived at the same time.
        if(myProcesses.size()>1){ //If there are more than one process that hasn't arrived yet,
            if(myProcesses[0].ArrivalT == myProcesses[1].ArrivalT){ //If the arrival times of the next two processes are equal
                sameArrival = true;
            }
                //else if current time is greater than or equal to the first two proceeses arrival times,
                //Note: in the code this is also considered as same arrival becouse there sould be one instance
                //of these two  situations in the output.
            else if(myProcesses[0].ArrivalT <= currentTime &&  myProcesses[1].ArrivalT <= currentTime){
                sameArrival = true;
            }
            else{
                sameArrival = false;
            }
        }
        else{
            sameArrival = false;
        }

        //If there are processes to be processed and the currentTime is greater than or equal to the first process's arrival time,
        //We push the processes into the queue and remove it from myProcesses vector.
        if(myProcesses.size() != 0){
            if(currentTime >= myProcesses[0].ArrivalT){
                myQueue.push(myProcesses[0]);
                myProcesses.erase(myProcesses.begin());
            }
        }

        //Here in this for loop we assign the associated "Code" to the top Process of myQueue
        //We do a pop/push sequence in order to achieve that.
        //The if statement checks if the the Code of the top process of the queue is
        //equal to the code in the myCodes vector.
        for(int i = 0; i<myCodes.size(); i++){
            if(myQueue.top().CodeName == myCodes[i].CodeName){
                lelCode = myCodes[i];
                lelProcess = myQueue.top();
                myQueue.pop();
                lelProcess.ProcessCode = lelCode;
                myQueue.push(lelProcess);

            }
        }

        //Here we create the output strings and push them into HeadTail vector to be outputted.
        //We use a temporary queue named SecondQueue so that we can make the opperations without
        //disturbing our actual queue, myQueue.
        SecondQueue = myQueue;
        myString = "HEAD-";
        for(int i = 0; i < myQueue.size(); i++){
            if(SecondQueue.size() != 0) {
                while(SecondQueue.size()!= 0){
                    myString = myString + SecondQueue.top().Name + "[" + to_string(SecondQueue.top().InstructionIndex + 1) + "]" + "-";
                    SecondQueue.pop();
                }
                myString = to_string(currentTime) + ":" + myString + "TAIL";
                if(sameArrival == false){
                    HeadTail.push_back(myString);
                    int xdxd = 0;
                }
            }
        }

        //In this while loop we update the current time. Hypothetically this part is where the execution of the processes would happen.
        //Current time is updated according to the next instructions execution time in the process Code.
        while(currentTime < myProcesses[0].ArrivalT || myProcesses.size()==0){
            currentTime = currentTime + myQueue.top().ProcessCode.InstructionExeT[myQueue.top().InstructionIndex];
            //If the last intruction is the next instruction to be executed. The process must be killed.
            //Therefore in this if statement we collect the finish time, the total execution time and the waiting time of the process
            //into the temporary tempProcess object.
            //Then, this tempProcess is pushed into the FinishedProcesses vector which will be used in the output of the program.
            //Finally, the process is removed from the queue and the break statement exits the while loop.
            if(myQueue.top().ProcessCode.InstructionName[myQueue.top().InstructionIndex] == "exit"){
                tempProcess = myQueue.top();
                tempProcess.FinishTime = currentTime; //we find the finishing time of a process here
                tempProcess.TurnaroundTime = tempProcess.FinishTime - tempProcess.ArrivalT; //we find the turnaround time of the process here
                tempProcess.totalExeTime = FindTotalExeTime(tempProcess);
                waitingTime = tempProcess.TurnaroundTime - tempProcess.totalExeTime;
                tempProcess.WaitingTime = waitingTime;
                finishedProcesses.push_back(tempProcess);
                myQueue.pop();
                break;
            }
            //In the following statements we increment the instruction index of the process so
            //that the process continues the execution from the next instruction when it gets to
            //use the CPU again. We do so again by the help of the temporary process myProcess.
            lelProcess = myQueue.top();
            myQueue.pop();
            lelProcess.InstructionIndex++;
            myQueue.push(lelProcess);
        }

    //The following if statement pushes the string into the HeadTail vector if the CPU  is idle.
    //That is, if there are no processes in the queue and currentTime is less than the arrival time of the next process
    //that is to be arrived.
    if(myQueue.size()  == 0  && currentTime < myProcesses[0].ArrivalT){
        HeadTail.push_back(to_string(currentTime)+ ":HEAD--TAIL");
    }

    }
    //Finally, when the while loop terminates, the string currentTime + "HEAD--TAIL" is pushed into
    //HeadTail vector.
    myString = to_string(currentTime) + ":HEAD--TAIL";
    HeadTail.push_back(myString);
}
