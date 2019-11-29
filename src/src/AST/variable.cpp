#include "AST/variable.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

VariableNode::VariableNode(
    int _line_number, 
    int _col_number, 
    string _variable_name, 
    VariableInfo* _type, 
    Node _constant_value_node
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->variable_name = _variable_name;
        this->type = _type;
        this->constant_value_node = _constant_value_node;
    }

VariableNode::~VariableNode(){
    SAFE_DELETE(this->type)
    SAFE_DELETE(this->constant_value_node)
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