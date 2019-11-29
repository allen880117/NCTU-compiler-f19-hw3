#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class CompoundStatementNode : public ASTNodeBase
{
    public:
        int  line_number; // begin
        int  col_number;  // begin
        NodeList* declaration_node_list; // Local variable and constant declarations (zero or more)
        NodeList* statement_node_list; // Statements (zero or more)

    public:
        CompoundStatementNode(
            int _line_number, 
            int _col_number, 
            NodeList* _declaration_node_list, 
            NodeList* _statement_node_list);
        ~CompoundStatementNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};