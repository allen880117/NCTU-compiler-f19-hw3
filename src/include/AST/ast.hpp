#pragma once

#include <memory>
#include <vector>
#include <string>
using namespace std;

typedef vector< class ASTNodeBase* > NodeList;
typedef class ASTNodeBase*           Node;

enum enumTypeSet{
    SET_SCALAR = 300,
    SET_ACCUMLATED,
    SET_CONSTANT_LITERAL,
    UNKNOWN_SET
};

enum enumType{
    TYPE_INTEGER = 400,
    TYPE_REAL,
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_VOID,
    UNKNOWN_TYPE
};

typedef struct __IntPair{
    int start;
    int end;
} IntPair;

enum BooleanLiteral{
    Boolean_TRUE = 400,
    Boolean_FALSE,
    UNKNOWN
};

typedef struct __VariableInfo{
    enumTypeSet type_set;
    enumType type;
    vector<IntPair> array_range;
    int int_literal;
    double real_literal;
    string string_literal;
    BooleanLiteral boolean_literal;
} VariableInfo ;

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

        uint space_counter = 0;
        void space_counter_increase();
        void space_counter_decrease();
        void print_space();
};

class ASTNodeBase
{
    public:
        virtual void accept(class ASTVisitorBase &v) = 0;
        virtual ~ASTNodeBase(){};
};

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
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
        ~ProgramNode(){};
};

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
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
        ~DeclarationNode(){};
};

class VariableNode : public ASTNodeBase
{
    public:
        int  line_number; // variable name
        int  col_number;  // variable name
        string variable_name;
        VariableInfo* type;
        Node constant_value_node; // constant value (zero or one)

        string variable_type;

    public:
        VariableNode(
            int _line_number, 
            int _col_number, 
            string _variable_name, 
            VariableInfo* _type, 
            Node _constant_value_node);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
        string getType();
        ~VariableNode(){};
};

class ConstantValueNode : public ASTNodeBase
{
    public:
        int  line_number; // constant value
        int  col_number;  // constant value
        VariableInfo* constant_value; // Not sure its type
    
    public:
        ConstantValueNode(
            int _line_number, 
            int _col_number, 
            VariableInfo* _constant_value);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class FunctionNode : public ASTNodeBase
{
    public:
        int  line_number; // function name
        int  col_number;  // function name
        string function_name;
        NodeList* parameters; // a list of declaration nodes (zero or more)
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
            NodeList* _parameters, 
            VariableInfo* _return_type, 
            Node _body, 
            int _end_line_number, 
            int _end_col_number, 
            string _end_name,
            vector<VariableInfo*> _prototype);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

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
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class AssignmentNode : public ASTNodeBase
{
    public:
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
    public:
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
    public:
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
    public:
        int  line_number; // variable name
        int  col_number;  // varibble name
        string variable_name;
        NodeList* expression_node_list; // indices

    public:
        VariableReferenceNode(int, int, string, NodeList*);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class BinaryOperatorNode : public ASTNodeBase
{
    public:
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
    public:
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
    public:
        int  line_number; // if
        int  col_number;  // if
        Node condition; // an expression node
        NodeList* body; // a list of statement nodes (zero or more)
        NodeList* body_of_else; // a list of statement nodes (zero or more)

    public:
        IfNode(int, int, Node, NodeList*, NodeList*);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class WhileNode : public ASTNodeBase
{
    public:
        int  line_number; // while
        int  col_number;  // while
        Node condition; // an expression node
        NodeList* body; // a list of statement nodes (zero or more)

    public:
        WhileNode(int, int, Node, NodeList*);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class ForNode : public ASTNodeBase
{
    public:
        int  line_number; // for
        int  col_number;  // for
        Node loop_variable_declaration; // an declaration node
        Node initial_statement; // an assignment node
        Node condition; // an expression node
        NodeList* body; // a list of statement nodes (zero or more)

    public:
        ForNode(int, int, Node, Node, Node, NodeList*);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};

class ReturnNode : public ASTNodeBase
{
    public:
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
    public:
        int  line_number; // function name
        int  col_number;  // function name
        string function_name;
        NodeList* arguments; // a list of expression nodes (zero ro more);

    public:
        FunctionCallNode(int, int, string, NodeList*);
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};