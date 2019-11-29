#include "AST/compound_statement.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

CompoundStatementNode::CompoundStatementNode(
    int _line_number, 
    int _col_number, 
    NodeList* _declaration_node_list, 
    NodeList* _statement_node_list
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->declaration_node_list = _declaration_node_list;
        this->statement_node_list = _statement_node_list;
    }

CompoundStatementNode::~CompoundStatementNode(){
    NODELIST_PTR_DELETE(this->declaration_node_list)
    NODELIST_PTR_DELETE(this->statement_node_list)
}

void CompoundStatementNode::print() {
    std::cout << "compound statement <line: " << line_number
        << ", col: " << col_number
        << "> " << std::endl;
}