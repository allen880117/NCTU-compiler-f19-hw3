#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class ProgramNode : public ASTNodeBase
{
    public:
        int  line_number; // program name
        int  col_number;  // program name
        string program_name;
        string return_type;
        NodeList* declaration_node_list; // zero or more
        NodeList* function_node_list; // zero or more
        Node compound_statement_node;
        int  end_line_number; // program name after end
        int  end_col_number;  // program name after end
        string end_name;

    public:
        ProgramNode(
            int _line_number, 
            int _col_number, 
            string _program_name, 
            string _return_type,
            NodeList* _declaration_node_list, 
            NodeList* _function_node_list, 
            Node _compound_statement_node, 
            int _end_line_number, 
            int _end_col_number, 
            string _end_name );
        ~ProgramNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};