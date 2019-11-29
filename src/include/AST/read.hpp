#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class ReadNode : public ASTNodeBase
{
    public:
        int  line_number; // print
        int  col_number;  // print
        Node variable_reference_node; // Target

    public:
        ReadNode(
            int _line_number, 
            int _col_number, 
            Node _variable_reference_node);
        ~ReadNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};