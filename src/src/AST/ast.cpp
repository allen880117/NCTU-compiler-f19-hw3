#include "AST/ast.hpp"
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
void DeclarationNode::print() {
    std::cout << "declaration <line: " << line_number
        << ", col: " << col_number
        << "> " << std::endl;
}

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
void VariableNode::print() {
    
    std::cout << "variable <line: " << line_number
        << ", col: " << col_number
        << "> " << variable_name
        << " " << this->getType()
        << std::endl;
}

string VariableNode::getType() {
    switch(this->type->type_set){
        case SET_SCALAR:
        case SET_CONSTANT_LITERAL:
            switch(this->type->type){
                case TYPE_INTEGER: this->variable_type = "integer"; break;
                case TYPE_REAL:    this->variable_type = "real"; break;
                case TYPE_STRING:  this->variable_type = "string"; break;
                case TYPE_BOOLEAN: this->variable_type = "boolean"; break;
                default:           this->variable_type = "unknown"; break;
            }
            break;
        case SET_ACCUMLATED:
            switch(this->type->type){
                case TYPE_INTEGER: this->variable_type = "integer"; break;
                case TYPE_REAL:    this->variable_type = "real"; break;
                case TYPE_STRING:  this->variable_type = "string"; break;
                case TYPE_BOOLEAN: this->variable_type = "boolean"; break;
                default:           this->variable_type = "unknown"; break;
            }

            for(uint i=0; i<this->type->array_range.size(); i++){
                this->variable_type += "[";
                this->variable_type += to_string(this->type->array_range[i].start);
                this->variable_type += "...";
                this->variable_type += to_string(this->type->array_range[i].end);
                this->variable_type += "]";
            }
            break;
        default:
            this->variable_type = "unknown";
            break;
    }
    return this->variable_type;
}

ConstantValueNode::ConstantValueNode(
            int _line_number, 
            int _col_number, 
            VariableInfo* _constant_value){
                this->line_number = _line_number;
                this->col_number = _col_number;
                this->constant_value = _constant_value;
            }
void ConstantValueNode::print() {
    std::cout << "constant <line: " << line_number
        << ", col: " << col_number
        << "> ";

    // cout << literal_value
    switch(this->constant_value->type){
        case TYPE_INTEGER: std::cout << this->constant_value->int_literal; break;
        case TYPE_REAL:    std::cout << fixed << setprecision(6) << this->constant_value->real_literal; break;
        case TYPE_STRING:  std::cout << fixed << setprecision(6) << this->constant_value->string_literal; break;
        case TYPE_BOOLEAN:
            switch(this->constant_value->boolean_literal){
                case Boolean_TRUE:  std::cout << "true"; break;
                case Boolean_FALSE: std::cout << "false"; break;
                default: std::cout << "unknown"; break;
            } 
            break;
        default: std::cout << "unknown"; break;
    }
    // cout << literal_value

    std::cout << std::endl;
}

FunctionNode::FunctionNode(
            int _line_number, 
            int _col_number, 
            string _function_name, 
            NodeList* _parameters, 
            VariableInfo* _return_type, 
            Node _body, 
            int _end_line_number, 
            int _end_col_number, 
            string _end_name,
            vector<VariableInfo*> _prototype){
                this->line_number = _line_number;
                this->col_number = _col_number;
                this->function_name = _function_name;
                this->parameters = _parameters;
                this->return_type = _return_type;
                this->body = _body;
                this->end_line_number = _end_line_number;
                this->end_col_number = _end_col_number;
                this->prototype = _prototype;
            }
void FunctionNode::print() {
    std::cout << "function declaration <line: " << line_number
        << ", col: " << col_number
        << "> " << function_name
        << " " ;
    
    // cout << return_type (scalar_type or void)
    switch(this->return_type->type_set){
        case SET_SCALAR:
            switch(this->return_type->type){
                case TYPE_INTEGER: std::cout<<"integer"; break;
                case TYPE_REAL:    std::cout<<"real"; break;
                case TYPE_STRING:  std::cout<<"string"; break;
                case TYPE_BOOLEAN: std::cout<<"boolean"; break;
                default:           std::cout<<"unknown"; break;
            }
            break;
        case UNKNOWN_SET:
            switch(this->return_type->type){
                case TYPE_VOID: std::cout<<"void"; break;
                default:        std::cout<<"unknown"; break;
            }
            break;
        default: std::cout<<"unknown"; break; break;
    }
    // cout << return_type
  

    // cout << parameter_prototype
    std::cout<<" (";
        for(uint i=0; i<this->prototype.size(); i++){
            if(i != 0) std::cout<<", ";
            switch(this->prototype[i]->type_set){
                case SET_SCALAR:
                case SET_CONSTANT_LITERAL:
                    switch(this->prototype[i]->type){
                        case TYPE_INTEGER: std::cout<<"integer"; break;
                        case TYPE_REAL:    std::cout<<"real"; break;
                        case TYPE_STRING:  std::cout<<"string"; break;
                        case TYPE_BOOLEAN: std::cout<<"boolean"; break;
                        default:           std::cout<<"unknown"; break;
                    }
                    break;
                case SET_ACCUMLATED:
                    switch(this->prototype[i]->type){
                        case TYPE_INTEGER: std::cout<<"integer"; break;
                        case TYPE_REAL:    std::cout<<"real"; break;
                        case TYPE_STRING:  std::cout<<"string"; break;
                        case TYPE_BOOLEAN: std::cout<<"boolean"; break;
                        default:           std::cout<<"unknown"; break;
                    }

                    for(uint j=0; j<this->prototype[i]->array_range.size(); j++){
                        std::cout<<"[";
                        std::cout<<to_string(this->prototype[i]->array_range[j].end-this->prototype[i]->array_range[j].start);
                        std::cout<<"]";
                    }
                    break;
                default: std::cout<<"unknown"; break;
            }
        }
    std::cout<<")";
    // cout << parameter_prototype
    std::cout<<std::endl;
}

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