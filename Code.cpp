//
// Created by MacBook on 22.11.2018.
//
#include <iostream>
#include "Code.h"
Code::Code(){

}
Code::Code(string CodeName) {
    this->CodeName = CodeName;
    vector<string> InstructionName;
    vector<int> InstructionExeT;
}
Code::Code(const Code &other){
    this->CodeName = other.CodeName;
    InstructionExeT = other.InstructionExeT;
    InstructionName = other.InstructionName;
}
