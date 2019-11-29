#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class VariableNode : public ASTNodeBase
{
    public:
        int  line_number; // variable name
        int  col_number;  // variable name
        string variable_name;
        VariableInfo* type;
        Node constant_value_node; // constant value (zero or one)

        string variable_type;

    public:
        VariableNode(
            int _line_number, 
            int _col_number, 
            string _variable_name, 
            VariableInfo* _type, 
            Node _constant_value_node);
        ~VariableNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
        string getType();
};