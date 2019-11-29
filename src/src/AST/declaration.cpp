#include "AST/declaration.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

DeclarationNode::DeclarationNode(
    int _line_number, 
    int _col_number, 
    NodeList* _variables_node_list
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->variables_node_list = _variables_node_list;
    }

DeclarationNode::~DeclarationNode(){
    NODELIST_PTR_DELETE(this->variables_node_list);
}

void DeclarationNode::print() {
    std::cout << "declaration <line: " << line_number
        << ", col: " << col_number
        << "> " << std::endl;
}