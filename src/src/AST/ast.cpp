#include "AST/ast.hpp"
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
void ProgramNode::print() {    
    std::cout << "program <line: " << line_number
        << ", col: " << col_number
        << "> " << program_name
        << " void" << std::endl;
}

DeclarationNode::DeclarationNode(
            int _line_number, 
            int _col_number, 
            NodeList* _variables_node_list){
                this->line_number = _line_number;
                this->col_number = _col_number;
                this->variables_node_list = _variables_node_list;
            }
void DeclarationNode::print() {std::cout<<"Is Hello?"<<std::endl;}

VariableNode::VariableNode(
            int _line_number, 
            int _col_number, 
            string _variable_name, 
            VariableInfo* _type, 
            Node _constant_value_node){
                this->line_number = _line_number;
                this->col_number = _col_number;
                this->variable_name = _variable_name;
                this->type = _type;
                this->constant_value_node = _constant_value_node;
            }
void VariableNode::print() {std::cout<<"Is Hello?"<<std::endl;}

ConstantValueNode::ConstantValueNode(
            int _line_number, 
            int _col_number, 
            VariableInfo* _constant_value){
                this->line_number = _line_number;
                this->col_number = _col_number;
                this->constant_value = _constant_value;
            }
void ConstantValueNode::print() {std::cout<<"Is Hello?"<<std::endl;}

FunctionNode::FunctionNode(
            int _line_number, 
            int _col_number, 
            string _function_name, 
            NodeList* _parameters, 
            VariableInfo* _return_type, 
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
void FunctionNode::print() {std::cout<<"Is Hello?"<<std::endl;}

CompoundStatementNode::CompoundStatementNode(
            int _line_number, 
            int _col_number, 
            NodeList* _declaration_node_list, 
            NodeList* _statement_node_list){
                line_number=_line_number;
                col_number=_col_number;
            }
void CompoundStatementNode::print() {
    std::cout << "compound statement <line: " << line_number
        << ", col: " << col_number
        << "> " << std::endl;
}
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