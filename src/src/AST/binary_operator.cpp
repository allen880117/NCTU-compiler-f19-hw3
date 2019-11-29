#include "AST/binary_operator.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

BinaryOperatorNode::BinaryOperatorNode(
    int _line_number, 
    int _col_number, 
    enumOperator _op, 
    Node _left_operand, 
    Node _right_operand
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->op = _op;
        this->left_operand = _left_operand;
        this->right_operand = _right_operand;
    }

BinaryOperatorNode::~BinaryOperatorNode(){
    SAFE_DELETE(this->left_operand)
    SAFE_DELETE(this->right_operand)
}

void BinaryOperatorNode::print() {
    std::cout << "binary operator <line: " << line_number
        << ", col: " << col_number
        << "> ";
    
    // cout << operator
    switch(op){
        case OP_OR:               std::cout<<"or"; break;
        case OP_AND:              std::cout<<"and"; break;
        // case OP_NOT:              std::cout<<"not"; break;
        case OP_LESS:             std::cout<<"<"; break;
        case OP_LESS_OR_EQUAL:    std::cout<<"<="; break;
        case OP_EQUAL:            std::cout<<"="; break;
        case OP_GREATER:          std::cout<<">"; break;
        case OP_GREATER_OR_EQUAL: std::cout<<">="; break;
        case OP_NOT_EQUAL:        std::cout<<"<>"; break;
        case OP_PLUS:             std::cout<<"+"; break;
        case OP_MINUS:            std::cout<<"-"; break;
        case OP_MULTIPLY:         std::cout<<"*"; break;
        case OP_DIVIDE:           std::cout<<"/"; break;
        case OP_MOD:              std::cout<<"mod"; break;
        default:                  std::cout<<"unknown"; break;
    }
    // cout << operator END

    std::cout << std::endl;
}