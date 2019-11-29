#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class ForNode : public ASTNodeBase
{
    public:
        int  line_number; // for
        int  col_number;  // for
        Node loop_variable_declaration; // a declaration node
        Node initial_statement; // an assignment node
        Node condition; // an expression node
        NodeList* body; // a list of statement nodes (zero or more)

    public:
        ForNode(
            int _line_number, 
            int _col_number, 
            Node _loop_variable_declaration, 
            Node _initial_statement, 
            Node _condition, 
            NodeList* _body);
        ~ForNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};