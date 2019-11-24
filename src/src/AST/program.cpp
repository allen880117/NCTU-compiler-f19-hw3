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
void ProgramNode::print(class ASTVisitorBase &v) {    
    v.print_space();
    std::cout<<"Is Hello?"<<std::endl;

    v.space_counter_increase();
        if (declaration_node_list != nullptr)
            for(uint i=0; i<declaration_node_list->size(); i++){
                (*declaration_node_list)[i]->accept(v);
            }

        if (function_node_list != nullptr)
            for(uint i=0; i<function_node_list->size(); i++){
                (*function_node_list)[i]->accept(v);
            }

        this->compound_statement_node->accept(v);
    v.space_counter_decrease();

}

DeclarationNode::DeclarationNode(
            int _line_number, 
            int _col_number, 
            NodeList* _variables_node_list){
                this->line_number = _line_number;
                this->col_number = _col_number;
                this->variables_node_list = _variables_node_list;
            }
void DeclarationNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}

VariableNode::VariableNode(
            int _line_number, 
            int _col_number, 
            string _variable_name, 
            VariableType* _type, 
            Node _constant_value_node){
                this->line_number = _line_number;
                this->col_number = _col_number;
                this->variable_name = _variable_name;
                this->type = _type;
                this->constant_value_node = _constant_value_node;
            }
void VariableNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void ConstantValueNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}

FunctionNode::FunctionNode(
            int _line_number, 
            int _col_number, 
            string _function_name, 
            NodeList* _parameters, 
            VariableType* _return_type, 
            Node _body, 
            int _end_line_number, 
            int _end_col_number, 
            string _end_name){
                this->line_number = _line_number;
                this->col_number = _col_number;
                this->function_name = _function_name;
                this->parameters = _parameters;
                this->return_type = _return_type;
                this->body = _body;
                this->end_line_number = _end_line_number;
                this->end_col_number = _end_col_number;
            }
void FunctionNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}

CompoundStatementNode::CompoundStatementNode(
            int _line_number, 
            int _col_number, 
            NodeList* _declaration_node_list, 
            NodeList* _statement_node_list){
                line_number=_line_number;
                col_number=_col_number;
            }
void CompoundStatementNode::print(class ASTVisitorBase &v) {
    v.print_space();
    std::cout<<"Is Hello?"<<std::endl;
    v.space_counter_increase();
    v.space_counter_decrease();
}
void AssignmentNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void PrintNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void ReadNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void VariableReferenceNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void BinaryOperatorNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void UnaryOperatorNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void IfNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void WhileNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void ForNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void ReturnNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}
void FunctionCallNode::print(class ASTVisitorBase &v) {std::cout<<"Is Hello?"<<std::endl;}