#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class ReturnNode : public ASTNodeBase
{
    public:
        int  line_number; // return
        int  col_number;  // return
        Node return_value; // an expression node

    public:
        ReturnNode(
            int _line_number, 
            int _col_number, 
            Node _return_value);
        ~ReturnNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};