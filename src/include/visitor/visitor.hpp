#include "AST/ast.hpp"

class ASTVisitor : public ASTVisitorBase
{
    public:
        void visit(ProgramNode *m) override;
        void visit(DeclarationNode *m) override;
        void visit(VariableNode *m) override;
        void visit(ConstantValueNode *m) override;
        void visit(FunctionNode *m) override;
        void visit(CompoundStatementNode *m) override;
        void visit(AssignmentNode *m) override;
        void visit(PrintNode *m) override;
        void visit(ReadNode *m) override;
        void visit(VariableReferenceNode *m) override;
        void visit(BinaryOperatorNode *m) override;
        void visit(UnaryOperatorNode *m) override;
        void visit(IfNode *m) override;
        void visit(WhileNode *m) override;
        void visit(ForNode *m) override;
        void visit(ReturnNode *m) override;
        void visit(FunctionCallNode *m) override;
};