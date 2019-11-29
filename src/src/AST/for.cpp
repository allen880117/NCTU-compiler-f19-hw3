#include "AST/for.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

ForNode::ForNode(
    int _line_number, 
    int _col_number, 
    Node _loop_variable_declaration, 
    Node _initial_statement, 
    Node _condition, 
    NodeList* _body
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->loop_variable_declaration = _loop_variable_declaration;
        this->initial_statement = _initial_statement;
        this->condition = _condition;
        this->body = _body;
    }

ForNode::~ForNode(){
    SAFE_DELETE(this->loop_variable_declaration)
    SAFE_DELETE(this->initial_statement)
    SAFE_DELETE(this->condition)
    NODELIST_PTR_DELETE(this->body)
}

void ForNode::print() {
    std::cout << "for statement <line: " << line_number
        << ", col: " << col_number
        << ">" << std::endl;
}