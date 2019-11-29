#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class UnaryOperatorNode : public ASTNodeBase
{
    public:
        int  line_number; // operator
        int  col_number;  // operator
        enumOperator op;
        Node operand; // an expression node

    public:
        UnaryOperatorNode(
            int _line_number, 
            int _col_number, 
            enumOperator _op, 
            Node _operand);
        ~UnaryOperatorNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};