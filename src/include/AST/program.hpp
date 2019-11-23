#pragma once

#include <memory>
#include <vector>
#include <string>
using namespace std;

typedef vector< shared_ptr<ASTNodeBase> > NodeList;
typedef shared_ptr<ASTNodeBase>           Node;

class ASTVisitorBase
{
    public:
        virtual void visit(class ProgramNode *node) = 0;
        virtual void visit(class DeclarationNode *node) = 0;
        virtual void visit(class VariableNode *node) = 0;
        virtual void visit(class ConstantValueNode *node) = 0;
        virtual void visit(class FunctionNode *node) = 0;
        virtual void visit(class CompoundStatementNode *node) = 0;
        virtual void visit(class AssignmentNode *node) = 0;
        virtual void visit(class PrintNode *node) = 0;
        virtual void visit(class ReadNode *node) = 0;
        virtual void visit(class VariableReferenceNode *node) = 0;
        virtual void visit(class BinaryOperatorNode *node) = 0;
        virtual void visit(class UnaryOperatorNode *node) = 0;
        virtual void visit(class IfNode *node) = 0;
        virtual void visit(class WhileNode *node) = 0;
        virtual void visit(class ForNode *node) = 0;
        virtual void visit(class ReturnNode *node) = 0;
        virtual void visit(class FunctionCallNode *node) = 0;
};

class ASTNodeBase
{
    public:
        virtual void accept(class ASTVisitorBase &v) = 0;
        virtual ~ASTNodeBase(){};
};

class ProgramNode : public ASTNodeBase
{
    private:
        int  line_number; // program name
        int  col_number;  // program name
        string program_name;
        // string return_type;
        NodeList declaration_node_list;
        NodeList function_node_list;
        Node compound_statement_node;
        int  end_line_number; // program name after end
        int  end_col_number;  // program name after end
        string end_name;

    public:
        ProgramNode(int, int, string, NodeList, NodeList, Node, int, int, string);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class DeclarationNode : public ASTNodeBase
{
    private:
        int  line_number; // var
        int  col_number;  // var
        NodeList variables_node_list; // Variables
    
    public:
        DeclarationNode(int, int, NodeList);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class VariableNode : public ASTNodeBase
{
    private:
        int  line_number; // variable name
        int  col_number;  // variable name
        string variable_name;
        string type;
        Node constant_value_node; // constant value
    
    public:
        VariableNode(int, int, string, string, Node);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class ConstantValueNode : public ASTNodeBase
{
    private:
        int  line_number; // constant value
        int  col_number;  // constant value
        string constant_value; // Not sure its type
    
    public:
        ConstantValueNode(int, int, string);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class FunctionNode : public ASTNodeBase
{
    private:
        int  line_number; // function name
        int  col_number;  // function name
        string function_name;
        NodeList parameters; // a list of declaration nodes
        string return_type;
        Node body; // a compound statement node
        int  end_line_number; // function name after end
        int  end_col_number;  // function name after end
        string end_name;
    
    public:
        FunctionNode(int, int, string, NodeList, string, Node, int, int, string);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class CompoundStatementNode : public ASTNodeBase
{
    private:
        int  line_number; // begin
        int  col_number;  // begin
        NodeList declaration_node_list; // Local variable and constant declarations
        NodeList statement_node_list; // Statements

    public:
        CompoundStatementNode(int, int, NodeList, NodeList);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class AssignmentNode : public ASTNodeBase
{
    private:
        int  line_number; // :=
        int  col_number;  // :=
        Node variable_reference_node; // Lvalue
        Node expression_node; // Expression

    public:
        AssignmentNode(int, int, Node, Node);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class PrintNode : public ASTNodeBase
{
    private:
        int  line_number; // print
        int  col_number;  // print
        Node expression_node; // Target

    public:
        PrintNode(int, int, Node);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class ReadNode : public ASTNodeBase
{
    private:
        int  line_number; // print
        int  col_number;  // print
        Node variable_reference_node; // Target

    public:
        ReadNode(int, int, Node);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class VariableReferenceNode : public ASTNodeBase
{
    private:
        int  line_number; // variable name
        int  col_number;  // varibble name
        string variable_name;
        NodeList expression_node_list; // indices

    public:
        VariableReferenceNode(int, int, string, NodeList);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class BinaryOperatorNode : public ASTNodeBase
{
    private:
        int  line_number; // operator
        int  col_number;  // operator
        string op;
        Node left_operand; // an expression node
        Node right_operand; // an expression node

    public:
        BinaryOperatorNode(int, int, string, Node, Node);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class UnaryOperatorNode : public ASTNodeBase
{
    private:
        int  line_number; // operator
        int  col_number;  // operator
        string op;
        Node operand; // an expression node

    public:
        UnaryOperatorNode(int, int, string, Node);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class IfNode : public ASTNodeBase
{
    private:
        int  line_number; // if
        int  col_number;  // if
        Node condition; // an expression node
        NodeList body; // a list of statement nodes
        NodeList body_of_else; // a list of statement nodes

    public:
        IfNode(int, int, Node, NodeList, NodeList);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class WhileNode : public ASTNodeBase
{
    private:
        int  line_number; // while
        int  col_number;  // while
        Node condition; // an expression node
        NodeList body; // a list of statement nodes

    public:
        WhileNode(int, int, Node, NodeList);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class ForNode : public ASTNodeBase
{
    private:
        int  line_number; // for
        int  col_number;  // for
        Node loop_variable_declaration; // an declaration node
        Node initial_statement; // an assignment node
        Node condition; // an expression node
        NodeList body; // a list of statement nodes

    public:
        ForNode(int, int, Node, Node, Node, NodeList);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class ReturnNode : public ASTNodeBase
{
    private:
        int  line_number; // return
        int  col_number;  // return
        Node return_value; // an expression node

    public:
        ReturnNode(int, int, Node);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class FunctionCallNode : public ASTNodeBase
{
    private:
        int  line_number; // function name
        int  col_number;  // function name
        string function_name;
        NodeList arguments; // a list of expression nodes

    public:
        FunctionCallNode(int, int, string, NodeList);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};