#pragma once
#include "AST/ast.hpp"
#include "visitor/visitor.hpp"

class FunctionNode : public ASTNodeBase
{
    public:
        int  line_number; // function name
        int  col_number;  // function name
        string function_name;
        vector<NodeWithTypeList*>* parameters; // a list of declaration nodes (zero or more)
        VariableInfo* return_type;
        Node body; // a compound statement node
        int  end_line_number; // function name after end
        int  end_col_number;  // function name after end
        string end_name;

        vector<VariableInfo*> prototype;
    
    public:
        FunctionNode(
            int _line_number, 
            int _col_number, 
            string _function_name, 
            vector<NodeWithTypeList*>* _parameters, 
            VariableInfo* _return_type, 
            Node _body, 
            int _end_line_number, 
            int _end_col_number, 
            string _end_name,
            vector<VariableInfo*> _prototype);
        ~FunctionNode();
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};