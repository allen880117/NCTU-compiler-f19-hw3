#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class WhileNode : public ASTNodeBase
{
    public:
        int  line_number; // while
        int  col_number;  // while
        Node condition; // an expression node
        NodeList* body; // a list of statement nodes (zero or more)

    public:
        WhileNode(
            int _line_number, 
            int _col_number, 
            Node _condition, 
            NodeList* _body);
        ~WhileNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};