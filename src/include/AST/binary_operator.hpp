#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class BinaryOperatorNode : public ASTNodeBase
{
    public:
        int  line_number; // operator
        int  col_number;  // operator
        enumOperator op;
        Node left_operand; // an expression node
        Node right_operand; // an expression node

    public:
        BinaryOperatorNode(
            int _line_number, 
            int _col_number, 
            enumOperator _op, 
            Node _left_operand, 
            Node _right_operand);
        ~BinaryOperatorNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};