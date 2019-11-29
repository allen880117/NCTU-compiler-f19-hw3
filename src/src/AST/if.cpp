#include "AST/if.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

IfNode::IfNode(
    int _line_number, 
    int _col_number, 
    Node _condition, 
    NodeList* _body, 
    NodeList* _body_of_else
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->condition = _condition;
        this->body = _body;
        this->body_of_else = _body_of_else;
    }

IfNode::~IfNode(){
    SAFE_DELETE(this->condition)
    NODELIST_PTR_DELETE(this->body)
    NODELIST_PTR_DELETE(this->body_of_else)
}

void IfNode::print() {
    std::cout << "if statement <line: " << line_number
        << ", col: " << col_number
        << ">" << std::endl;
}