#include "AST/program.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

ProgramNode::ProgramNode(
    int _line_number, 
    int _col_number, 
    string _program_name, 
    string _return_type,
    NodeList* _declaration_node_list, 
    NodeList* _function_node_list, 
    Node _compound_statement_node, 
    int _end_line_number, 
    int _end_col_number, 
    string _end_name
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->program_name = _program_name;
        this->return_type = _return_type;
        this->declaration_node_list = _declaration_node_list;
        this->function_node_list = _function_node_list;
        this->compound_statement_node = _compound_statement_node;
        this->end_line_number = _end_line_number;
        this->end_col_number = _end_col_number;
        this->end_name = _end_name;
    }

ProgramNode::~ProgramNode(){
    NODELIST_PTR_DELETE(this->declaration_node_list)
    NODELIST_PTR_DELETE(this->function_node_list)
    SAFE_DELETE(this->compound_statement_node)
}

void ProgramNode::print() {    
    std::cout << "program <line: " << line_number
        << ", col: " << col_number
        << "> " << program_name
        << " void" << std::endl;
}