#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "Process.h"
#include "Scheduler.h"
#include "Code.h"
#include <stdio.h>
#include <vector>
using namespace std;
template <class Container>

//This function splits a string into words.
void split1(const string& str, Container& cont){
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}
//This bool value will be true if the code of a process already
//exists in the Codes vector. So the same files will not be added to Codes
//multiple times.
bool codeExists = false;

//This vector holds all the processes and will be given as an argument for the scheduling.
vector<Process> Processes;

//This vector holds the Codes we're going to use.
vector<Code> Codes;

//This bool funtion returns codeExists and it traces both Processes and Codes vectors
//in nested for loops searching matching "Codes".
bool doesCodeExist(int i){
    codeExists = false;
    for(int j = 0; j < Codes.size(); j++){
        if(Processes[i].CodeName == Codes[j].CodeName){
            codeExists = true;
            break;
        }
    }
    return codeExists;
}

int main() {
    //These 4 correspond to  the fields of a Process. We're going to use them while putting new Processes into the
    //vector Processes.
    string currentName;
    int currentPriority;
    string currentCodeName;
    int currentArrivalT;

    //These 2 vectors words and words two are going to hold the lines of the input files
    //with every word as an element.
    vector<string> words; //words holds definition.txt file
    vector<string> words2; //words2 holds CodeX.txt files

    //We get the input file into infile.
    ifstream infile("definition.txt");  //infile is the input file.
    string line;
    int i = 0;
    Process k;
    if (infile.is_open())  //if the input file is open.
    {

        while ( infile.good() ) //if the file is not completely read.
        {
            //We split the file into lines.
            getline(infile, line);
            //We split the lines into words.
            split1(line, words);
            //At each iteration, we create a process, p, and push it into Processes vector.
            currentName = words[4*i+0];
            currentPriority = stoi(words[4*i+1]);
            currentCodeName = words[4*i+2];
            currentArrivalT = stoi(words[4*i+3]);

            //We break if the last line of the file is added to words second time (at the end of the file).
            if(currentName == k.Name){
                break;
            }

            //We create a Process p for each line of the definitions.txt and push it intp Processes vector.
            Process p(currentName, currentPriority, currentCodeName, currentArrivalT);
            // we create this k Process just to check if the last line is added twice.
            k.Name = p.Name;
            k.Priority = p.Priority;
            k.CodeName =  p.CodeName;
            k.ArrivalT = p.ArrivalT;
            Processes.push_back(p);
            i++;
        }
        infile.close(); //we close the file at copmletion.
    }
    //Now we'll be reading codeX.txt files
    int indice1 = 0;
    Code myCode; //This Code obj. will be pushed into Codes vector in every iteration.
    for(int i = 0; i<Processes.size(); i++){
        if(doesCodeExist(i) == false){ //We wont read the  file if we already did for another Process.
            myCode.CodeName = Processes[i].CodeName;
            myCode.InstructionName.clear();
            myCode.InstructionExeT.clear();
            string myString = myCode.CodeName + ".txt"; //myString is the codes name + ".txt"
            ifstream myfile(myString);
            if (myfile.is_open())
            {

                while ( myfile.good() )
                {
                    getline (myfile,line);
                    split1(line, words2);
                    myCode.InstructionName.push_back(words2[2*indice1+0]); //Here we assign the instruction name vector of the code
                    myCode.InstructionExeT.push_back(stoi(words2[2*indice1+1]));//Here we assign the instruction execution time vector of the code
                    indice1++;
                }
                myfile.close();
            }
            Codes.push_back(myCode);
            currentCodeName = myCode.CodeName;
            Codes[Codes.size()-1].CodeName=currentCodeName;

        }
    }

    Scheduler myScheduler(Processes, Codes); //We create a Scheduler instance with Processes and Codes vectors.
    myScheduler.Schedule(Processes); //We call the Schedule method of the myScheduler. This is where the magic happens.
    vector<string> output1 = myScheduler.HeadTail;  //output1 is the vector that holds the HEAD--TAIL strings and will be printed as the output
    for(int i = 0; i<Processes.size(); i++){
        for(int j= 0; j<myScheduler.finishedProcesses.size(); j++){
            if(Processes[i].Name == myScheduler.finishedProcesses[j].Name){
                //Then we assign the waiting times and turnaround times of the processes in Processes which will be outputting.
                //myScheduler has a finishedProcesses vector field that holds the processes with the final time values.
                Processes[i].WaitingTime = myScheduler.finishedProcesses[j].WaitingTime;
                Processes[i].TurnaroundTime = myScheduler.finishedProcesses[j].TurnaroundTime;
            }
        }
    }

    //here, perform the output operation
    ofstream offile; //offile is the name of the output file.
    offile.open("output.txt"); //name of the output file is output.txt
    //First we print the output1 vector in a for loop.
    for(int w = 0; w < output1.size(); w++){
        cout << output1[w] << endl;
        offile << output1[w] << endl;
    }
    cout << endl;
    offile <<endl;
    // Here we print the second part of the output.
    for(int w = 0; w< Processes.size();w++){
        cout << "Turnaround time for " << Processes[w].Name << " = " << Processes[w].TurnaroundTime << " ms" << endl;
        cout  << "Waiting time for " << Processes[w].Name << " = " << Processes[w].WaitingTime << "" << endl;
        offile << "Turnaround time for " << Processes[w].Name << " = " << Processes[w].TurnaroundTime << " ms" << endl;
        if(w == Processes.size() - 1){
            offile<< "Waiting time for " << Processes[w].Name << " = " << Processes[w].WaitingTime << "";
        }
        else{
            offile<< "Waiting time for " << Processes[w].Name << " = " << Processes[w].WaitingTime << "" << endl;
        }

    }
    return 0;
}