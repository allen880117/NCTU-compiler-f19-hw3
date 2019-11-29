#include "AST/variable_reference.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

VariableReferenceNode::VariableReferenceNode(
    int _line_number, 
    int _col_number, 
    string _variable_name, 
    NodeList* _expression_node_list
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->variable_name = _variable_name;
        this->expression_node_list = _expression_node_list;
    }

VariableReferenceNode::~VariableReferenceNode(){
    NODELIST_PTR_DELETE(this->expression_node_list)
}

void VariableReferenceNode::print() {
    std::cout << "variable reference <line: " << line_number
        << ", col: " << col_number
        << "> " << variable_name 
        << std::endl;
}