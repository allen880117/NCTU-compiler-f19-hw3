#include "AST/function_call.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>


FunctionCallNode::FunctionCallNode(
    int _line_number, 
    int _col_number, 
    string _function_name, 
    NodeList* _arguments
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->function_name = _function_name;
        this->arguments = _arguments;
    }

FunctionCallNode::~FunctionCallNode(){
    NODELIST_PTR_DELETE(this->arguments)
}

void FunctionCallNode::print() {
    std::cout << "function call statement <line: " << line_number
        << ", col: " << col_number
        << "> " << function_name 
        << std::endl;
}