#include "AST/assignment.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>


AssignmentNode::AssignmentNode(
    int _line_number, 
    int _col_nubmer, 
    Node _variable_reference_node, 
    Node _expression_node
    ){
        this->line_number = _line_number;
        this->col_number = _col_nubmer;
        this->variable_reference_node = _variable_reference_node;
        this->expression_node = _expression_node;
    }

AssignmentNode::~AssignmentNode(){
    SAFE_DELETE(this->variable_reference_node)
    SAFE_DELETE(this->expression_node)
}

void AssignmentNode::print() {
    std::cout << "assignment statement <line: " << line_number
        << ", col: " << col_number
        << "> " << std::endl;
}