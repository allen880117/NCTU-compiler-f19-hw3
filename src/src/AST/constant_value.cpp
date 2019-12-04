#include "AST/constant_value.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

ConstantValueNode::ConstantValueNode(
    int _line_number, 
    int _col_number, 
    VariableInfo* _constant_value
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->constant_value = _constant_value;
    }

ConstantValueNode::~ConstantValueNode(){
    SAFE_DELETE(this->constant_value)
}

void ConstantValueNode::print() {
    std::cout << "constant <line: " << line_number
        << ", col: " << col_number
        << "> ";

    // cout << literal_value
    switch(this->constant_value->type){
        case TYPE_INTEGER: std::cout << this->constant_value->int_literal; break;
        case TYPE_REAL:    std::cout << fixed << setprecision(6) << this->constant_value->real_literal; break;
        case TYPE_STRING:  std::cout << this->constant_value->string_literal; break;
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