#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class IfNode : public ASTNodeBase
{
    public:
        int  line_number; // if
        int  col_number;  // if
        Node condition; // an expression node
        NodeList* body; // a list of statement nodes (zero or more)
        NodeList* body_of_else; // a list of statement nodes (zero or more)

    public:
        IfNode(
            int _line_number, 
            int _col_number, 
            Node _condition, 
            NodeList* _body, 
            NodeList* _body_of_else);
        ~IfNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};