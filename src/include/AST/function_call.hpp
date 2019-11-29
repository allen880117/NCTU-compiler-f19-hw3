#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class FunctionCallNode : public ASTNodeBase
{
    public:
        int  line_number; // function name
        int  col_number;  // function name
        string function_name;
        NodeList* arguments; // a list of expression nodes (zero ro more);

    public:
        FunctionCallNode(
            int _line_number, 
            int _col_number, 
            string _function_name, 
            NodeList* _arguments);
        ~FunctionCallNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};