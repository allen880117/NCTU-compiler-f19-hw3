#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class DeclarationNode : public ASTNodeBase
{
    public:
        int  line_number; // var
        int  col_number;  // var
        NodeList* variables_node_list; // Variables
    
    public:
        DeclarationNode(
            int _line_number, 
            int _col_number, 
            NodeList* _variables_node_list);
        ~DeclarationNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};