#include "AST/unary_operator.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

UnaryOperatorNode::UnaryOperatorNode(
    int _line_number, 
    int _col_number, 
    enumOperator _op, 
    Node _operand
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->op = _op;
        this->operand = _operand;
    }

UnaryOperatorNode::~UnaryOperatorNode(){
    SAFE_DELETE(this->operand)
}

void UnaryOperatorNode::print() {
    std::cout << "unary operator <line: " << line_number
        << ", col: " << col_number
        << "> ";
    
    // cout << operator
    switch(op){
        case OP_NOT:              std::cout<<"not"; break;
        case OP_MINUS:            std::cout<<"neg"; break;
        default:                  std::cout<<"unknown"; break;
    }
    // cout << operator END

    std::cout << std::endl;
}