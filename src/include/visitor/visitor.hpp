#pragma once
#include "AST/ast.hpp"

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

class ASTVisitor : public ASTVisitorBase
{
    public:
        void visit(class ProgramNode *m) override;
        void visit(class DeclarationNode *m) override;
        void visit(class VariableNode *m) override;
        void visit(class ConstantValueNode *m) override;
        void visit(class FunctionNode *m) override;
        void visit(class CompoundStatementNode *m) override;
        void visit(class AssignmentNode *m) override;
        void visit(class PrintNode *m) override;
        void visit(class ReadNode *m) override;
        void visit(class VariableReferenceNode *m) override;
        void visit(class BinaryOperatorNode *m) override;
        void visit(class UnaryOperatorNode *m) override;
        void visit(class IfNode *m) override;
        void visit(class WhileNode *m) override;
        void visit(class ForNode *m) override;
        void visit(class ReturnNode *m) override;
        void visit(class FunctionCallNode *m) override;
};