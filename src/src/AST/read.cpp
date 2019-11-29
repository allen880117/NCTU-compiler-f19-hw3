#include "AST/read.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

ReadNode::ReadNode(
    int _line_number, 
    int _col_number, 
    Node _variable_reference_node
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->variable_reference_node = _variable_reference_node;
    }

ReadNode::~ReadNode(){
    SAFE_DELETE(this->variable_reference_node)
}

void ReadNode::print() {
    std::cout << "read statement <line: " << line_number
        << ", col: " << col_number
        << "> " << std::endl;
}