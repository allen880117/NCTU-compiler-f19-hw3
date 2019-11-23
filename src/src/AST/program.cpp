#if 0
#include "AST/program.h"

#include <stdio.h>

AstNode *newProgramNode(void) {
    // TODO
    printf("I didn't put the Program Node down in black and white, so it's "
           "between existence and non-existence. Surprise!\n");
    return NULL;
}

void freeProgramNode(void *node) {
    // TODO
    printf("You're a mature adult until you remember to free the memory space "
           "you allocated.\n");
}
#endif

#include "AST/program.hpp"
#include <iostream>
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
    string _end_name ){
        line_number = _line_number;
        col_number = _col_number;
        program_name = _program_name;
        return_type = _return_type;
        declaration_node_list = _declaration_node_list;
        function_node_list = _function_node_list;
        compound_statement_node = _compound_statement_node;
        end_line_number = _end_line_number;
        end_col_number = _end_col_number;
        end_name = _end_name;
    }
ProgramNode::~ProgramNode(){
    delete compound_statement_node;
    for(uint i=0; i<declaration_node_list->size(); i++)
        delete (*declaration_node_list)[i];
    for(uint i=0; i<function_node_list->size(); i++)
        delete (*function_node_list)[i];
    delete declaration_node_list;
    delete function_node_list;
}
void ProgramNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void DeclarationNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void VariableNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void ConstantValueNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void FunctionNode::print() {std::cout<<"Is Hello?"<<std::endl;}

CompoundStatementNode::CompoundStatementNode(
            int _line_number, 
            int _col_number, 
            NodeList* _declaration_node_list, 
            NodeList* _statement_node_list){
                line_number=_line_number;
                col_number=_col_number;
            }

void CompoundStatementNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void AssignmentNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void PrintNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void ReadNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void VariableReferenceNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void BinaryOperatorNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void UnaryOperatorNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void IfNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void WhileNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void ForNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void ReturnNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void FunctionCallNode::print() {std::cout<<"Is Hello?"<<std::endl;}