#include "AST/return.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

ReturnNode::ReturnNode(
    int _line_number, 
    int _col_number, 
    Node _return_value
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->return_value = _return_value;
    }

ReturnNode::~ReturnNode(){
    SAFE_DELETE(this->return_value)
}

void ReturnNode::print() {
    std::cout << "return statement <line: " << line_number
        << ", col: " << col_number
        << ">" << std::endl;
}