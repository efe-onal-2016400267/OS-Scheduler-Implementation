//
// Created by MacBook on 22.11.2018.
//

#ifndef CMPE322PROJECT1_CODE_H
#define CMPE322PROJECT1_CODE_H
#include <iostream>
#include <vector>
using namespace std;
class Code{
public:
    Code(); //Default ccontructor.
    Code(string CodeName); //Constructor
    Code(const Code &other); //Copy consturctor.
    string CodeName; //Each Code object has a Code name field.
    vector<string> InstructionName; //Each code object has an InstructionName string vector field that holds the first column of the codeX.txt files
    vector<int> InstructionExeT; //And an InstructionExeT integer vector that holds the second column of the codeX.txt files.
};

#endif //CMPE322PROJECT1_CODE_H
