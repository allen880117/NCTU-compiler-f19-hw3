#include "AST/print.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

PrintNode::PrintNode(
    int _line_number, 
    int _col_number, 
    Node _expression_node
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->expression_node = _expression_node;
    }

PrintNode::~PrintNode(){
    SAFE_DELETE(this->expression_node)
}

void PrintNode::print() {
    std::cout << "print statement <line: " << line_number
        << ", col: " << col_number
        << "> " << std::endl;
}