#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class ConstantValueNode : public ASTNodeBase
{
    public:
        int  line_number; // constant value
        int  col_number;  // constant value
        VariableInfo* constant_value; // Not sure its type
    
    public:
        ConstantValueNode(
            int _line_number, 
            int _col_number, 
            VariableInfo* _constant_value);
        ~ConstantValueNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};