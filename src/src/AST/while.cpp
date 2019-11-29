#include "AST/while.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

WhileNode::WhileNode(
    int _line_number, 
    int _col_number, 
    Node _condition, 
    NodeList* _body
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->condition = _condition;
        this->body = _body;
    }

WhileNode::~WhileNode(){
    SAFE_DELETE(this->condition)
    NODELIST_PTR_DELETE(this->body)
}

void WhileNode::print() {
    std::cout << "while statement <line: " << line_number
        << ", col: " << col_number
        << ">" << std::endl;
}