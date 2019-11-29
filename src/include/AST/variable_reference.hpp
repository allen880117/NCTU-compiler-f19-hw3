#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class VariableReferenceNode : public ASTNodeBase
{
    public:
        int  line_number; // variable name
        int  col_number;  // varibble name
        string variable_name;
        NodeList* expression_node_list; // indices

    public:
        VariableReferenceNode(
            int _line_number, 
            int _col_number, 
            string _variable_name, 
            NodeList* _expression_node_list);
        ~VariableReferenceNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};